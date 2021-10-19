import os
import string

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    # Getting user id
    id = session["user_id"]
    
    # Query summary tabel table for all the symbols
    symbol_list = db.execute("SELECT symbol, shares FROM summary WHERE user_id = ?", id)

    # total (float): Total amount of money for all the shares
    total = 0.0
    
    # user (list)
    user = []

    for element in symbol_list:
        
        # Collecting symbol
        # symbol (str)
        symbol = element["symbol"]
        # Collecting shares
        # shares (int)
        shares = element["shares"]

        # Collecting informations associated with symbol
        row = lookup(symbol)
        # company_name (str): Company's name
        company_name = row["name"]
        # stock_price (float): Stock's price
        stock_price = row["price"]
        
        # stock_total_price (float): Total price of stocks for single company
        stock_total_price = float(shares) * stock_price
        total += stock_total_price

        # Update summary table
        db.execute("UPDATE summary SET price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                   stock_price, stock_total_price, id, symbol)
        
        # Query summary table with id and symbol
        row5 = db.execute("SELECT * FROM summary WHERE user_id = ? AND symbol = ?", id, symbol)

        # Update row5 
        # Convert money in usd format
        row5[0]["price"] = usd(row5[0]["price"])
        row5[0]["total"] = usd(row5[0]["total"])
        
        # Add data to user
        user.append(row5[0])

    # Query users table for cash
    row6 = db.execute("SELECT cash FROM users WHERE id = ?", id)
    cash = row6[0]["cash"]
    # grand_total (float): Total amount of cash of all shares and the amount user has
    grand_total = cash + total

    # Convert money in usd
    cash_remain = usd(cash)
    grand_total = usd(grand_total)

    # User reached route via GET (As by clicking a link or via redirect)
    return render_template("index.html", user=user, cash_remain=cash_remain, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # User reached route via POST (As by submitting a form via POST)
    if request.method == "POST":
        
        # Ensure user provided a symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("MISSING SYMBOL")
        
        # Collect informations associated with the symbol
        # row (dict): the keys of row are stock symbol, company name and stock price
        row = lookup(symbol)
        
        # Ensure user provided a valid symbol
        if row == None:
            return apology("INVALID SYMBOL")
        
        # Ensure user provided shares
        shares = request.form.get("shares")
        if not shares:
            return apology("MISSING SHARES")
            
        # Ensure user provided positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("SHARES IS NOT POSITIVE INTEGER")
        except:
            return apology("SHARES IS NOT INTEGER")

        # company_name (str): Name of the company
        company_name = row["name"]
        # stock_price (float): Price of a stock
        stock_price = row["price"]
        # company_symbol (str): Company's symbol
        company_symbol = row["symbol"]

        # total_cash_needed (float): Total amount of money needed for
        # buying the shares
        total_cash_needed = float(shares) * stock_price

        # User's id
        id = session["user_id"]
        
        # Query database for user with the id 
        # row2 (list of dictionary)
        row2 = db.execute("SELECT * FROM users WHERE id = ?", id)
        
        # cash (float): Total cash the user has.
        cash = float(row2[0]["cash"])

        # Ensure user has sufficient money
        if cash < total_cash_needed:
            return apology("DON'T HAVE ENOUGH MONEY")

        # stock_price_usd (str): Stock price in usd format
        stock_price_usd = usd(stock_price)

        # cash_remain (float): Amount of remain cash after buying shares
        cash_remain = cash - total_cash_needed

        # now (datetime): Current date and time
        now = datetime.now()
        date_time = now.strftime("%Y-%m-%d %H:%M:%S")
        date_time = str(date_time)

        # Converting shares to int
        shares = int(shares)
        
        # Inserting user id, company symbol, shares, stock price and datetime in the history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, datetime) VALUES(?, ?, ?, ?, ?)", 
                   id, company_symbol, shares, stock_price_usd, date_time)

        # Updating cash in the users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_remain, id)

        # Query summary table
        row3 = db.execute("SELECT * FROM summary WHERE symbol = ? AND user_id = ?", company_symbol, id)

        # Inserting user id, company sybol, company name and shares in the summary table if they are not 
        # present in the table
        if (len(row3) == 0):
            db.execute("INSERT INTO summary (user_id, symbol, name, shares) VALUES(?, ?, ?, ?)",
                       id, company_symbol, company_name, shares)
            
        # If user is alreay in the summary table then update the table
        else:
            # Query summary table
            row4 = db.execute("SELECT * FROM summary WHERE user_id = ? AND symbol = ?", id, company_symbol)
            # Collect shares the user has.
            previous_shares = row4[0]["shares"]
            
            # Update shares
            new_shares = previous_shares + shares

            # Update shares in summary table
            db.execute("UPDATE summary SET shares = ? WHERE user_id = ? AND symbol = ?", new_shares, id, company_symbol)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (As by clicking a link or via redirect)
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    # Getting user id
    id = session["user_id"]
    
    # Query history table
    history = db.execute("SELECT * FROM history WHERE user_id = ?", id)
    
    # User reached routed by GET (As by clicking a link or via redirect)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # User reached route via POST (As by submitting a form via POST)
    if request.method == "POST":
        
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("MISSING SYMBOL")
        
        # Collect informations associated with the symbol
        # row (dict): the keys of row are stock symbol, company name and stock price
        row = lookup(symbol)
        
        # Ensures user provides a valid symbol
        if row == None:
            return apology("INVALID SYMBOL")

        # Informations associated with the symbol
        company_name = row["name"]
        stock_price = usd(row["price"])
        company_symbol = row["symbol"]
        
        # Shows the price of a stock associated with the symbol
        return render_template("quoted.html", company_name=company_name, stock_price=stock_price, company_symbol=company_symbol)
    
    # User reached route via GET (As by clicking a link or via redirect)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    
    # User reached route via POST (As by submitting a form via POST)
    if request.method == "POST":
        
        # Ensure user name was submitted
        username = request.form.get("username")
        if not username:
            return apology("MUST PROVIDE USERNAME!")

        # Ensure username doesn't exist already
        row = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(row) > 0:
            return apology("USERNAME ALREADY EXIST!")

        # Get users password and confirmation from form
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        # Ensure password and confirmation was provided
        if not password or not confirmation:
            return apology("MUST PROVIDE PASSWORD!")
        
        # Ensure password and confirmation are same
        if password != confirmation:
            return apology("PASSWORD DOESN'T MATCH!")
            
        # Checking valid password
        digits = "0123456789"
        punctuations = string.punctuation
        letters = string.ascii_lowercase + string.ascii_uppercase
        
        digit_present = False
        punctuation_present = False
        letter_present = False
        
        # Checking if password contain letter, digit, symbol or not
        for char in password:
            if char in digits:
                digit_present = True
            elif char in punctuations:
                punctuation_present = True
            elif char in letters:
                letter_present = True
        
        # If length of password is less than 6 or it doesn't contain letter, digit
        # and punctuation then reject registration
        if len(password) < 6 or not digit_present or not punctuation_present or not letter_present:
            return apology("Length of password must be atleast 6 and it should contain letter, digit and symbol")
        
        # Generates hash value of password
        password_hash = generate_password_hash(password)

        # Inserts user in the users table
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)
        
        # Redirect user to login form
        return redirect("/login")

    # User reached route via GET (As by clicking a link or via redirect)
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    # Getting user id
    id = session["user_id"]

    # User reached route via POST (As by submitting a form via POST)
    if request.method == "POST":
        
        # Ensure user provided symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("MUST SELECT SYMBOL")

        # Getting shares from form
        shares = request.form.get("shares")

        # Ensure user provided shares
        if not shares:
            return apology("MISSING SHARES")

        # Ensures user provided positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("SHARES IS NOT POSITIVE INTEGER")
        except:
            return apology("SHARES IS NOT INTEGER")

        # Query summary table for shares
        # summary (list of dictionary)
        summary = db.execute("SELECT shares FROM summary WHERE user_id = ? AND symbol = ?", id, symbol)
        # shares_available (int): Available shares
        shares_available = summary[0]["shares"]
        
        # Ensures user has enough shares to sell
        if shares > shares_available:
            return apology("DON'T HAVE ENOUGH SHARES TO SELL")

        # If shares is eqaual to user's available shares then delete the row from summary
        if shares == shares_available:
            db.execute("DELETE FROM summary WHERE user_id = ? AND symbol = ?", id, symbol)
        
        # Otherwise update the summary table
        elif shares < shares_available:
            # Update shares
            new_shares = shares_available - shares
            # Update table with new shares 
            db.execute("UPDATE summary SET shares = ? WHERE user_id = ? AND symbol = ?", new_shares, id, symbol)

        # Query users table for cash
        users = db.execute("SELECT cash FROM users WHERE id = ?", id)
        # cash (float)
        cash = users[0]["cash"]

        # Collecting stock informations associated with the symbol
        row = lookup(symbol)
        
        # stock_price (float)
        stock_price = row["price"]
        
        # stock_price_usd (str)
        # Converting stock price in usd format
        stock_price_usd = usd(stock_price)
        
        # new_cash(float)
        # Update cash after selling shares
        new_cash = cash + stock_price * float(shares)

        # Updating users table with new cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, id)

        # now (datetime)
        now = datetime.now()
        date_time = now.strftime("%Y-%m-%d %H:%M:%S")
        date_time = str(date_time)

        # Selling shares are negative
        shares = -shares

        # Insert user id, shares, stock price and datetime into history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, datetime) VALUES(?, ?, ?, ?, ?)",
                   id, symbol, shares, stock_price_usd, date_time)
        
        # Redirecting the user to home page
        return redirect("/")

    # Query summary for symbol
    symbols = db.execute("SELECT symbol FROM summary WHERE user_id = ?", id)
    # User reached route via GET (As by clicking a link or via redirect)
    return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

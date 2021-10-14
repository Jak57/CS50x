--Keep a log of any SQL queries you execute as you solve the mystery.
--Crime Scene Information:
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
--Details: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
--Time: 10:15 AM
--Interview: 3
--Transcript: contains courthouse

--Transcripts:
SELECT id, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND year = 2020 AND month = 7 AND day = 28;
--Information related to thief:
--Person 1:
--Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Time: 10 min
--Footage: parking (license number), exit ear
--Person 2:
--I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--ATM: Fifer Street, withdraw money
--Person3:
--As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--Call duration: < 1 min
--Place: Out of Fiftyville
--Ask: Buy ticket for tomorrow

--Courthouse security log:
--Using informations of person 1:
--License plate:
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";
--Suspected People:
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit");
--List-01:

--Patrick
--Amber
--Elizabeth
--Roger
--Danielle
--Russell
--Evelyn
--Ernest


--ATM info:
--Using informations of person 2:
--Account Number:

SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";




--Id of people who withdraw money using bank_accounts table:

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");





--Name of people who withdraw money:

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
--List-02:
--name

--Bobby
--Elizabeth
--Victoria
--Madison
--Roy
--Danielle
--Russell
--Ernest

--So, the suspected people are (comparing List-01 and List-02):
--These people have the suspected license,  account numbers and they withdraw money.

--List-03:
--Elizabeth
--Danielle
--Russell
--Ernest


--Phone call information:
--Using information of person 3:

SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

--Caller name:

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);
--List-04:

--name
--Bobby
--Roger
--Victoria
--Madison
--Russell
--Evelyn
--Ernest
--Kimberly

--So, the suspected people who call in the suspected manner, have suspected license and withdraw money are: (using List 3 and 4)
--List-05:
--Russell
--Ernest

--Airport information:

--Using information of person 3:
SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%";

SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%") ORDER BY hour;

--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30

--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15

--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20

--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0

--Destination airport id = 4 (as the thief take earliest flight)

SELECT city FROM airports WHERE id = 4;

--City = London

--Flight id: 36

SELECT passport_number FROM passengers WHERE flight_id = 36;




SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

--List-06:
--name

--Bobby

--Roger

--Madison

--Danielle

--Evelyn

--Edward

--Ernest

--Doris

--So, these are the suspected people.

--Comparing them from above suspected people (List 5 and 6) we get:
--Name:
--Ernest

--He is the thief.

--Finding the accompany:
--Using information of person 3:
SELECT phone_number FROM people WHERE name = "Ernest";

--phone_number

--(367) 555-5533

--Finding Receiver :

SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = "Ernest") AND year = 2020 AND month = 7 AND day = 28 AND duration < 60;

--receiver:

--(375) 555-8161

SELECT name FROM people WHERE phone_number = "(375) 555-8161";

--Accomplice name:
--Berthold


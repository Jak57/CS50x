#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];
int cnt;

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool visit[MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int i;
    string s;
    for (i = 0; i < candidate_count; i++)
    {
        s = candidates[i];
        if (strcmp(s, name) == 0)
        {
            ranks[rank] = i;
           
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int i, j, n = candidate_count, x, y;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            x = ranks[i];
            y = ranks[j];

            preferences[x][y] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
   
    int i, j, n = candidate_count - 1, a, b, k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            a = preferences[i][j];
            b = preferences[j][i];

            if (a > b)
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
            else if (a < b)
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                k++;
            }
        }
    }

    pair_count = k;
   
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
   
    int i, j, n = pair_count - 1, a, b, w1, l1, w2, l2, t1, t2;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            w1 = pairs[j].winner;
            l1 = pairs[j].loser;

            w2 = pairs[j + 1].winner;
            l2 = pairs[j + 1].loser;

            a = preferences[w1][l1];
            b = preferences[w2][l2];

            if (b > a)
            {
                t1 = pairs[j].winner;
                t2 = pairs[j].loser;

                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;

                pairs[j + 1].winner = t1;
                pairs[j + 1].loser = t2;
            }
        }
    }

   
    return;
}

void dfs(int i)
{
    int j;
    visit[i] = true;
    for (j = 0; j < candidate_count; j++)
    {
        if (locked[i][j] == true && visit[j] == false)
        {
            dfs(j);
        }
        else if (locked[i][j] == true && visit[j] == true)
        {
            cnt++;
            return;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    
    int i, j, x, y, k, count, id;
    for (i = 0; i < pair_count; i++)
    {
        x = pairs[i].winner;
        y = pairs[i].loser;
        locked[x][y] = true;

        for (j = 0; j < candidate_count; j++)
        {
            visit[j] = false;
        }
        
        visit[x] = true;
        cnt = 0;
        dfs(y);
        
        if (cnt > 0)
        {
            locked[x][y] = false;
        }


    }

 

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
  
    int i, j, n = candidate_count, count;

    for (i = 0; i < n; i++)
    {
        count = 0;
        for (j = 0; j < n; j++)
        {
            if (locked[j][i] == false)
            {
                count++;
            }
        }

        if (count == n)
        {
           
            break;
        }
    }

    printf("%s\n", candidates[i]);
    return;
}


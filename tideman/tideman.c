#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

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
    // Check if the rank is in range - For current realisation of the main function it is obsolete
    if (rank < 0 || rank > (candidate_count - 1))
    {
        return false;
    }

    // Check if the name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Check if the rank for this voter is not taken - For current realisation of the main function it is impossible (no ranks clearing) and actually obsolete

            // Update ranks[]
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair curPair;
    int curMaxVote, curInd;
    for (int i = 0; i < pair_count; i++)
    {
        curMaxVote = 0;
        curInd = -1;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > curMaxVote)
            {
                curMaxVote = preferences[pairs[j].winner][pairs[j].loser];
                curInd = j;
            }
        }
        curPair = pairs[i];
        pairs[i] = pairs[curInd];
        pairs[curInd] = curPair;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool branchstep(int k, int curNode);

    for (int i = 0; i < pair_count; i++)
    {
        if (!branchstep(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}


// Recursive function for graph branches testing for cycles
bool branchstep(int k, int curNode)
{
    for (int i = 0; i < candidate_count; i++) // cycle over candidates to look for the branch prolongation
    {
        if (locked[curNode][i]) // current candidate beats someone - branch continues
        {
            if (i == k) // we returned to the source - this is a cycle
            {
                return true;
            }
            else if (branchstep(k, i)) // It is just a branch continuation - lets go next step
            {
                return true; // THis "True" is passed though the recursion stack up
            }
        }
    }

    return false; // This candidate doesn't beat anyone - theis is the end of the branch without cycling
}

// Print the winner of the election
void print_winner(void)
{
    bool isLoser = true;
    int cand = 0;
    while (isLoser)
    {
        isLoser = false;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][cand])
            {
                isLoser = true;
            }
        }
        cand++;
    }
    printf("%s\n", candidates[cand - 1]);
    return;
}


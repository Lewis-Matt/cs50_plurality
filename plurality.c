#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates, of length = to the constant MAX (9), of type candidate
candidate candidates[MAX];

// Number of candidates, global variable
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates, subtract 1 as the 1st arg is the program itself
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // the dot (.) operator is used to access the children of candidates (which is type candidate, containing name and votes)
        candidates[i].name = argv[i + 1]; // accessing string variable 'name' of ith position of candidates array, and setting this counter = to i + 1 (adding 1 as 1st agrv is the program)
        candidates[i].votes = 0; // accessing int variable 'votes' of ith position of the candidates array, and setting the counter to 0.
    }
    // ask for the number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        // each voter enters the name of the candidate they are voting for
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)) // ! reverses the truth value of the bool. So this if statement will run when !vote(name) is true, which occurs when
                        // vote(name) is false (line 82)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election

    print_winner();
}

// Update vote totals given a new vote
bool vote(string name) // look for candidate called 'name', if found update their vote total and return true
{
    for (int i = 0; i < candidate_count; i++)
    {
        // asking if the name entered (2nd name) matches a name in the ith position of the array (loops through all names) and increases the vote count
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false; // candidate not found (name typed (voted for) doesn't match what is in the array)
}

// Print the winner (or winners) of the election (need to sort and search)
void print_winner(void) // no input from caller / output to caller; just executes whatever is inside the function
{
   // loop to determine the maximum votes
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes) //
        {
            max_votes = candidates[i].votes; // max_votes is updated after looking at the number of votes for each candidate
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes) // will print out multiple winners if their votes = max_votes
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

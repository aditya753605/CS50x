/* a program to conduct an election 
 * and calculate the result based 
 * on tideman way.
 * */
#include <stdio.h>    // printf(), scanf()
#include <string.h>   // strcmp()

// max number of candidates
#define MAX 9

int preferences[MAX][MAX];

int locked[MAX][MAX];

// defining custom type 
typedef struct{
  int winner;
  int loser;
} pair;

char *candidates[MAX];
pair pairs[MAX *(MAX - 1) / 2];

int pair_count;
int candidate_count;

// function prototypes
int vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int cycle(int winner, int loser);

// getting command line input
int main(int argc, char *argv[])
{
  // checking command line input
  if(argc < 2)
  {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }
  
  candidate_count = argc - 1;

  // checking candidate_count
  if(candidate_count > MAX)
  {
    printf("Maximum number of candidate is %i\n", MAX);
    return 2;
  }
  
  // setting candidate names
  for(int i = 0; i < candidate_count; i++)
  {
    candidates[i] = argv[i+1];
  }
  
  for(int i = 0; i < candidate_count; i++)
  {
    for(int j = 0; j < candidate_count; j++)
    {
      locked[i][j] = 0;
    }
  }

  pair_count = 0;
  // detting voter count
  int voter_count;
  printf("Number of voters: ");
  scanf("%d", &voter_count);

  for(int i = 0; i < voter_count; i++)
  {
    int ranks[candidate_count];

    for (int j = 0; j < candidate_count; j++)
    {
      char name[10];
      printf("Rank %i: ", j+1);
      scanf("%s", name);
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
// update ranks given a new vote
int vote(int rank, char *name, int ranks[])
{
  for(int i = 0; i < candidate_count; i++)
  {
    if (strcmp(name, candidates[i]) == 0)
    {
      ranks[rank] = i;
      return 1;
    }
  }
  return 0;
}

// update preferences given one's voter's rank
void record_preferences(int ranks[])
{
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = i + 1; j < candidate_count; j++)
    {
      preferences[ranks[i]][ranks[j]]++;
    }
  }
  return;
}

// Record pairs of candidate where one is preferred over the other
void add_pairs(void)
{
  int strength;
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = i + 1; j < candidate_count; j++)
    {
      strength = preferences[i][j] - preferences[j][i];
      if (strength > 0)
      {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
      else if (strength < 0)
      {
        pairs[pair_count].winner = j;
        pairs[pair_count].loser = i;
        pair_count++;
      }
    }
  }
  return;
}
// sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
  for (int i = 0; i < pair_count; i++)
  {
    int strongest = preferences[pairs[i].winner][pairs[i].loser] -
                    preferences[pairs[i].loser][pairs[i].winner];
    int current_strongest;
    int strongest_index = i;
    for (int j = i + 1; j < pair_count; j++)
    {
        current_strongest = preferences[pairs[j].winner][pairs[j].loser] -
                            preferences[pairs[j].loser][pairs[j].winner];
        if (strongest < current_strongest)
        {
            strongest = current_strongest;
            strongest_index = j;
        }
    }
    if (strongest_index != i)
    {
        pair buffer = pairs[i];
        pairs[i] = pairs[strongest_index];
        pairs[strongest_index] = buffer;
    }
  }
  return;
}
// lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle(pairs[i].winner, pairs[i].loser) == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int is_winner = 1;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1)
            {
                is_winner = 0;
                break;
            }
        }
        if (is_winner == 1)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

int cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == 1)
        {
            if (cycle(winner, i) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

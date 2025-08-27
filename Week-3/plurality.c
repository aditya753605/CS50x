/* a program to conduct a election where 
 * each person can vote for a single person
 */
#include <stdio.h>      // printf(), Scanf()
#include <string.h>     // strcmp()

// max number of candidate
#define MAX 9           
// a custom data type to store candidate name and their votes
typedef struct
{
  char *name;
  int votes;
} candidate;

candidate candidates[MAX];

// declaring candidate_count as global variable
int candidate_count;

int vote(char *name);
void print_winner(void);

// getting command line input
int main(int argc, char **argv)
{
  //  checking if correct CLI
  if (argc < 2)
  {
    printf("Usage: plurality [candidate ...]\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX)
  {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  // setting candidate names
  for(int i = 0; i < candidate_count; i++)
  {
    candidates[i].name = argv[i+1];
    candidates[i].votes = 0;
  }

  // getting number of voters
  int voter_count;
  printf("Number of voters: ");
  scanf ("%d", &voter_count);

  // getting votes from voters
  for (int i = 0; i < voter_count; i++) 
  {
    char name[10];
    printf("Vote: ");
    scanf("%s", name);

    // checking if vote is correct or not
    if (!vote(name))
    {
      printf("Invalid vote.\n");
    }
  }
  // printing winner 
  print_winner();
  return 0;  
}
int vote(char *name)
{
  for(int i = 0; i < candidate_count; i++)
  {
    // checking if the name given by voter is same as candidate name or not
    if(strcmp(name, candidates[i].name) == 0)
    {
      candidates[i].votes += 1;
      return 1;
    }
  }
  return 0;
}
void print_winner(void)
{
  int max_votes = 0;

  // getting the max votes for a candidate
  for(int i = 0; i < candidate_count; i++)
  {
    if(candidates[i].votes > max_votes)
    {
      max_votes = candidates[i].votes;
    }
  }
  
  // printing candidate with max votes as winnner
  for(int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes == max_votes)
    {
      printf("%s\n", candidates[i].name);
    }
  }
  return;
}


// make a program in which usser input 
// the amount and we return him the minimum 
// number of coins required as change.
#include <ctype.h>      // for isdigit()
#include <stdio.h>      // for printf(), scanf()
#include <stdlib.h>     // for atol()
#include <string.h>     // for strlen()

int coin(int cash);
int main()
{
    int cash, coins, valid;
    char check[25];
    // prompt until user enters a valid cash amount
    do
    {
        
        printf("Change owed: ");
        scanf("%s", check);

        valid = 1;
        
        // checking if all character in input are digit
        for (int i = 0; i < (int)strlen(check);i++)
        {   
            if(!isdigit(check[i]))
            {
                valid = 0;
                break;
            }
        }
        if (valid)
        {
            cash = atoi(check);        // convert to integer if input is valid
        }
        else
        {
            cash = -1;        // Force reprompt on invalid input
        }
        
    }
    while (cash < 0);
    
    if (cash == 0)
    {
        printf("0\n");
    }
    else
    {
        // calculating nummber of min coins required
        coins = coin(cash);
        printf("%d\n", coins);
    }
    return 0;
}
int coin(int cash)
{
    int count = 0;
    // making an array of coin denomination in cents
    int coins[] = {25, 10, 5, 1};

    // Loop through each coin denomination, starting from largest
    for (int i = 0; i < 4; i++)
    {
        count = count + cash / coins[i];
        cash = cash % coins[i];
    }
    return count;
}

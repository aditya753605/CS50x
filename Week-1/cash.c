// make a program in which usser input 
// the amount and we return him the minimum 
// number of coins required as change.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int coin(int cash);
int main()
{
    int cash, coins, valid;
    char check[25];
    do
    {
        printf("Change owed: ");
        scanf("%s", check);

        valid = 1;
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
            cash = atoi(check);
        }
        else
        {
            cash = -1;
        }
        
    }
    while (cash < 0);
    if (cash == 0)
    {
        printf("0\n");
    }
    else
    {
        coins = coin(cash);
        printf("%d\n", coins);
    }
    return 0;
}
int coin(int cash)
{
    int count = 0;
    int coins[] = {25, 10, 5, 1};
    for (int i = 0; i < 4; i++)
    {
        count = count + cash / coins[i];
        cash = cash % coins[i];
    }
    return count;
}
// a program in which we check 
// whether a given number is a real card number or not
// and printing it's type

#include <ctype.h>      // for isdigit()
#include <stdio.h>      // for printf(), scanf()
#include <stdlib.h>     // for atol()
#include <string.h>     // for strlen()

int cal_check_sum(long card_number);
void card_name(int count, int number);

int main()
{
	long card_number, number;
	int check_sum, valid, count = 0;
	char check[30];

	// Prompt until user enters a valid number
	do
	{
		printf("Number: ");
		scanf("%s", check);
		valid = 1;

		int len = strlen(check);
		// Check if all characters in input are digits
		for (int i = 0; i < len; i++)
		{
			 if (!isdigit(check[i]))
            {
                valid = 0;
                break;
            }
		}
		if(valid)
		{
			card_number = atol(check);		// Convert to long if input is valid
		}
		else 
		{
			card_number = -1;			// Force reprompt on invalid input
		}
	}
	while(card_number < 0);

	// calculating check sum
	check_sum = cal_check_sum(card_number);
	 
	// validate checksum
	if(check_sum % 10 != 0)
	{
		printf("INVALID\n");
		return 0;
	}
	else
	{
		// getting first two digit of card number
		while (card_number > 100)
		{
			number = card_number / 10;
			card_number /= 10;
		}

		// counting the number of digits in card number
		count = strlen(check);

		// display card type
		card_name(count, number);
	}
	return 0;
}

int cal_check_sum(long card_number)
{
	long n = card_number;
	int sum1 = 0, sum2 = 0;
	int last_digit, second_last;
	for (n; n >0; n = n /100)
	{
		// Add last digit to sum1 (odd positions from right)
		last_digit = n % 10;
		// Double second last digit and add adjusted value to sum2 (even positions from right)
		second_last = (n / 10) % 10;
		second_last *= 2;

		if(second_last > 9)
		{
			second_last -= 9;
		}

		sum1 += last_digit;
		sum2 += second_last;
	}
	return sum1 + sum2;
}
void card_name(int count, int number)
{
    // condition for American Express card
    if (count == 15 && (number == 34 || number == 37))
    {
        printf("AMEX\n");
    }
    // condition for Mastercard
    else if (count == 16 &&
             (number == 51 || number == 52 || number == 53 || number == 54 || number == 55))
    {
        printf("MASTERCARD\n");
    }
    // condition for VISA card
    else if ((count == 13 || count == 16) && number / 10 == 4)
    {
        printf("VISA\n");
    }
    // if no match,, number is invalid
    else
    {
        printf("INVALID\n");
    }
}

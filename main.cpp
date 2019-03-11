#include <iostream>

using namespace std;


#define ASCII_0 48
#define ASCII_9 57

bool characteristic(char numString[], int& c);

int main()
{
	char number[] = "  123.53245456";
	int c = 0;

	if (characteristic(number, c))
		cout << c << endl;
	else
		cout << "error with input string" << endl;

	system("pause");
	return 0;
}



bool characteristic(char numString[], int& c)
{
	bool isValid = true;

	//True = positive, False = negative
	bool sign = true;
	//The running value of the characteristic
	int res = 0;

	char * currentAddress = numString;

	//skips over leading spacess
	while (*currentAddress == ' ')
	{
		currentAddress++;
	}

	//checks if string begins with + or -
	if (*currentAddress == '+')
	{
		sign = true;
		currentAddress++;
	}
	else if (*currentAddress == '-')
	{
		sign = false;
		currentAddress++;
	}

	for (currentAddress; *currentAddress != '\0'; currentAddress++) {
		//End of characteristic
		if (*currentAddress == '.')
		{
			break;
		}
		else if ((*currentAddress <= ASCII_0 || *currentAddress >= ASCII_9))
		{
			isValid = false;
			break;
		}
		else
		{
			//Will continue to add to res and shift digits over by multiplying res by 10
			res = res * 10 + *currentAddress - '0';
		}
	}

	//if everything was good, place res into c
	if (isValid)
		c = res; 

	return isValid;
}
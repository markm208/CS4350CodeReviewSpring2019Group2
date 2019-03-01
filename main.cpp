#include <iostream>

using namespace std;

bool characteristic(char numString[], int& c);
int getStringSize(char numString[]);
void getFirstHalf(char originalString[], char newString[]);
bool validateNum(char * newString);
int arrToInt(char * validatedString);

int main()
{
	char number[] = "  123.53245456";
	int c = 0;

	characteristic(number, c);
	cout << c << endl;

	system("pause");
	return 0;
}

//characteristic function takes in two parameters: numString is a char [] representation of a number,
//int c is the int that is supposed to be represented in numString, the point of the function is so that c == numString as an int
//if the data passed in is not valid, we must return false
bool characteristic(char numString[], int& c)
{
	//bool variable avoids multiple return statements
	bool isValid = true;

	//dynamically allocated with +1 for '\0'
	char * firstHalf = new char[getStringSize(numString) + 1]{};

	//firstHalf will hold all of the elements before the '.' while removing spaces
	getFirstHalf(numString, firstHalf);

	//validateNum will make sure there are no bad symbols, make sure the first element is + or -, and will return true if valid 
	if (!validateNum(firstHalf))
	{
		cout << "User input is not valid on left side of '.'" << endl;
		isValid = false;
	}

	//c gets the value returned from conversion function
	c = arrToInt(firstHalf);

	//Get that Memory back, it's not like we can just download more RAM ;)
	delete firstHalf;
	return isValid;
}

//this function was implemented to allow for dynamic allocation of the char []
int getStringSize(char numString[])
{
	char* currentAddress = numString;
	int counter = 0;
	for (currentAddress; *currentAddress != '\0'; currentAddress++) {
		if (*currentAddress == '.')
		{
			break;
		}
		else if (*currentAddress == ' ')
		{
			continue;
		}
		counter++;
	}
	return counter;
}

//Having a seperate function to parse the correct part of the string allows for more readable code
//numString is the original char[], firstHalf is the inheriting char[] that will only get good values before the '.'
void getFirstHalf(char originalString[], char newString[])
{
	char* currentAddress = originalString;
	int counter = 0;
	for (currentAddress; *currentAddress != '\0'; currentAddress++) {
		if (*currentAddress == '.')
		{
			break;
		}
		else if (*currentAddress == ' ')
		{
			continue;
		}

		newString[counter] = *currentAddress;
		counter++;
	}
}

//This function does the work for the characteristic boolean return, and checks the string for any bad inputs
bool validateNum(char * newString)
{
	bool isStringValid = true;
	char * currentAddress = newString;

	//two differnt forms of input
	//one where there could be '+' or '-' in first element
	if (*currentAddress == '+' || *currentAddress == '-')
	{
		//increment if first element is '+' or '-'
		currentAddress++;
		for (currentAddress; *currentAddress != '\0'; currentAddress++) {
			//ascii values 0-9
			//will fall into if if char at *currentAddress != 0-9
			if ((*currentAddress <= 48 || *currentAddress >= 57))
			{
				isStringValid = false;
				break;
			}
		}
	}
	//and one where there is no '+' and no '-'
	else
	{
		for (currentAddress; *currentAddress != '\0'; currentAddress++) {
			//ascii values 0-9
			//will fall into if if char at *currentAddress != 0-9
			if ((*currentAddress <= 48 || *currentAddress >= 57))
			{
				isStringValid = false;
				break;
			}
		}
	}

	return isStringValid;
}

//converts the validated string to int
int arrToInt(char * validatedString)
{
	int res = 0;
	char * currentAddress = validatedString;
	bool isNegative = false;

	if (*currentAddress == '-')
	{
		isNegative = true;
		currentAddress++;
	}
	else if (*currentAddress == '+')
	{
		currentAddress++;
	}

	for (currentAddress; *currentAddress != '\0'; currentAddress++) {
		res = res * 10 + *currentAddress - '0';
	}
	if (isNegative)
	{
		res *= -1;
	}

	return res;
}

#include <iostream> //do not include anything other than this
#define INT_MAX 2,147,483,647


using namespace std;

//Fraction Struct that represents each fraction in equation
struct Fraction
{
    char sign;
    int constant;
    int numerator;
    int denominator;
};
//Addition function I'm implementing
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int findLCM(int d1, int d2);

int convertToImproper(Fraction fraction); 

int abs(int num);

void printFractions(Fraction firstFraction);

int gcd(int, int);

int getNumDigits(int numerator);

void longDivision(Fraction &answer, char result[], int len);

void splitDividend(char* numerator, int dividend,int sizeOfDividend);

Fraction addFractions(Fraction firstFraction, Fraction secondFraction);

Fraction changeFractionSign(Fraction fraction);

void simplifyFraction(Fraction &fraction);

void intToChar(int number, char* parsedNumerator);

void reverseOrder(char* parsedNumerator, int dividend);
//Test Functions
void testAdd();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);

int main()
{
    testAdd();

    return 0;
}

//new functions go here
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //Local variables
    Fraction firstFraction;
    Fraction secondFraction;
    Fraction answer;

    bool retVal = true;
    int lcm;
    //Can't divide by 0
    if (d1 == 0 || d2 == 0 || len == 0)
    {
        retVal = false;
        return retVal;
    }
    //Assign all the passed in variables to 2 fraction objects
    firstFraction.constant = c1;
    firstFraction.numerator = n1;
    firstFraction.denominator = d1;

    secondFraction.constant = c2;
    secondFraction.numerator = n2;
    secondFraction.denominator = d2;

    //Convert to improper
    firstFraction.numerator = convertToImproper(firstFraction);
    firstFraction.constant = '\0';

    secondFraction.numerator = convertToImproper(secondFraction);
    secondFraction.constant = '\0';

    //Changes the sign of the fraction
    firstFraction = changeFractionSign(firstFraction);
    secondFraction = changeFractionSign(secondFraction);
    //Gets Least Common Multiple
    lcm = findLCM(d1, d2);

    //Multplies two improper fractions if denominator is not LCM
    if (firstFraction.denominator != lcm)
    {
        int multiplier = lcm / firstFraction.denominator;

        firstFraction.denominator = firstFraction.denominator * multiplier;
        firstFraction.numerator = firstFraction.numerator * multiplier;
    }

    if (secondFraction.denominator != lcm)
    {
        int multiplier = lcm / secondFraction.denominator;

        secondFraction.denominator = secondFraction.denominator * multiplier;
        secondFraction.numerator = secondFraction.numerator * multiplier;
    }

    //Add the two fractions together
    answer = addFractions(firstFraction, secondFraction);
    //Simplify the two fractions if necessary
    simplifyFraction(answer);

    //Ignoring the - sign for actual divison
    if(answer.denominator < 0 || answer.numerator < 0)
    {
        answer.sign = '-';
        answer.denominator = abs(answer.denominator);
        answer.numerator = abs(answer.numerator);
    }
    longDivision(answer, result, len);
    //Get the true size of the result array
    size_t n = sizeof(result)/sizeof(result[0]);
    //Print out the answer
    cout << "Answer: ";
    for(int i = 0; i < len; i++)
    {
        cout << result[i];
    }
    cout << endl;
    return retVal;
}
void intToChar(int number, char* parsedNumerator)
{
    int position = 0;
    //Converts a single integer to a char array to be used in the long div function
    while(number)
    {
       parsedNumerator[position] = number % 10 + 48;
       number /= 10;
       position++;
    }
    position++;
    parsedNumerator[position] = '\0';
    
    
}

void reverseOrder(char* parsedNumerator, int numDigits)
{
    //Reverses the order of the char[] using simple swap algorithm
    char temp;
    int i, j = 0;

 
    i = 0;
    j = numDigits - 1;
    
    while (i < j) {
        temp = parsedNumerator[i];
        parsedNumerator[i] = parsedNumerator[j];
        parsedNumerator[j] = temp;
        i++;
        j--;
    }
    
}
//Long division Function
void longDivision(Fraction &answer, char result[], int len)
{   
    int divisor = answer.denominator;
    int dividend = answer.numerator;

    int numOfDigits = getNumDigits(dividend);//log10(dividend) + 1;
    char* parsedNumerator = (char*)malloc(len);
    for(int i = 0; i < len; i++)
    {
        parsedNumerator[i] = ' ';
    }

    intToChar(dividend, parsedNumerator);
    reverseOrder(parsedNumerator, numOfDigits);

    int idx = 0;

    int resultIndex = 0;

    int temp = parsedNumerator[idx] - '0'; 

    while (temp < divisor)
    { 
       temp = (temp * 10) + (parsedNumerator[++idx] - '0'); 
    }

    if(answer.sign == '-')
    {
        result[resultIndex] = '-';
        resultIndex++;
    }

    while (numOfDigits > idx) 
    { 
        result[resultIndex] = (temp / divisor) + '0'; 
        temp = (temp % divisor) * 10 + parsedNumerator[++idx] - '0'; 
        resultIndex++;
    }

    int postDecimalRemainder = dividend % divisor;

    if(postDecimalRemainder > 0)
    {
            result[resultIndex] = '.';

            resultIndex++;

        while(postDecimalRemainder != 0 && resultIndex != len - 1)
       {
           
           postDecimalRemainder *= 10;

           int remain_part = postDecimalRemainder / divisor;
            cout << "REMAIN PART: " << remain_part + '0' << endl;
            result[resultIndex] = remain_part + '0';

           postDecimalRemainder = postDecimalRemainder % divisor;

            resultIndex++;
        }
    }
    

    result[len] = '\0';


}

//Gets the number of digits in a specific number
int getNumDigits(int numerator)
{
    int numDigits = 0;
    int temp = numerator;
    while(temp)
    {
        temp % 10;
        temp /= 10;
        numDigits++;
    }
    return numDigits;
}

//Converts a Fraction Object to an improper fraction
int convertToImproper(Fraction fraction)
{
    int newNumerator;
    newNumerator = (fraction.denominator * fraction.constant) + fraction.numerator;

    return newNumerator;
}

//Returns the absolute value of the value passed in
int abs(int v)
{
    return v * ((v < 0) * (-1) + (v > 0));
}

//toString method that prints the passed in Fraction
void printFractions(Fraction firstFraction)
{
    if (firstFraction.sign == '+')
    {
        cout << "Fraction: " << firstFraction.constant << " " << firstFraction.numerator << "/" << firstFraction.denominator << endl;
    }
    else
    {
        cout << "Fraction: " << firstFraction.sign << firstFraction.constant << " " << firstFraction.numerator << "/" << firstFraction.denominator << endl;
    }
}

//Finds the least Common multiple between the denominators passed in
int findLCM(int d1, int d2)
{
    int lcm;

    //If they're equal or d1 is bigger
    if (d1 >= d2)
        lcm = d1;
    else if (d2 > d1)
        lcm = d2;

    while (true)
    { //If both denominators are evenly divisible by the lcm value, you've reached the lowest multiple
        //for both fractions
        if ((lcm % d1 == 0) && (lcm % d2 == 0))
        {
            break;
        }
        lcm++;
    }
    return lcm;
}

//Changes the sign's of the fractions if neccessary
Fraction changeFractionSign(Fraction fraction)
{
    Fraction correctSigns;
    //if both are numerator and denominator are less than zero, abs on bottom
    if ((fraction.numerator < 0 && fraction.denominator < 0) ||
        (fraction.numerator > 0 && fraction.denominator > 0))
    {
        correctSigns.numerator = abs(fraction.numerator);
        correctSigns.denominator = abs(fraction.denominator);
        correctSigns.sign = '+';
    }
    else
    {
        //Fraction is negative...make numerator negative, denominator positive, sign for fraction negative
        correctSigns.numerator = abs(fraction.numerator);
        correctSigns.numerator *= -1;
        correctSigns.denominator = abs(fraction.denominator);
        correctSigns.sign = '-';
    }

    return correctSigns;
}

//Simpliefies the fractions if necessary
void simplifyFraction(Fraction &fraction)
{
    int greatestCommonDivisor;

    //Get the greatest commmon divisor for the fraction
    greatestCommonDivisor = gcd(fraction.numerator, fraction.denominator);

    //Divide the numerator and denominator by the GCD
    fraction.numerator = fraction.numerator / greatestCommonDivisor;
    fraction.denominator = fraction.denominator / greatestCommonDivisor;
}

//Fraction function that add's the two fractions together
Fraction addFractions(Fraction firstFraction, Fraction secondFraction)
{
    Fraction answer;
    answer.denominator = secondFraction.denominator;
    answer.numerator = firstFraction.numerator + secondFraction.numerator;

    if (answer.numerator <= -0)
    {
        answer.sign = '-';
    }
    else
        answer.sign = '+';

    return answer;
}

//Returns the greatest common divisior 
int gcd(int numerator, int denominator)
{
    if (numerator == 0)
    {
        return denominator;
    }
    return gcd(denominator % numerator, numerator);
}

//Splits the dividend up into a char[] to be used in the long divsion func
void splitDividend(char* arr, int dividend, int numOfDigits)
{
    for(int i=0; i < numOfDigits; i++, dividend /= 10)
    {
	    arr[i] = dividend % 10;
    }
}
void testAdd()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (add(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 + 0 = "0"
	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//1 + 1 = "2"
	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 + -1.5 = "-.5"
	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, -5, 10);

	//1.125 + 1.6R = "2.79"
	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 79, 100);

	//1.125 + 1.6R = "2.7916666"
	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 7916666, 10000000);

	//1.125 + 1.6R = "2.79166666666666666"
	add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "2.79166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in add()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

		if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}

			if (expectedNumerator != n)
			{
				cout << "expected numerator: " << expectedNumerator << " "
					<< "actual numerator: " << n << endl;

			}

			if (expectedDenominator != d)
			{
				cout << "expected denominator: " << expectedDenominator << " "
					<< "actual denominator: " << d << endl;
			}
		}

}


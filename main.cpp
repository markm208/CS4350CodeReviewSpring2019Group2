#include <iostream>

using namespace std;

const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;

// Function Template declarations

//characteristic functions
bool characteristic(char numString[], int& c);

//mantissa functions
bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& length);
bool mantissa(char numString[], int& numerator, int& denominator);
void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);

//Quade's
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool longDivision(int n, int d, int &cha, int &man, bool& neg);
bool createDecimalString(int cha, int man, char result[], int len, bool neg);
int firstDigit(int x, int& subtraction);

//multiply functions
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void fractionToCharArray(char* result, int numer, int denom, int maxLength, bool isNegative);
void intToCharArray(unsigned int input, char* output, int* resultLength);
void reverseArray(char* array, int arrayLength, bool hasNullTerminator);
int makePositive(int toMakePositive);
char digitToChar(int inputDigit);

// End Function Template declarations


void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(char number[]);

void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	testMath();
    
    return 0;
}


//characteristic function will rturn true or false for if the char [] was valid input
//and the converted int value is then stored in c
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
		else if (*currentAddress == ' ')
		{
			continue;
		}
		else if ((*currentAddress <= ASCII_ZERO || *currentAddress >= ASCII_NINE))
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

//This function will go through the numString and check to see if there are any
//invalid chracters, it will store where the mantissa starts in the numString, and
//it will store the length of the mantissa
bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& mantissaLength, bool& isNegative)
{
    const int decimalVal = '.';

    bool retval = true;

    //We will use current element to keep track of where we are in the numString
    int currentElement = 0;

    //When looking for the mantissa, we only want to store numbers that come after the decimal
    //therefore we will ignore everyting until we find a decimal value
    while(numString[currentElement] != decimalVal)
    {
        if(isNegative == true)
        {
            if(numString[currentElement] == '0')
            {
                isNegative = true;
            }
            else
            {
                isNegative = false;
            }
            
        }

        //If we get to \0 we know there is no matissa in numString so we will set retval to false
        if(numString[currentElement] == '\0')
        {
            retval = false;
            break;
        }
        else if(numString[currentElement] == '-')
        {
            isNegative = true;
        }

        currentElement++;
    }

    //Only enter this if statement if we did find a decimal
    if(!numString[currentElement] == '\0')
    {
        //Need to add one to the index or we will start with the decimal
        currentElement = currentElement + 1;
        startOfMantissaPosition = currentElement;

        //Counter to see how many extra zeros numString may have
        int numOfZeros = 0;

        //This while loop will go through the rest of numString and make sure
        //all the elements are in fact numbers and it will keep track of extra zeros
        while(numString[currentElement] != '\0')
        {
            //Checks to see if the element is 0-9 and if it's not set retval to false for invalid numString
            if((numString[currentElement] < ASCII_ZERO || numString[currentElement] > ASCII_NINE) && numString[currentElement] != ' ')
            {
                retval = false;
                break;
            }
            //If we find a zero we need to keep track of how many zeros we have found to make sure
            //that if it's only zeros at the end we need to cut them off the mantissa
            else if(numString[currentElement] == ASCII_ZERO || numString[currentElement] == ' ')
            {
                numOfZeros++;
            }
            //If we found a number 1-9 reset the zero count
            else
            {
                numOfZeros = 0;
            }

            //continue to next element
            currentElement++;
        }

        //The overal mantissa length will be how long numString is minus the startOfMantissaPosition
        //Also note we add numOfZeros due to the fact we do not want extra zeros to be part of our mantissaLength
        mantissaLength = currentElement - (startOfMantissaPosition + numOfZeros);

		if (mantissaLength >= 13)
		{
			retval = false;
		}
    }
    
    return retval;
}

bool mantissa(char numString[], int& numerator, int& denominator)
{
    bool retval = true;

    //This variable will be passed to numStringCheck to store the initial index of the mantissa
    int startOfMantissaPosition = 0;

    //This variable will be passed to numStringCheck to store the length of the mantissa
    int mantissaLength = 0;

    bool isNegative = false;

    //ValidateAndGetMantissaLength returns whether or not we have a valid numString so we will only
    //build the mantissa if it is valid
    if(ValidateAndGetMantissaLength(numString, startOfMantissaPosition, mantissaLength, isNegative))
    {
        retval = true;

        numerator = 0;
        
        //Denominator is base 10 so we can multiple 1 by 10 however many times to get the correct denominator
        denominator = 1;

        //We will start from the back due to the fact if the mantissa was 321 we build 321 with ints by adding
        //1 + 20 + 300 and we can do that by multiple the numerator by the current denominator
        for(int i = startOfMantissaPosition + mantissaLength - 1; i >= startOfMantissaPosition; i--)
        {
            numerator += (numString[i] - ASCII_ZERO) * denominator;

            //Go up by a base of ten for every element
            denominator = denominator * 10;
        }

        //In case the mantissa is empty, we want the denominator to be 10
        if(denominator == 1)
        {
            denominator = 10;
        }

        if(isNegative == true)
        {
            numerator = numerator * -1;
        }
    }
    else
    {
        numerator = 0;
        denominator = 10;
    }
    

    return retval;
}

void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123, 456, 1000);
	shouldConvert("    123.456", 123, 456, 1000);
	shouldConvert("123.456    ", 123, 456, 1000);
	shouldConvert("    123.456    ", 123, 456, 1000);

	shouldConvert("+123.456", 123, 456, 1000);
	shouldConvert("   +123.456", 123, 456, 1000);
	shouldConvert("+123.456   ", 123, 456, 1000);
	shouldConvert("   +123.456   ", 123, 456, 1000);

	shouldConvert("-123.456", -123, 456, 1000);
	shouldConvert("   -123.456", -123, 456, 1000);
	shouldConvert("-123.456   ", -123, 456, 1000);
	shouldConvert("    -123.456   ", -123, 456, 1000);

	shouldConvert("0.456", 0, 456, 1000);
	shouldConvert("   0.456", 0, 456, 1000); 
	shouldConvert("0.456   ", 0, 456, 1000);
	shouldConvert("   0.456   ", 0, 456, 1000);

	shouldConvert("-0.456", 0, -456, 1000);
	shouldConvert("   -0.456", 0, -456, 1000);
	shouldConvert("-0.456   ", 0, -456, 1000);
	shouldConvert("   -0.456   ", 0, -456, 1000);

	shouldConvert(".456", 0, 456, 1000);
	shouldConvert("    .456", 0, 456, 1000);
	shouldConvert(".456   ", 0, 456, 1000);
	shouldConvert("   .456   ", 0, 456, 1000);

	shouldConvert("-.456", 0, -456, 1000);
	shouldConvert("    -.456", 0, -456, 1000);
	shouldConvert("-.456   ", 0, -456, 1000);
	shouldConvert("   -.456   ", 0, -456, 1000);

	shouldConvert("123456", 123456, 0, 10);
	shouldConvert("   123456", 123456, 0, 10);
	shouldConvert("123456   ", 123456, 0, 10);
	shouldConvert("   123456   ", 123456, 0, 10);

	shouldConvert("-123456", -123456, 0, 10);
	shouldConvert("   -123456", -123456, 0, 10);
	shouldConvert("-123456   ", -123456, 0, 10);
	shouldConvert("   -123456   ", -123456, 0, 10);

	shouldConvert("000123.456", 123, 456, 1000);
	shouldConvert("123.45600000", 123, 456, 1000);
	shouldConvert("00000123.45600000", 123, 456, 1000);

	shouldConvert("-000123.456", -123, 456, 1000);
	shouldConvert("-123.45600000", -123, 456, 1000);
	shouldConvert("-00000123.45600000", -123, 456, 1000);

	shouldConvert("123.00000456", 123, 456, 100000000);
	shouldConvert("-123.00000456", -123, 456, 100000000);
}


void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
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
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}
//--
void shouldNotConvert(char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}
//--
void testMath()
{
	//add
	testAdd();
	testSubtract();
	testMultiply();
	testDivide();
}
//--
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
//--
void testSubtract()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (subtract(INT_MIN, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 - 0 = "0"
	subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 0, 10);

	//1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 5, 10);

	//1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -54, 100);

	//1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5416666, 10000000);

	//1.125 - 1.6R = "-.54166666666666666"
	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "-.54166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in subtract()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
//--
void testMultiply()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (multiply(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 * 0 = "0"
	multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//3 * 2 = "6"
	multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 6, 0, 10);

	//3 * -1.5 = "-4.5"
	multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, -4, 5, 10);

	//1.125 * 1.6R = "1.87"
	multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 87, 100);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 875, 1000);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 875, 1000);
}
//--
void testDivide()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (divide(INT_MAX, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//cannot divide by zero
	if (divide(10, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: cannot divide by zero" << endl;
	}

	//0 / 1 = "0"
	divide(0, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//6 / 3 = "2"
	divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 / -1.5 = "-.66"
	divide(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -66, 100);
	
	//1 / -1.5 = "-.6666666"
	divide(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -6666666, 10000000);
	
	//1 / -1.5 = "-.66666666666666666"
	divide(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	char expectedResult1[] = "-.66666666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult1[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in divide()." << endl
				<< "Expected: " << expectedResult1 << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}

	//1.125 / 1.6R = "0.67"
	divide(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 67, 100);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 675, 1000);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 675, 1000);
}


// "c1, n1, d1" are "characteristic, numerator, denominator" respectively.
// "c2, n2, d2" are to be multiplied against "c1, n1, d1".
// The output is stored into `result[]`, with a max-length of `len` (incl. \0
// terminator)
//
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {
    // Quick check to make sure `d1` and `d2` are ! <= 0,
    // since we can't divide by 0, and only the
    // characteristic should ever be negative

    if (d1 <= 0 || d2 <= 0) {
        return false;
    }

    // Also return false if either numerator is < 0,
    // since only characteristic can be negative.
    if (n1 < 0 || n2 < 0) {
        return false;
    }

    // `resultIsNegative` will dictate the first character of the `result`.
    // If `false`, the new characteristic will be the 0th char,
    // if `true`, the 0th char will be "-".
    bool resultIsNegative = ((c1 > 0 && c2 < 0) || (c1 < 0 && c2 > 0));

    // As `resultIsNegative` is known, we can do the remaining math much easier
    // with positive characteristic values
    c1 = makePositive(c1);
    c2 = makePositive(c2);

    // e.g. c1=2, n1=5, d1=10 will result in asLong1 = 25,
    // which is 2.5 * 10.
    // Allows us to perform non-floating point operations on
    // regularly floating point numbers.
    unsigned int asLong1 = (c1 * d1) + n1;
    unsigned int asLong2 = (c2 * d2) + n2;

    // Since `asLong1&2` essentially store a numerator,
    // to successfully multiply we can do `(numer * numer) / (denom * denom)`.
    unsigned int combinedNumer = asLong1 * asLong2;
    unsigned int combinedDenom = d1 * d2;

    fractionToCharArray(result, combinedNumer, combinedDenom, len, resultIsNegative);

    return true;
}

void fractionToCharArray(char* result, int numer, int denom, int maxLength, bool isNegative) {
    // Convert `numer` to a char[]
    char numerCharArray[32];

    int resultLength = 0;
    intToCharArray(numer, numerCharArray, &resultLength);

    // Long division algorithm
    //
    int numerIdx = 0;
    int firstStepRemainder = numerCharArray[numerIdx] - '0';
    while (firstStepRemainder < denom) {
        firstStepRemainder = (firstStepRemainder * 10) + (numerCharArray[++numerIdx] - '0');
    }

    int resultIdx = 0;
    // Add the negative if necessary, increase
    // resultIdx to stay in the correct spot
    if (isNegative) {
        result[resultIdx++] = '-';
    }

    // Before decimal
    while (resultLength > numerIdx) {
        // Write to `result`
        result[resultIdx++] = (firstStepRemainder / denom) + '0';
        // Get next digit
        firstStepRemainder = (firstStepRemainder % denom) * 10 + numerCharArray[++numerIdx] - '0';
    }

    // Add decimal if necessary
    int secondStepRemainder = numer % denom;
    if (secondStepRemainder > 0) {
        result[resultIdx++] = '.';

        secondStepRemainder *= 10;

        // After decimal
        while (secondStepRemainder > 0) {
            // Write to `result`
            result[resultIdx++] = (secondStepRemainder / denom) + '0';
            // Get next digit
            secondStepRemainder = (secondStepRemainder % denom) * 10;
        }
    }
    //
    // End Long division algorithm

    // Null terminate
    result[resultIdx] = '\0';
}

void intToCharArray(unsigned int input, char* output, int* resultLength) {
    // `currentIndex` is the position where the next digit will go
    int currentIndex = 0;

    // Iterate over `input` digit by digit (% 10),
    // until `input < 10`. At this point, just store the last digit
    // into `output`.
    while (input != 0) {
        output[currentIndex++] = digitToChar(input % 10);
        if(input >= 10){
            input /= 10;
        } else {
            output[currentIndex++] = digitToChar(input);
            input -= input;
        }
    }

    // Null terminate
    output[currentIndex] = '\0';

    // Reverse digits since we've built `output` backwards
    reverseArray(output, currentIndex + 1, true);

    // Store `resultLength`
    *resultLength = currentIndex;
}

// Reverses a `char[]` in-place
void reverseArray(char* array, int arrayLength, bool hasNullTerminator) {
    // Need to account for the null terminator, don't move that
    if (hasNullTerminator) {
        arrayLength -= 1;
    }

    // Simple in-place flip of array elements
    for (int i = 0; i < (arrayLength / 2); i++) {
        char t = array[i];
        array[i] = array[(arrayLength - 1) - i];
        array[(arrayLength - 1) - i] = t;
    }

    // No need to return since we are modifying the original `array`
}

// Will return a positive version of `toMakePositive`
int makePositive(int toMakePositive) {
    if (toMakePositive < 0) {
        toMakePositive *= -1;
    }
    return toMakePositive;
}

// Offsets `inputDigits` by char-value of '0',
// returning the ASCII value of the digit
char digitToChar(int inputDigit) {
    if (inputDigit <= 9) {
        return '0' + inputDigit;
    } else {
        // Oh no.
    }
}

/**
* c1 = characteristic 1
* n1 = numerator of mantissa 1
* d1 = denominator of mantissa 1
* c2 = characteristic 2
* n2 = numerator of mantissa 2
* d1 = denominator of mantissa 2
* result[] = where the result is stored
* len = amount of integers allowed in results array
*/

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {
	//step 1:  find common denominator by multiplying the two
	int commonD = d1 * d2;

	//step 2: match numerators based on commonD
	// this is done by multiplying the numerator by the opposite denominator
	int fixedn1 = n1 * d2;
	int fixedn2 = n2 * d1;

	//step 3: take the characteristic and multiply it by the denominator and add it to the numerator
	if (c1 != 0) {
		fixedn1 = c1 * commonD + fixedn1;
	}
	if (c2 != 0) {
		fixedn2 = c2 * commonD + fixedn2;
	}

	//step 4: subtract the fixed numerator 1 from the fixed numerator 2 since the denominators are now matching.
	int subtractedNum = fixedn1 - fixedn2;

	//step 5: fuck my life
	int cha = 0, man = 0;
	bool neg = false;
	longDivision(commonD, subtractedNum, cha, man, neg);

	//step 6: populate result
	createDecimalString(cha, man, result, len, neg);

	return false;
}

bool longDivision(int n, int d, int &cha, int &man, bool& neg) {
	
	if (d == 0) {
		return false;
	}
	neg = false;

	int dividend = d;

	if (dividend < 0) {
		dividend = dividend * -1;
		neg = true;
	}
	int digitCount = 0;
	bool onCha = true;

	do {
		//if the numerator is not equal or too big to the dividend
		if (n > dividend) {
			dividend = dividend * 10;
			//if were on characteristic
			if (onCha) {
				onCha = false;
			}
		}
		else {
			if (onCha) {
				cha = (cha * 10) + dividend / n;
			}
			else {
				if (digitCount > 8){
					return true;
				}
				digitCount = digitCount++;
				man = (man * 10) + dividend / n;
			}
			dividend = dividend % n;
		}
	} while (dividend != 0);

	return true;
}


//BUGGED: Stores numbers backwards and breaks at the completion of the program.
bool createDecimalString(int cha, int man, char result[], int len, bool neg) {
	if (cha == 0 && man == 0) {
		return false;
	}

	int oCha = cha;
	char temp = 'a';
	bool decimal = false;
	bool lastChar = false;
	bool done = false;
	int last = 0;
	int subtraction;

	for (int i = 0; i < len - 1; i++) {
		if (man == 0 && cha == 0) {
			result[i] = '\0';
			return true;
		}
		if (done == true) {
			break;
		}
		if (i == 0) {
			if (neg == true) {
				result[i] = '-';
				i = 1;
			}
		}
		if (cha > 0) {
			if (cha >= 10) {
				result[i] = cha % 10 + 48;
				cha = cha / 10;

			}
			//were below 10
			else {
				result[i] = cha + 48;
				cha = cha / 10;
			}
			if (cha == 0) {
				lastChar = true;
			}
		}
		else {
			if (lastChar || oCha == 0) {
				result[i] = '.';
				lastChar = false;
				decimal = true;
				oCha = 1;
			}
			else if (man >= 10) {
				if (!decimal) {
					result[i] = firstDigit(man, subtraction) + 48;
					man = man - subtraction;
				}
				else {
					decimal = false;
					result[i] = firstDigit(man, subtraction) + 48;
					man = man - subtraction;
				}
			}
			else {
				if (!decimal) {
					result[i] = man + 48;
				}
				else {
					decimal = false;
					result[i] = man + 48;
				}
				if (man % man == 0) {
					done = true;
				}
				else {
					man = man / man;
				}
			}
		}
		last = i + 1;
	}

	result[last] = '\0';

	return true;
}


int firstDigit(int x, int& subtraction) {
	int count = 1;
	while (x > 9) {
		x /= 10;
		count *= 10;
	}
	subtraction = x * count;
	return x;
}


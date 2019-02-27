#include <iostream> //do not include anything other than this

using namespace std;

const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;

bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& length);
bool mantissa(char numString[], int& numerator, int& denominator);

int main()
{
    char numString[] = "-4.120000";
    int numerator = 0;
    int denominator = 0;
    bool retval = mantissa(numString, numerator, denominator);
    cout << numerator << endl;
    cout << denominator << endl;
    cout << retval << endl;
    return 0;
}

//This function will go through the numString and check to see if there are any
//invalid chracters, it will store where the mantissa starts in the numString, and
//it will store the length of the mantissa
bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& mantissaLength)
{
    const int decimalVal = '.';

    bool retval = true;

    //We will use current element to keep track of where we are in the numString
    int currentElement = 0;

    //When looking for the mantissa, we only want to store numbers that come after the decimal
    //therefore we will ignore everyting until we find a decimal value
    while(numString[currentElement] != decimalVal)
    {
        //If we get to \0 we know there is no matissa in numString so we will set retval to false
        if(numString[currentElement] == '\0')
        {
            retval = false;
            break;
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
            if(numString[currentElement] < ASCII_ZERO || numString[currentElement] > ASCII_NINE)
            {
                retval = false;
                break;
            }
            //If we find a zero we need to keep track of how many zeros we have found to make sure
            //that if it's only zeros at the end we need to cut them off the mantissa
            else if(numString[currentElement] == ASCII_ZERO)
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
    }
    
    return retval;
}

bool mantissa(char numString[], int& numerator, int& denominator)
{
    bool retval = false;

    //This variable will be passed to numStringCheck to store the initial index of the mantissa
    int startOfMantissaPosition = 0;

    //This variable will be passed to numStringCheck to store the length of the mantissa
    int mantissaLength = 0;

    //ValidateAndGetMantissaLength returns whether or not we have a valid numString so we will only
    //build the mantissa if it is valid
    if(ValidateAndGetMantissaLength(numString, startOfMantissaPosition, mantissaLength))
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
    }

    return retval;
}
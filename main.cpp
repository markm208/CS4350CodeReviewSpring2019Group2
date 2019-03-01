#include <iostream> //do not include anything other than this

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
//Finds the least Common multiple between the denominators passed in
int findLCM(int d1, int d2);
//Converts a Fraction Object to an improper fraction
int convertToImproper(Fraction fraction); 
//Returns the absolute value of the value passed in
int abs(int num);
//toString method that prints the passed in Fraction
void printFractions(Fraction firstFraction);
//Returns the greatest common divisior 
int gcd(int, int);
//Gets the number of digits in a specific number
int getNumDigits(int numerator);
//Long division Function
void longDivision(Fraction &answer, char result[], int len);
//Splits the dividend up into a char[] to be used in the long divsion func
void splitDividend(int numerator, char dividend[],int sizeOfDividend);
//Fraction function that add's the two fractions together
Fraction addFractions(Fraction firstFraction, Fraction secondFraction);
//Changes the sign's of the fractions if neccessary
Fraction changeSigns(Fraction fraction);
//Simpliefies the fractions if necessary
void simplifyFraction(Fraction &fraction);
//Free's any pointers allocated to prevent memory leaks
void freeAndNull(void **ptr);

int main()
{
    /*
    Long divsion doesn't work
    No result returned
    */
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    cout << "******************" << endl;
    c1 = 1;
    n1 = 2;
    d1 = 6;

    c2 = 0;
    n2 = 5;
    d2 = 1;

    add(c1, n1, d1, c2, n2, d2, answer, 10);
    cout << endl;

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
    if (d1 == 0 || d2 == 0)
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
    firstFraction = changeSigns(firstFraction);
    secondFraction = changeSigns(secondFraction);
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
    int sizeCheck = getNumDigits(answer.numerator);
    //Size check for result char array
    if(sizeCheck < len)
    {
        return false;
    }
    longDivision(answer, result, len);

    return retVal;
}
void longDivision(Fraction &answer, char result[], int len)
{   
    
    //Doesn't work
    int size;
    size = getNumDigits(answer.numerator);
    //Need one extra for padding 
    size++;
    char * dividend = (char*) malloc(size);

    int divisor;
    
    divisor = answer.denominator;
    splitDividend(answer.numerator, dividend, size);

}

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
int convertToImproper(Fraction fraction)
{
    int newNumerator;
    newNumerator = (fraction.denominator * fraction.constant) + fraction.numerator;

    return newNumerator;
}
int abs(int v)
{
    return v * ((v < 0) * (-1) + (v > 0));
}
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
int findLCM(int d1, int d2)
{
    int lcm;

    //If they're equal or d1 is bigger
    if ((d1 > d2) || (d1 == d2))
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
Fraction changeSigns(Fraction fraction)
{
    printFractions(fraction);
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
void simplifyFraction(Fraction &fraction)
{
    int greatestCommonDivisor;

    //Get the greatest commmon divisor for the fraction
    greatestCommonDivisor = gcd(fraction.numerator, fraction.denominator);

    //Divide the numerator and denominator by the GCD
    fraction.numerator = fraction.numerator / greatestCommonDivisor;
    fraction.denominator = fraction.denominator / greatestCommonDivisor;
}
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
int gcd(int numerator, int denominator)
{
    if (numerator == 0)
    {
        return denominator;
    }
    return gcd(denominator % numerator, numerator);
}
void splitDividend(int numerator, char dividend[], int sizeOfDividend)
{
    sprintf(dividend, "%ld", numerator);
}

void freeAndNull(void **ptr)
{
   free(*ptr);
   *ptr = NULL;
}
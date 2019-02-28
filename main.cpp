#include <iostream> //do not include anything other than this

using namespace std;

struct Fraction{
    char sign;
    int constant;
    int numerator;
    int denominator;
};

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int findLCM(int d1, int d2);
bool isNegative(int c, int n, int d);
int convertToImproper(Fraction fraction); //--> Would probably have to return a c string.... 12,10 where 12 is the numerator/10 is denominator
void freeAndNull(void **ptr);
int abs(int num);
void printFractions(Fraction firstFraction);
Fraction addFractions(Fraction firstFraction, Fraction secondFraction); 
Fraction changeSigns(Fraction fraction);


int main()
{

    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2; 
    
    cout << "1******************" << endl;
    c1 = 1;
    n1 = 2;
    d1 = 6;
 
    c2 = 0;
    n2 = 5;
    d2 = 1; 

    add(c1,n1,d1,c2,n2,d2,answer,10);
    cout << endl;
    cout << "2*****************" << endl;

    c1 = -1;
    n1 = 2;
    d1 = 6;
 
    c2 = 0;
    n2 = 5;
    d2 = 1; 

    add(c1,n1,d1,c2,n2,d2,answer,10);
    cout << endl;
    cout << "3*****************" << endl;
    c1 = 1;
    n1 = 2;
    d1 = 6;
 
    c2 = -0;
    n2 = -5;
    d2 = 1; 

    add(c1,n1,d1,c2,n2,d2,answer,10);
    cout << endl;
    cout << "4*****************" << endl;

    c1 = -1;
    n1 = 2;
    d1 = 6;
 
    c2 = 0;
    n2 = -5;
    d2 = 1; 

    add(c1,n1,d1,c2,n2,d2,answer,10);
    cout << endl;
    cout << "5*****************" << endl;

    return 0;
}

//new functions go here
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //Local variables
    Fraction firstFraction;
    Fraction secondFraction;
    Fraction answer;

    bool retVal;
    int lcm;
    if(d1 == 0 || d2 == 0)
    {
        retVal = false;
        return retVal;
    }

    firstFraction.constant = c1;
    firstFraction.numerator = n1;
    firstFraction.denominator = d1;

    secondFraction.constant = c2;
    secondFraction.numerator = n2;
    secondFraction.denominator = d2;
    

    //AT THIS POINT, EACH INDIVIDUAL FRACTION HAS THEIR CORRECT SIGN and IS PARSED

    //Convert to improper
   firstFraction.numerator = convertToImproper(firstFraction);
   firstFraction.constant = '\0';
   
   secondFraction.numerator = convertToImproper(secondFraction);
   secondFraction.constant = '\0';

   //Then get the sign
   firstFraction = changeSigns(firstFraction);
   secondFraction = changeSigns(secondFraction);

    cout << endl;
    cout << "SIGNS SHOULD BE CORRECT" << endl;
    printFractions(firstFraction);
    printFractions(secondFraction);
    cout << endl;

    lcm = findLCM(d1,d2);
    //What to multiply the fraction by.

    if(firstFraction.denominator != lcm)
    {
        int multiplier = lcm/firstFraction.denominator;
    
        firstFraction.denominator = firstFraction.denominator * multiplier;
        firstFraction.numerator = firstFraction.numerator * multiplier;
    }

    if(secondFraction.denominator != lcm)
    {
        int multiplier = lcm/secondFraction.denominator;

        secondFraction.denominator = secondFraction.denominator * multiplier;
        secondFraction.numerator = secondFraction.numerator * multiplier;
    }
    //All fractions should now be imporoper and have correct LCM
    cout << endl;
    printFractions(firstFraction);
    printFractions(secondFraction);
    cout << endl;

    answer = addFractions(firstFraction, secondFraction);
    //Add
    cout << endl;
    printFractions(answer);
    cout << endl;
    //Mod final result

    //Long division

    //Fill result[]




    //Buffers used for helper functions
    char *improperConversionPtr = (char *)malloc(len);

 //   convertToImproper(improperConversionPtr, c1, n1, d1, len);

    freeAndNull((void**)improperConversionPtr);

    return retVal;
}
int convertToImproper(Fraction fraction) //--> Would probably have to return a c string.... 12,10 where 12 is the numerator/10 is denominator
{
    int newNumerator;
    newNumerator =  (fraction.denominator * fraction.constant) + fraction.numerator;

    return newNumerator;
}
void freeAndNull(void **ptr)
{
   free(*ptr);
   *ptr = NULL;
}
int abs(int v) 
{
  return v * ( (v<0) * (-1) + (v>0));
  // simpler: v * ((v>0) - (v<0))   thanks Jens
}
void printFractions(Fraction firstFraction)
{
    if(firstFraction.sign == '+')
    {
        cout << "Fraction: " << firstFraction.constant << " " << firstFraction.numerator << "/" << firstFraction.denominator << endl;
        //print without
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
    if((d1 > d2) || (d1 == d2)) 
        lcm = d1;
    else if(d2 > d1)
        lcm = d2;

    //Very slow first implementation
    //Will improve runtime
    while(true)
    {   //If both denominators are evenly divisible by the lcm value, you've reached the lowest multiple 
        //for both fractions
        if((lcm % d1 == 0) && (lcm % d2 == 0))
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
    if((fraction.numerator < 0 && fraction.denominator < 0) ||
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
Fraction addFractions(Fraction firstFraction, Fraction secondFraction)
{
    Fraction answer; 
    answer.denominator = secondFraction.denominator;
    answer.numerator = firstFraction.numerator + secondFraction.numerator;

    if(answer.numerator <= -0)
    {
        answer.sign = '-';
    }
    else
        answer.sign = '+';

    return answer;

}
#include <iostream> //do not include anything other than this

using namespace std;


bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int findLCM(int d1, int d2);

int main()
{

    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2; 
    

    c1 = 1;
    n1 = 1;
    d1 = 2;
 
    c2 = 2;
    n2 = 2;
    d2 = 3; 

    add(c1,n1,d1,c2,n2,d2,answer,10);

    c1 = -5;
    n1 = 6;
    d1 = 360;
 
    c2 = 2;
    n2 = 2;
    d2 = 245; 

    add(c1,n1,d1,c2,n2,d2,answer,10);

    c1 = -5;
    n1 = 6;
    d1 = 7;
 
    c2 = 2;
    n2 = 2;
    d2 = 1246; 

    add(c1,n1,d1,c2,n2,d2,answer,10);


    return 0;
 
}

//new functions go here
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    bool retVal;
    int lcm;



    //Check should check to see if chara

    lcm = findLCM(d1,d2);



    return retVal;
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

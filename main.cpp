#include <iostream>
using namespace std;
//a little preface to the methods used
bool divide(int char1, int numerator, int denomerator1, int char2, int numerator2, int denomerator2, char result[], int len);
bool longdivision(int n, int d, int &c, int &m, int &limit);


int main() {
	char result[8];
	divide(2, 1, 2, 4, 2, 3, result, 8);

	for (int i = 0; i < sizeof(result); i++)
	{
		cout << result[i];
	}
	system("pause");
	return 0;
}



bool divide(int char1, int numerator, int denomerator1, int char2, int numerator2, int denomerator2, char result[], int len)
{

	//can't divide by zero
	if (denomerator2 <= 0 || denomerator1 <= 0 || numerator < 0 || numerator2 < 0)
	{
		return false;
	}
	bool negative = false;
	if (char1 < 0)
	{
		if (!numerator)
		{
			char1 = -char1;
		}
		else
		{
			char1 = -char1 - 1;
			numerator = denomerator1 - numerator;
		}
		negative = !negative;
	}
	if (char2 < 0)
	{
		if (!numerator2)
		{
			char2 = -char2;
		}
		else
		{
			char2 = -char2 - 1;
			numerator2 = denomerator2 - numerator2;
		}
		negative = !negative;
	}

	//usinng revised variables to make a single numerator and denominator for both entries by  division
	int num1;
	num1 = (char1*denomerator1) + numerator;
	int num2;
	num2 = (char2*denomerator2) + numerator2;

	//now that the fractions are set up, we divide by multiplying numerator with denomerator2 and numerator2 and denomerator1
	int finalnum;
	int finalden;
	finalnum = num1 * denomerator2;
	finalden = num2 * denomerator1;
	//bring the fraction back into our decimal form
	// if num is greater than equal to denom, subtract dom from num and increase quotient 
	int predecimal = 0;
	int postdecimal = 0;
	//now to divide the final product
	int limit = len - 1;
	longdivision(finalnum, finalden, predecimal, postdecimal, limit);
	if (!longdivision(finalnum, finalden, predecimal, postdecimal, limit))
	{
		cout << "Divide Failed" << endl;
		return false;
	}
	else {
		//after that is complete we insert into the result array, however in reverse order
		int iter = 0;
		int charTemp;
		int i = postdecimal;
		while (i != 0) {
			result[iter] = i % 10;
			i = i / 10;
			iter++;
		}
		result[iter] = '.';
		i = predecimal;
		while (i != 0) {
			result[iter] = i % 10;
			i = i / 10;
			iter++;
		}

		//this probably could be in a helper like the above.
		for (int j = 0; j < (len / 2); j++) {
			char t = result[i];
			result[j] = result[(len - 1) - i];
			result[(len - 1) - i] = t;
		}

		return true;
	}
}
bool longdivision(int n, int d, int &c, int &m, int &limit)
{
	//I know there is probably a better way but i use this array to find the limit of decimal places based on the character before
	int multipleOf[] = { 1, 10, 100, 1000 , 10000, 10000 };

	if (n%d == 0)
	{
		c = n / d;
		m = 0;
		return true;
	}

	int quotient = 0;
	while (n >= d)
	{

		n = n - d;
		quotient++;
		for (int i = 0; i < sizeof(multipleOf); i++)
		{
			if (quotient == multipleOf[i])
			{
				limit--;
			}
		}
	}
	c = quotient;

	//now we are left with the smaller numerator


	while ( limit < 1)
	{
		
		if (n == 0)
		{
			return true;
		}
		if (d > n)
		{
			//if the denominator is we need to multiply by 10 
			d = d * 10;
			m = m * 10;

		}
		else {
			int num = 0;
			while (n >= d)
			{
				n = n - d;
				num++;
			}
			m = m + num;
			limit--;
		
		}
	}
	return true;

}

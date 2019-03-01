#include <iostream>
using namespace std;
//a little preface to the methods used
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool longdivision(int n, int d, int &c, int &m, int &limit);


int main() {
	char result[8];
	divide(2, 1, 2, 4, 2, 3, result, 8);
	cout << "hello?";
	for (int i = 0; i < sizeof(result); i++)
	{
		cout << result[i];
	}
	system("pause");
	return 0;
}



bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

	//can't divide by zero, so this is checking for user misinput. also assuming the fraction shouln't be negative
	if (d2 <=0 || d1 <= 0 || n1 < 0 || n2 < 0)
	{
		return false;
	}
	


	//we are now gonna make our revised variables to make a single numerator and denominator for both entries by simple fraction division
	int num1;
	num1 = (c1*d1) + n1;
	int num2;
	num2 = (c2*d2) + n2;

	//now that the fun fractions are set up, we divide by multiplying n1 with d2 and n2 and d1
	//and create some result variables.
	int finalnum;
	int finalden;
	finalnum = num1 * d2;
	finalden = num2 * d1;
	cout << finalnum << finalden;
	//splendid! now we just need to use more funky integer arithmetic to bring the fraction back into our fun decimal avenue
	// if num is greater than equal to denom, subtract dom from num and increase quotient 
	int predecimal=0;
	int postdecimal = 0;;
	//now to divide the final product
	int limit = len - 1;
	
	longdivision(finalnum, finalden, predecimal, postdecimal, limit);
	cout << predecimal << postdecimal;
	//after that is complete we insert into the result array, however in reverse order
	int iter = 0;
	int charTemp;
	int i = postdecimal;
	while (i != 0) {
		result[iter] = i % 10;
		i = i / 10;
		iter++;
	}
	result[iter] = ',';
	i = predecimal;
	while (i != 0) {
		result[iter] = i % 10;
		i = i / 10;
		iter++;
	}

	//this probably could be in a helper like the above. we shall see if i have time
	for (int j = 0; j < (len / 2); i++) {
		char t = result[i];
		result[j] = result[(len - 1) - i];
		result[(len - 1) - i] = t;
	}

	return true;

}
bool longdivision(int n, int d, int &c, int &m, int &limit)
{
	//I know there is probably a better way but i use this array to find the limit of decimal places based on the character before
	int multipleOf[] = { 1, 10, 100, 1000 , 10000, 10000 };

	if (n%d == 0)
	{
		c = n/d;
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
		//this part was quite rushed
		//"itsover" refers to the division process status
		bool itsover = false;
		while (!itsover || limit < 1)
		{
			cout << n << "DSAFFSADFSAEDF";
			if (n == 0)
			{
				itsover = true;
			}
			if (d > n)
			{
				//if the denominator we need to multiply by 10 to keep chuggin
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
				//cout << m;
			}
		}
		return true;

}

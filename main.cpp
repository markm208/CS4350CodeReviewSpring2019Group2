
#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool longDivision(int n, int d, int &cha, int &man);
bool createDecimalString(int cha, int man, char result[], int len);

int main()
{
	char result[10];

	bool yeet = subtract(0, 3, 4, 0, 3, 7, result, 10);

	system("pause");
	return 0;
}

//new functions go here


/**
* c1 = characteristic 1
* n1 = numerator of mantissa 1
* d1 = denominator of mantissa 2
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
	longDivision(commonD, subtractedNum, cha, man);

	//step 6: populate result
	createDecimalString(cha, man, result, len);

	return false;
}

bool longDivision(int n, int d, int &cha, int &man) {
	
	if (d == 0) {
		return false;
	}

	int dividend = d;
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
bool createDecimalString(int cha, int man, char result[], int len) {
	if (cha == 0 && man == 0) {
		return false;
	}

	int oCha = cha;
	char temp = 'a';
	bool decimal = false;
	bool lastChar = false;

	for (int i = 0; i < len; i++) {
		if (man == 0 && cha == 0) {
			result[i] = '\n';
			return true;
		}
		if (cha > 0) {
			if (cha >= 10) {
				result[i] = cha % 10 + 48;
				cha = cha / 10;
				if (cha == 0) {
					lastChar = true;
				}
			}
			else {
				result[i] = cha + 48;
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
					result[i] = result[i - 1];
					result[i - 1] = man % 10 + 48; ;
				}
				else {
					decimal = false;
					result[i] = man % 10;
				}
				man = man / 10;
			}
			else {
				if (!decimal) {
					result[i] = result[i - 1];
					result[i - 1] = man + 48;
				}
				else {
					decimal = false;
					result[i] = man + 48;
				}
				man = man / man;
			}
		}
	}

	result[len] = '\n';

	return true;
}
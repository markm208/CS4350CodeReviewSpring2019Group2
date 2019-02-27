#include <iostream>  //do not include anything other than this

using namespace std;

// Function Template declarations
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool longNumerAndDenomToCharArray(char result[],
                                  unsigned long numer,
                                  unsigned long denom,
                                  int maxLength,
                                  bool isNegative);
int makePositive(int toStrip);
static const int ASCII_ZERO = 48;
// End Function Template declarations

int main() {
    //
    // Test Code
    //

    int c1 = 2;
    int n1 = 5;
    int d1 = 8;

    int c2 = 8;
    int n2 = 42;
    int d2 = 100;

    // 17,682 / 800 ==
    // 2.625 * 8.42 == 22.1025

    char* testOut = new char[100];

    multiply(c1, n1, d1, c2, n2, d2, testOut, 100);

    for (int i = 0; testOut[i] != '\0'; i++) {
        cout << testOut[i] << " ";
    }
    cout << endl;

    // system("pause");
    //
    // End Test Code
    //

    return 0;
}

// new functions go here

// "c1, n1, d1" are "characteristic, numerator, denominator" respectively.
// "c2, n2, d2" are to be multiplied against "c1, n1, d1".
// The output is stored into `result[]`, with a max-length of `len` (incl. \0 terminator)
//
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {
    // Quick check to make sure `d1` and `d2` are != 0,
    // since we can't divide by 0
    if (d1 == 0 || d2 == 0) {
        return false;
    }

    // `resultIsNegative` will dictate the first character of the `result`.
    // If `false`, the new characteristic will be the 0th char,
    // if `true`, the 0th char will be "-".
    bool resultIsNegative = (c1 > 0 && c2 < 0) || (c1 > 0 && c2 < 0);

    // As `resultIsNegative` is known, we can do the remaining math much easier with
    // positive characteristic values
    c1 = makePositive(c1);
    c2 = makePositive(c2);

    // e.g. c1=2, n1=5, d1=10 will result in asLong1 = 25,
    // which is 2.5 * 10.
    // Allows us to perform non-floating point operations on
    // regularly floating point numbers.
    unsigned long asLong1 = (c1 * d1) + n1;
    unsigned long asLong2 = (c2 * d2) + n2;

    // Since `asLong1/2` essentially store a numerator,
    // to successfully multiply we can do `(numer * numer) / (denom * denom)`.
    unsigned long combinedNumer = asLong1 * asLong2;
    unsigned long combinedDenom = d1 * d2;

    longNumerAndDenomToCharArray(result, combinedNumer, combinedDenom, len, resultIsNegative);

    return true;
}

bool longNumerAndDenomToCharArray(char result[],
                                  unsigned long numer,
                                  unsigned long denom,
                                  int maxLength,
                                  bool isNegative) {
    int insertIndex = 0;

    cout << numer << " | " << denom << endl;

    if (isNegative) {
        result[insertIndex++] = '-';
    }

    result[insertIndex] = '\0';

    return true;
}

// Will return a positive version of `toStrip`
int makePositive(int toStrip) {
    if (0 > toStrip) {
        toStrip = toStrip * -1;
    }
    return toStrip;
}

char numToChar(int input){
    return ASCII_ZERO + input;
}
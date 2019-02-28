#include <iostream>  //do not include anything other than this

using namespace std;

static const int ASCII_ZERO = 48;

// Function Template declarations
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void fractionToCharArray(char* result, int numer, int denom, int maxLength, bool isNegative);
void intToCharArray(unsigned int input, char* output, int maxLength, int* resultLength);

void reverseArray(char* array, int arrayLength, bool hasNullTerminator);
int makePositive(int toStrip);
char digitToChar(int inputDigit);
// End Function Template declarations

int main() {
    //
    // Test Code
    //

    int c1 = -2;
    int n1 = 5;
    int d1 = 8;

    int c2 = 8;
    int n2 = 42;
    int d2 = 100;

    // 17,682 / 800 ==
    // 2.625 * 8.42 == 22.1025

    char* testOut = new char[100];

    multiply(c1, n1, d1, c2, n2, d2, testOut, 100);

    // TEST PRINT
    cout << "main:: ";
    int i = 0;
    char c = testOut[i++];
    while (c != '\0') {
        cout << c;
        c = testOut[i++];
    }
    cout << endl;
    // END TEST PRINT

    //
    // End Test Code
    //

    return 0;
}

// new functions go here

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
    // since characteristic shouldn't be negative ever.
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

    // Check for int overflow, return false
    // if (INT32_MAX / asLong1 > asLong2) {
    //     return false;
    // }

    // Since `asLong1&2` essentially store a numerator,
    // to successfully multiply we can do `(numer * numer) / (denom * denom)`.
    unsigned int combinedNumer = asLong1 * asLong2;
    unsigned int combinedDenom = d1 * d2;

    fractionToCharArray(result, combinedNumer, combinedDenom, len, resultIsNegative);

    return true;
}

void fractionToCharArray(char* result, int numer, int denom, int maxLength, bool isNegative) {
    // Convert `numer` to a char[]
    char numerCharArray[2048];
    int resultLength = 0;
    intToCharArray(numer, numerCharArray, maxLength, &resultLength);

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

void intToCharArray(unsigned int input, char* output, int maxLength, int* resultLength) {
    int currentIndex = 0;
    while (input && currentIndex < maxLength - 1) {
        output[currentIndex++] = digitToChar(input % 10);
        input /= 10;
    }

    // Null terminate
    output[currentIndex] = '\0';
    // Reverse digits
    reverseArray(output, currentIndex + 1, true);

    // Store `resultLength`
    *resultLength = currentIndex;
}

// Reverses a `char[]` in-place
void reverseArray(char* array, int arrayLength, bool hasNullTerminator) {
    if (hasNullTerminator) {
        arrayLength -= 1;
    }
    for (int i = 0; i < (arrayLength / 2); i++) {
        char t = array[i];
        array[i] = array[(arrayLength - 1) - i];
        array[(arrayLength - 1) - i] = t;
    }
}

// Will return a positive version of `toStrip`
int makePositive(int toStrip) {
    if (0 > toStrip) {
        toStrip = toStrip * -1;
    }
    return toStrip;
}

// Offsets `inputDigits` by char-value of '0'
char digitToChar(int inputDigit) {
    if (inputDigit <= 9) {
        return ASCII_ZERO + inputDigit;
    } else {
        // Oh no.
    }
}
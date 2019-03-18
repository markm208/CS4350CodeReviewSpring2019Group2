#include <iostream>  //do not include anything other than this

using namespace std;

// Function Template declarations
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void fractionToCharArray(char* result, int numer, int denom, int maxLength, bool isNegative);
void intToCharArray(unsigned int input, char* output, int* resultLength);

void reverseArray(char* array, int arrayLength, bool hasNullTerminator);
int makePositive(int toMakePositive);
char digitToChar(int inputDigit);
// End Function Template declarations

int main() {
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
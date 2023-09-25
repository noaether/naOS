int pow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

double calculateNthDigitOfPi(int n) {
    double pi = 0.0;

    for (int i = 0; i < n; i++) {
        double term = 1.0 / (2 * i + 1);
        if (i % 2 == 0) {
            pi += term;
        } else {
            pi -= term;
        }
    }

    pi *= 4.0;

    // Now pi contains an approximation of π up to the nth term of the series
    // To get the nth digit, we can multiply pi by 10^n and take the integer part
    //int nthDigit = (int)(pi * pow(10, n)) % 10;

    return pi;
}
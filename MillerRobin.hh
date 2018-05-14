bool MillerRabinTest(const BigInteger &num, const BigInteger &a) {
    BigInteger temp = num - 1;
    int r = 0;
    while (temp % 2 == 0) {
        r++;
        temp /= 2;
    }
    BigInteger k = power(a, temp, num);
    if (k == 1)
        return true;
    for (int j = 0; j < r; j++, k = k * k % num)
        if (k == num - 1)
            return true;
    return false;
}

bool IsPrime(const BigInteger &num) {
    int prime[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (auto i:prime)
        if (i==num) return true;
    for (auto i:prime)
        if (!MillerRabinTest(num,i)) return false;
    return true;
}

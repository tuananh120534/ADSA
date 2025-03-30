#include <bits/stdc++.h>
using namespace std;
long long baseToDecimal(const string &num, int base) {
    long long result = 0;
    for (char digit : num) {
        result = result * base + (digit - '0');
    }
    return result;
}
string decimalToBase(long long num, int base) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) {
        result += (num % base) + '0';
        num /= base;
    }
    reverse(result.begin(), result.end());
    return result;
}
string schoolAddition(const string &num1, const string &num2, int base) {
    long long a = baseToDecimal(num1, base);
    long long b = baseToDecimal(num2, base);
    return decimalToBase(a + b, base);
}
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) return x * y;
    int n = max(to_string(x).length(), to_string(y).length());
    int m = n / 2;
    long long high1 = x / pow(10, m);
    long long low1 = x % (long long)pow(10, m);
    long long high2 = y / pow(10, m);
    long long low2 = y % (long long)pow(10, m);
    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba(low1 + high1, low2 + high2);
    long long z2 = karatsuba(high1, high2);
    return z2 * pow(10, 2 * m) + (z1 - z2 - z0) * pow(10, m) + z0;
}
string karatsubaMultiplication(const string &num1, const string &num2, int base) {
    long long a = baseToDecimal(num1, base);
    long long b = baseToDecimal(num2, base);
    return decimalToBase(karatsuba(a, b), base);
}
string integerDivision(const string &num1, const string &num2, int base, bool isPostgrad) {
    if (!isPostgrad) return "0";
    long long a = baseToDecimal(num1, base);
    long long b = baseToDecimal(num2, base);
    return decimalToBase(a / b, base);
}
int main() {
    string I1, I2;
    int B;
    cin >> I1 >> I2 >> B;
    bool isPostgrad = false;
    cout << schoolAddition(I1, I2, B) << " "
         << karatsubaMultiplication(I1, I2, B) << " "
         << integerDivision(I1, I2, B, isPostgrad) << endl;
    return 0;
}
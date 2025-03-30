#include <iostream>
#include <string>
#include <algorithm>
#include<cmath>
using namespace std;



string addMethod(string num1, string num2, int base) {
    int carry = 0;
    string result = "";
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result += to_string(sum % base);
        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    return result;
}

string multiplyMethod(string num1, string num2, int base) {
    int n = num1.size();
    int m = num2.size();
    string product(n + m, '0');
    for (int i = n - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = m - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0') + (product[i + j + 1] - '0') + carry;
            carry = mul / base;
            product[i + j + 1] = (mul % base) + '0';
        }
        product[i] += carry;
    }
    if (product[0] == '0') {
        product.erase(product.begin());
    }

    return product;
}



string divideMethod(string num1, string num2, int base) {
    return "0";
}


int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    string sum = addMethod(num1, num2, base);
    string product = multiplyMethod(num1, num2, base);
    string ratio = divideMethod(num1, num2, base);
    cout << sum << " " << product << " " << ratio << endl;
    return 0;
}
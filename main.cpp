#include <bits/stdc++.h>
using namespace std;

string addSchoolMethod(string num1, string num2, int base) {
    int carry = 0;
    string result = "";
    int len1 = num1.size(), len2 = num2.size();
    int maxLength = max(len1, len2);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    while ((int)num1.size() < maxLength) num1 += "0";
    while ((int)num2.size() < maxLength) num2 += "0";
    
    
    for (int i = 0; i < maxLength; i++) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result += (sum % base) + '0';
    }
    if (carry) result += (carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

string karatsubaMultiply(string num1, string num2, int base) {
    int len1 = num1.size(), len2 = num2.size();
    if (len1 == 1 && len2 == 1)
        return to_string((num1[0] - '0') * (num2[0] - '0'));
    
    int half = max(len1, len2) / 2;
    string high1 = num1.substr(0, len1 - half);
    string low1 = num1.substr(len1 - half);
    string high2 = num2.substr(0, len2 - half);
    string low2 = num2.substr(len2 - half);
    
    string z0 = karatsubaMultiply(low1, low2, base);
    string z1 = karatsubaMultiply(to_string(stoi(low1) + stoi(high1)), to_string(stoi(low2) + stoi(high2)), base);
    string z2 = karatsubaMultiply(high1, high2, base);
    
    string result = to_string(stoi(z2) * pow(base, 2 * half) + (stoi(z1) - stoi(z2) - stoi(z0)) * pow(base, half) + stoi(z0));
    return result;
}

string convertToBase(int num, int base) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) {
        result += (num % base) + '0';
        num /= base;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    
    string sumResult = addSchoolMethod(num1, num2, base);
    string productResult = karatsubaMultiply(num1, num2, base);
    string divisionResult = "0";
    
    cout << sumResult << " " << productResult << " " << divisionResult << endl;
    return 0;
}
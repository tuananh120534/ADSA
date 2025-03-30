#include <bits/stdc++.h>
using namespace std;

string addMethod(string num1, string num2, int base) {
    int carry = 0;
    string result = "";
    int length1 = num1.size(), length2 = num2.size();
    int maxLength = max(length1, length2);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    
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

string multiplyMethod(string num1, string num2, int base) {
    int length1 = num1.size(), length2 = num2.size();
    if (length1 == 1 && length2 == 1)
        return to_string((num1[0] - '0') * (num2[0] - '0'));
    
    int halfLength = max(length1, length2) / 2;
    string highPart1 = num1.substr(0, length1 - halfLength);
    string lowPart1 = num1.substr(length1 - halfLength);
    string highPart2 = num2.substr(0, length2 - halfLength);
    string lowPart2 = num2.substr(length2 - halfLength);
    
    string z0 = multiplyMethod(lowPart1, lowPart2, base);
    string z1 = multiplyMethod(to_string(stoi(lowPart1) + stoi(highPart1)), to_string(stoi(lowPart2) + stoi(highPart2)), base);
    string z2 = multiplyMethod(highPart1, highPart2, base);
    
    string productResult = to_string(stoi(z2) * pow(base, 2 * halfLength) + (stoi(z1) - stoi(z2) - stoi(z0)) * pow(base, halfLength) + stoi(z0));
    return productResult;
}

string divideMethod(string num1, string num2, int base) {
    return "0";
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    
    string sumOutput = addMethod(num1, num2, base);
    string productOutput = multiplyMethod(num1, num2, base);
    string divisionOutput = divideMethod(num1, num2, base);
    
    cout << sumOutput << " " << productOutput << " " << divisionOutput << endl;
    return 0;
}

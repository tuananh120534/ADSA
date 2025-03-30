#include <bits/stdc++.h>
using namespace std;

string schoolAddition(string firstNumber, string secondNumber, int base) {
    int carry = 0;
    string sumResult = "";
    int length1 = firstNumber.size(), length2 = secondNumber.size();
    int maxLength = max(length1, length2);
    reverse(firstNumber.begin(), firstNumber.end());
    reverse(secondNumber.begin(), secondNumber.end());
    
    for (int i = 0; i < maxLength; i++) {
        int digit1 = firstNumber[i] - '0';
        int digit2 = secondNumber[i] - '0';
        int total = digit1 + digit2 + carry;
        carry = total / base;
        sumResult += (total % base) + '0';
    }
    if (carry) sumResult += (carry + '0');
    reverse(sumResult.begin(), sumResult.end());
    return sumResult;
}

string karatsubaMultiplication(string firstNumber, string secondNumber, int base) {
    int length1 = firstNumber.size(), length2 = secondNumber.size();
    if (length1 == 1 && length2 == 1)
        return to_string((firstNumber[0] - '0') * (secondNumber[0] - '0'));
    
    int halfLength = max(length1, length2) / 2;
    string highPart1 = firstNumber.substr(0, length1 - halfLength);
    string lowPart1 = firstNumber.substr(length1 - halfLength);
    string highPart2 = secondNumber.substr(0, length2 - halfLength);
    string lowPart2 = secondNumber.substr(length2 - halfLength);
    
    string z0 = karatsubaMultiplication(lowPart1, lowPart2, base);
    string z1 = karatsubaMultiplication(to_string(stoi(lowPart1) + stoi(highPart1)), to_string(stoi(lowPart2) + stoi(highPart2)), base);
    string z2 = karatsubaMultiplication(highPart1, highPart2, base);
    
    string productResult = to_string(stoi(z2) * pow(base, 2 * halfLength) + (stoi(z1) - stoi(z2) - stoi(z0)) * pow(base, halfLength) + stoi(z0));
    return productResult;
}

string convertBase(int number, int base) {
    if (number == 0) return "0";
    string convertedResult = "";
    while (number > 0) {
        convertedResult += (number % base) + '0';
        number /= base;
    }
    reverse(convertedResult.begin(), convertedResult.end());
    return convertedResult;
}

int main() {
    string firstNumber, secondNumber;
    int base;
    cin >> firstNumber >> secondNumber >> base;
    
    string sumOutput = schoolAddition(firstNumber, secondNumber, base);
    string productOutput = karatsubaMultiplication(firstNumber, secondNumber, base);
    string divisionOutput = "0";
    
    cout << sumOutput << " " << productOutput << " " << divisionOutput << endl;
    return 0;
}
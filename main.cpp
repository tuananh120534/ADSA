#include <bits/stdc++.h>
using namespace std;

string addNumbers(string firstNumber, string secondNumber, int numberBase) {
    int carryOver = 0;
    string sumResult = "";
    int firstLength = firstNumber.size(), secondLength = secondNumber.size();
    int maxLength = max(firstLength, secondLength);
    reverse(firstNumber.begin(), firstNumber.end());
    reverse(secondNumber.begin(), secondNumber.end());
    
    for (int i = 0; i < maxLength; i++) {
        int digitOne = firstNumber[i] - '0';
        int digitTwo = secondNumber[i] - '0';
        int total = digitOne + digitTwo + carryOver;
        carryOver = total / numberBase;
        sumResult += (total % numberBase) + '0';
    }
    if (carryOver) sumResult += (carryOver + '0');
    reverse(sumResult.begin(), sumResult.end());
    return sumResult;
}

string multiplyNumbers(string firstNumber, string secondNumber, int numberBase) {
    int firstLength = firstNumber.size(), secondLength = secondNumber.size();
    if (firstLength == 1 && secondLength == 1)
        return to_string((firstNumber[0] - '0') * (secondNumber[0] - '0'));
    
    int halfLength = max(firstLength, secondLength) / 2;
    string highPartFirst = firstNumber.substr(0, firstLength - halfLength);
    string lowPartFirst = firstNumber.substr(firstLength - halfLength);
    string highPartSecond = secondNumber.substr(0, secondLength - halfLength);
    string lowPartSecond = secondNumber.substr(secondLength - halfLength);
    
    string z0 = multiplyNumbers(lowPartFirst, lowPartSecond, numberBase);
    string z1 = multiplyNumbers(to_string(stoi(lowPartFirst) + stoi(highPartFirst)), to_string(stoi(lowPartSecond) + stoi(highPartSecond)), numberBase);
    string z2 = multiplyNumbers(highPartFirst, highPartSecond, numberBase);
    
    string productResult = to_string(stoi(z2) * pow(numberBase, 2 * halfLength) + (stoi(z1) - stoi(z2) - stoi(z0)) * pow(numberBase, halfLength) + stoi(z0));
    return productResult;
}

string divideNumbers(string firstNumber, string secondNumber, int numberBase) {
    return "0";
}

int main() {
    string firstNumber, secondNumber;
    int numberBase;
    cin >> firstNumber >> secondNumber >> numberBase;
    
    string sumOutput = addNumbers(firstNumber, secondNumber, numberBase);
    string productOutput = multiplyNumbers(firstNumber, secondNumber, numberBase);
    string divisionOutput = divideNumbers(firstNumber, secondNumber, numberBase);
    
    cout << sumOutput << " " << productOutput << " " << divisionOutput << endl;
    return 0;
}
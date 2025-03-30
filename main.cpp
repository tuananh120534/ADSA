#include <iostream>
#include <string>
#include <algorithm>
#include<cmath>
using namespace std;
string multiplyMethod(string n1, string n2, int ba) {
    int n = n1.size();
    int m = n2.size();
    string pr(n + m, '0');
    for (int i = n - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = m - 1; j >= 0; j--) {
            int mu = (n1[i] - '0') * (n2[j] - '0') + (pr[i + j + 1] - '0') + carry;
            carry = mu / ba;
            pr[i + j + 1] = (mu % ba) + '0';
        }
        pr[i] += carry;
    }
    if (pr[0] == '0') {
        pr.erase(pr.begin());
    }

    return pr;
}
string addMethod(string n1, string n2, int ba) {
    int carry = 0;
    string result = "";
    int a = n1.size() - 1;
    int b = n2.size() - 1;
    while (a >= 0 || b >= 0 || carry > 0) {
        int firstDigit = (a >= 0) ? n1[a] - '0' : 0;
        int secondDigit = (b >= 0) ? n2[b] - '0' : 0;
        int s = firstDigit + secondDigit + carry;
        carry = s / ba;
        result += to_string(s % ba);
        a--;
        b--;
    }
    reverse(result.begin(), result.end());
    return result;
}
string divideMethod(string n1, string n2, int ba) {
    return "0";
}
int main() {
    string n1, n2;
    int ba;
    cin >> n1 >> n2 >> ba;
    string sum = addMethod(n1, n2, ba);
    string product = multiplyMethod(n1, n2, ba);
    string ratio = divideMethod(n1, n2, ba);
    cout << sum << " " << product << " " << ratio << endl;
    return 0;
}
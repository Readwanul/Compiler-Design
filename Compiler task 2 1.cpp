#include <iostream>
#include <string>
using namespace std;

bool isNumericConstant(string str) {
    if (str.empty()) return false;

    bool hasDigits = false;
    bool hasDecimalPoint = false;


    for (size_t i = 0; i < str.length(); ++i) {
        if (isdigit(str[i])) {
            hasDigits = true;
        } else if (str[i] == '.' && !hasDecimalPoint) {
            hasDecimalPoint = true;
        } else {
            return false;
        }
    }

    return hasDigits;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (isNumericConstant(input)) {
        cout << "Numeric constant" << std::endl;
    } else {
        cout << "Not numeric" << std::endl;
    }

    return 0;
}

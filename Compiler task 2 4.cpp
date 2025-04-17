#include <iostream>
#include <string>
using namespace std;

bool Identifier(string str) {
    if (str.empty()) {
        return false;
    }

    if (!isalpha(str[0]) && str[0] != '_' && str[0] != '$') {
        return false;
    }

    for (size_t i = 1; i < str.length(); ++i) {
        if (!isalnum(str[i]) && str[i] != '_' && str[i] != '$') {
            return false;
        }
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (Identifier(input)) {
        cout << "Valid identifier" << endl;
    } else {
        cout << "Invalid identifier" << endl;
    }

    return 0;
}


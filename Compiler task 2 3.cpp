#include <iostream>
#include <string>
using namespace std;

int main() {
    string input, line, multiLineInput;
    bool isMultiLine = false;

    cout << "Enter the input (end with 'END' on a new line):" << endl;

    while (getline(cin, line)) {
        if (line == "END") {
            break;
        }

        if (isMultiLine) {
            multiLineInput += line + "\n";
            if (line.find("*/") != string::npos) {
                isMultiLine = false;
                cout << "Multiple line comment" << endl;
            }
            continue;
        }

        if (line.find("//") != string::npos) {
            cout << "Single line comment" << endl;
        }

        else if (line.find("/*") != string::npos) {
            isMultiLine = true;
            multiLineInput = line + "\n";
            if (line.find("*/") != string::npos) {
                isMultiLine = false;
                cout << "Multiple line comment" << endl;
            }
        }

        else {
            cout << "Not a comment" << endl;
        }
    }

    return 0;
}


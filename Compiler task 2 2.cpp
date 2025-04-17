#include <iostream>
#include <string>
using namespace std;


void findArithmeticOperators(const string& input) {
    char operators[] = {'+', '-', '*', '/', '%', '='};
    int operatorsCount = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < input.length(); ++i) {
        for (int j = 0; j < operatorsCount; ++j) {
            if (input[i] == operators[j]) {
                cout << "Operator: '" << input[i] <<"' "<<endl;
            }
        }
    }
}

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    cin>>input;

    findArithmeticOperators(input);

    return 0;
}


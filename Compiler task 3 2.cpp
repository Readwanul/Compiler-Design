#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool CheckExp(string expression) {
    stack<char> parentheses;
    int length = expression.length();

    if (length == 0) {
        return false;
    }

    if (isOperator(expression[length - 1])) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        char ch = expression[i];

        if (ch == '(') {
            parentheses.push(ch);
        } else if (ch == ')') {
            if (parentheses.empty() || parentheses.top() != '(') {
                return false;
            }
            parentheses.pop();
        }

        if (isOperator(ch)) {
            if (i == 0 || i == length - 1) {
                return false;
            }
            if (!islower(expression[i - 1]) || !islower(expression[i + 1])) {
                return false;
            }
        }

        if (!islower(ch) && !isOperator(ch) && ch != '(' && ch != ')') {
            return false;
        }
    }

    if (!parentheses.empty()) {
        return false;
    }

    return true;
}

int main() {
    string expression;
    cout << "Enter a mathematical expression: ";
    cin >> expression;

    if (CheckExp(expression)) {
        cout << "Valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }

    return 0;
}


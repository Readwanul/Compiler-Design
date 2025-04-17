#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool isValidExpression(const string& expr, int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (i == start || i == end) {
                return false;
            }
            if (!islower(expr[i-1]) && expr[i-1] != ')' ||
                !islower(expr[i+1]) && expr[i+1] != '(') {
                return false;
            }
        }
    }
    return true;
}

bool OperatorPosition(const string& expr) {
    int n = expr.length();
    int parenthesesDepth = 0;

    for (int i = 0; i < n; ++i) {
        if (expr[i] == '(') {
            parenthesesDepth++;
            int j = i;
            while (j < n && parenthesesDepth > 0) {
                j++;
                if (expr[j] == '(') {
                    parenthesesDepth++;
                } else if (expr[j] == ')') {
                    parenthesesDepth--;
                }
            }

            if (!isValidExpression(expr, i + 1, j - 1)) {
                return false;
            }
            i = j;
        }
    }
    return isValidExpression(expr, 0, n - 1);
}

int main() {
    string expr1;
    cout << "Expression: ";
    getline(cin, expr1);

    cout << (OperatorPosition(expr1) ? "true" : "false") << endl;

    return 0;
}

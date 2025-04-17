#include <stack>
#include <string>
#include<iostream>
using namespace std;

bool isBalanced(string expr) {
    std::stack<char> stack;

    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) {
                return false;
            }
        else {
            char top = stack.top();
            stack.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{'))
                {
                return false;
                }
            }
        }
    }

    return stack.empty();
}

int main() {
    string expr1;
    cout<<"Expression:";
    cin>>expr1;

    cout << boolalpha;
    cout << "Is " << expr1 << " balanced: " << isBalanced(expr1) << endl;


    return 0;
}

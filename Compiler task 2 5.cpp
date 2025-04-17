#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string str) {
    int start = 0;
    int end = str.length() - 1;

    while (start < end) {
        while (start < end && !isalnum(str[start])) {
            start++;
        }
        while (start < end && !isalnum(str[end])) {
            end--;
        }

        if (std::tolower(str[start]) != std::tolower(str[end])) {
            return false;
        }

        start++;
        end--;
    }

    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(std::cin, input);

    if (isPalindrome(input)) {
        cout << "Palindrome" << std::endl;
    } else {
        cout << "Not a palindrome" << std::endl;
    }

    return 0;
}

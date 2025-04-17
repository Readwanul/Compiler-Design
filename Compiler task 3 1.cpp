#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <sstream>
using namespace std;

const unordered_set<string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case",
    "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const", "consteval",
    "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype",
    "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace",
    "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
    "public", "reflexpr", "register", "reinterpret_cast", "requires", "return", "short", "signed",
    "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template",
    "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
    "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};

const unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '^', '%'};
const unordered_set<char> delimiters = {',', ';', '(', ')', '{', '}', '[', ']'};

bool isKeyword(string word) {
    return keywords.find(word) != keywords.end();
}

bool isValidIdentifier(string str) {
    if (str.empty() || !(isalpha(str[0]) || str[0] == '_')) {
        return false;
    }
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

bool isInteger(string str) {
    if (str.empty() || (str[0] == '-' && str.length() == 1)) {
        return false;
    }
    size_t start = (str[0] == '-') ? 1 : 0;
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isRealNumber(string str) {
    if (str.empty()) {
        return false;
    }
    bool decimalPoint = false;
    size_t start;
    if (str[0] == '-') {
       start = 1;
    } else {
       start = 0;
    }
    for (size_t i = start; i < str.length(); ++i) {
        if (str[i] == '.') {
            if (decimalPoint) {
                return false;
            }
            decimalPoint = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return decimalPoint;
}

void processToken(string token) {
    if (isKeyword(token)) {
        cout << token << " is a keyword" << endl;
    } else if (isValidIdentifier(token)) {
        cout << token << " is a valid identifier" << endl;
    } else if (!token.empty() && isdigit(token[0])) {
        cout << token << " is an invalid identifier" << endl;
    } else if (isInteger(token)) {
        cout << token << " is an integer" << endl;
    } else if (isRealNumber(token)) {
        cout << token << " is a real number" << endl;
    } else {
        cout << token << " is an invalid identifier" << endl;
    }
}

void tokenizeAndClassify(string line) {
    string token;
    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];
        if (isspace(ch) || operators.count(ch) || delimiters.count(ch)) {
            if (!token.empty()) {
                processToken(token);
                token.clear();
            }
            if (operators.count(ch)) {
                cout << ch << " is an operator" << endl;
            } else if (delimiters.count(ch)) {
                cout << ch << " is a delimiter" << endl;
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        processToken(token);
    }
}

int main() {
    ifstream file("program.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        tokenizeAndClassify(line);
    }

    file.close();
    return 0;
}

#include <iostream>
#include <string>
#include <regex>
using namespace std;

bool CheckVariableDeclaration(const string& line) {
    regex variableRegex(R"((int|float|double|char|std::string)\s+[a-zA-Z_][a-zA-Z0-9_]*(\s*=\s*[^;]+)?\s*;)");
    return regex_match(line, variableRegex);
}


bool CheckFunctionDeclaration(const string& line) {
    regex functionDeclRegex(R"((int|void|float|double|char|std::string)\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(\s*([a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*(,\s*[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*)*)?\)\s*;)");
    return regex_match(line, functionDeclRegex);
}

bool CheckFunctionDefinition(const string& line) {
    regex functionDefRegex(R"((int|void|float|double|char|std::string)\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(\s*([a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*(,\s*[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*)*)?\)\s*\{)");
    return regex_match(line, functionDefRegex);
}

bool CheckDataTypeMatch(const string& dataType, const string& value) {
    stringstream ss(value);
    if (dataType == "int") {
        int intValue;
        ss >> intValue;
        return !ss.fail() && ss.eof();
    } else if (dataType == "float" || dataType == "double") {
        double floatValue;
        ss >> floatValue;
        return !ss.fail() && ss.eof();
    } else if (dataType == "char") {
        return value.length() == 3 && value[0] == '\'' && value[2] == '\'';  // char should be like 'a'
    } else if (dataType == "string") {
        return value.length() >= 2 && value[0] == '"' && value.back() == '"';  // string should be in quotes
    }
    return false;
}

bool CheckVariableDeclarationWithType(const string& line) {
    regex variableRegex(R"((int|float|double|char|std::string)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(=\s*(.+))?\s*;)");
    smatch match;

    if (regex_match(line, match, variableRegex)) {
        string dataType = match[1];
        string value = match[4];
        if (!value.empty()) {
            return CheckDataTypeMatch(dataType, value);
        }
        return true;
    }
    return false;
}

int main() {
    string ln;

    cout << "Enter lines of C++ code :" << endl;

    while (true) {
        getline(cin, ln);
        if (ln.empty()) {
            break;
        }

        if (CheckVariableDeclarationWithType(ln)) {
            cout << "Proper Variable Declaration: " << ln << endl;
        } else if (CheckFunctionDeclaration(ln)) {
            cout << "Proper Function Declaration: " << ln << endl;
        } else if (CheckFunctionDefinition(ln)) {
            cout << "Proper Function Definition: " << ln << endl;
        } else {
            cout << "Invalid Declaration or Definition: " << ln << endl;
        }
    }

    return 0;
}

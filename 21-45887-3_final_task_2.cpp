#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <regex>
using namespace std;

struct AnalysisResult {
    int lineNumber;
    string message;
    bool isError;

    AnalysisResult(int line,string msg, bool error)
        : lineNumber(line), message(msg), isError(error) {}
};


bool areParenthesesBalanced(string line) {
    stack<char> st;
    for (char c : line) {
        if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}

bool CheckFunctionDefinition(const string& line) {
    regex functionDefRegex(R"((int|void|float|double|char|std::string)\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(\s*([a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*(,\s*[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*)*)?\)\s*\{)");
    return regex_match(line, functionDefRegex);
}


AnalysisResult syntaxAnalysis(int lineNumber,string line) {
    if (regex_match(line, regex("^\\s*$")) || regex_match(line, regex("^\\s*//.*$"))) {
        return AnalysisResult(lineNumber, "Skip (blank/comment)", false);
    }

    if (!regex_match(line, regex(".*;\\s*(//.*)?$")) && !regex_match(line, regex(".*\\}\\s*$")) && !CheckFunctionDefinition(line)) {
        return AnalysisResult(lineNumber, "Syntax Error: Missing semicolon.", true);
    }


    if (!areParenthesesBalanced(line)) {
        return AnalysisResult(lineNumber, "Syntax Error: Mismatched parentheses.", true);
    }

    if (regex_search(line, regex("(int|float|char)\\s+\\w+\\s*;"))) {
        return AnalysisResult(lineNumber, "Passed", false);
    }

    return AnalysisResult(lineNumber, "Passed", false);
}

AnalysisResult semanticAnalysis(int lineNumber, string line, vector<string>& declaredVariables) {
    if (regex_match(line, regex("^\\s*$")) || regex_match(line, regex("^\\s*//.*$"))) {
        return AnalysisResult(lineNumber, "Skip (blank/comment)", false);
    }

    smatch match;
    if (regex_search(line, match, regex("(\\w+)\\s*=\\s*[^;]+;"))) {
        string variable = match.str(1);
        if (find(declaredVariables.begin(), declaredVariables.end(), variable) == declaredVariables.end()) {
            return AnalysisResult(lineNumber, "Semantic Error: Undeclared variable '" + variable + "'", true);
        }
    }

    if (regex_search(line, match, regex("(int|float|char)\\s+(\\w+)\\s*;"))) {
        string variable = match.str(2);
        declaredVariables.push_back(variable);
    }

    return AnalysisResult(lineNumber, "Passed", false);
}

// Main program
int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error: Unable to open input or output file." << endl;
        return 1;
    }

    string ln;
    int lineNumber = 0;
    vector<AnalysisResult> syntaxResults;
    vector<AnalysisResult> semanticResults;
    vector<string> declaredVariables;

    while (getline(inputFile, ln)) {
        lineNumber++;

        // Perform Syntax Analysis
        AnalysisResult syntaxResult = syntaxAnalysis(lineNumber, ln);
        syntaxResults.push_back(syntaxResult);

        // Perform Semantic Analysis
        if (!syntaxResult.isError) {
            AnalysisResult semanticResult = semanticAnalysis(lineNumber, ln , declaredVariables);
            semanticResults.push_back(semanticResult);
        } else {
            semanticResults.push_back(AnalysisResult(lineNumber, "error", true));
        }
    }

    outputFile << "Syntax Analysis:\n";
    for (const auto& result : syntaxResults) {
        outputFile << "- Line " << result.lineNumber << ": " << result.message << endl;
    }

    outputFile << "\nSemantic Analysis:\n";
    for (const auto& result : semanticResults) {
        outputFile << "- Line " << result.lineNumber << ": " << result.message << endl;
    }

    outputFile.close();
    inputFile.close();

    cout << "Analysis complete. Results written to output.txt." << endl;

    return 0;
}

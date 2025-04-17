#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <regex>
using namespace std;

// Structure to hold analysis results
struct AnalysisResult {
    int lineNumber;
    string message;
    bool isError;

    AnalysisResult(int line, const string& msg, bool error)
        : lineNumber(line), message(msg), isError(error) {}
};

// Function to check for balanced parentheses
bool areParenthesesBalanced(const string& line) {
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

// Function for syntax analysis of a single line
AnalysisResult syntaxAnalysis(int lineNumber, const string& line) {
    // Check for semicolon at the end of the line (for most statements)
    if (!regex_match(line, regex(".*;\\s*$")) && !regex_match(line, regex(".*\\}\\s*$"))) {
        return AnalysisResult(lineNumber, "Syntax Error: Missing semicolon.", true);
    }

    // Check for balanced parentheses
    if (!areParenthesesBalanced(line)) {
        return AnalysisResult(lineNumber, "Syntax Error: Mismatched parentheses.", true);
    }

    // Check for valid variable declaration (basic check)
    if (regex_search(line, regex("(int|float|char)\\s+\\w+\\s*;"))) {
        return AnalysisResult(lineNumber, "Passed", false);
    }

    return AnalysisResult(lineNumber, "Passed", false);
}

// Function for semantic analysis of a single line (very basic)
AnalysisResult semanticAnalysis(int lineNumber, const string& line, vector<string>& declaredVariables) {
    // Check if variables are declared before use
    smatch match;
    if (regex_search(line, match, regex("(\\w+)\\s*=\\s*[^;]+;"))) {
        string variable = match.str(1);
        if (find(declaredVariables.begin(), declaredVariables.end(), variable) == declaredVariables.end()) {
            return AnalysisResult(lineNumber, "Semantic Error: Undeclared variable '" + variable + "' used.", true);
        }
    }

    // Check for valid variable declarations
    if (regex_search(line, match, regex("(int|float|char)\\s+(\\w+)\\s*;"))) {
        string variable = match.str(2);
        declaredVariables.push_back(variable);
    }

    return AnalysisResult(lineNumber, "Passed", false);
}

// Main program
int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output1.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error: Unable to open input or output file." << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    vector<AnalysisResult> syntaxResults;
    vector<AnalysisResult> semanticResults;
    vector<string> declaredVariables;

    // Read file line by line
    while (getline(inputFile, line)) {
        lineNumber++;

        // Perform Syntax Analysis
        AnalysisResult syntaxResult = syntaxAnalysis(lineNumber, line);
        syntaxResults.push_back(syntaxResult);

        // Perform Semantic Analysis (only if syntax is correct)
        if (!syntaxResult.isError) {
            AnalysisResult semanticResult = semanticAnalysis(lineNumber, line, declaredVariables);
            semanticResults.push_back(semanticResult);
        } else {
            // If syntax error, no need for semantic analysis
            semanticResults.push_back(AnalysisResult(lineNumber, "Skipped due to syntax error", true));
        }
    }

    // Output the results
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


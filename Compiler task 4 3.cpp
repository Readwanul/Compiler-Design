#include <iostream>
#include <string>
#include <cctype>

using namespace std;


bool isValidPhoneNumber(string phone) {
    if(phone.length()==11){
        enum State { START, PLUS, DIGIT, DASH };
    State state = START;

    for (char c : phone) {
        switch (state) {
            case START:
                if (c == '+') {
                    state = PLUS;
                } else if (isdigit(c)) {
                    state = DIGIT;
                } else {
                    return false;
                }
                break;
            case PLUS:
            case DIGIT:
                if (isdigit(c)) {
                    state = DIGIT;
                } else if (c == '-') {
                    state = DASH;
                } else {
                    return false;
                }
                break;
            case DASH:
                if (isdigit(c)) {
                    state = DIGIT;
                } else {
                    return false;
                }
                break;
        }
    }

    return state == DIGIT;
    }
    else{
        cout<<"Invalid number.";
    }

}


bool isValidEmailAddress(const string& email) {
    enum State { LOCAL, AT, DOMAIN, DOT, AFTER_DOT };
    State state = LOCAL;
    int atCount = 0;
    bool dotFound = false;
    bool validDomainPart = false;

    for (char c : email) {
        switch (state) {
            case LOCAL:
                if (isalnum(c) || c == '.' || c == '_') {
                    // Stay in LOCAL
                } else if (c == '@') {
                    state = AT;
                    atCount++;
                } else {
                    return false;
                }
                break;
            case AT:
                if (isalnum(c)) {
                    state = DOMAIN;
                } else {
                    return false;
                }
                break;
            case DOMAIN:
                if (isalnum(c) || c == '-') {
                } else if (c == '.') {
                    state = DOT;
                    dotFound = true;
                } else {
                    return false;
                }
                break;
            case DOT:
                if (isalpha(c)) {
                    state = AFTER_DOT;
                } else {
                    return false;
                }
                break;
            case AFTER_DOT:
                if (isalpha(c)) {
                    validDomainPart = true;
                    state = DOMAIN;
                } else if (c == '.') {
                    state = DOT;
                    validDomainPart = false;
                } else {
                    return false;
                }
                break;
        }
    }

    return state == DOMAIN && atCount == 1 && dotFound && validDomainPart;
}

int main() {
    string input;


    cout << "Enter a phone number: ";
    getline(cin, input);
    cout << (isValidPhoneNumber(input) ? "true" : "false") << endl;

    cout << "Enter an email address: ";
    getline(cin, input);
    cout << (isValidEmailAddress(input) ? "true" : "false") << endl;

    return 0;
}

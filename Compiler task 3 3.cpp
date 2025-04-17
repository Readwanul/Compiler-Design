#include <iostream>
using namespace std;

bool isValidSentence(const char* sentence) {
    enum State { START, AFTER_CAPITAL, AFTER_SPACE, AFTER_LOWER };
    State currentState = START;

    while (*sentence != '\0') {
        switch (currentState) {
            case START:
                if (*sentence >= 'A' && *sentence <= 'Z') {
                    currentState = AFTER_CAPITAL;
                } else {
                    return false;
                }
                break;
            case AFTER_CAPITAL:
                if ((*sentence >= 'a' && *sentence <= 'z') ||
                    (*sentence == ' ')) {

                } else if (*sentence == '.') {
                    return true;
                } else {
                    return false;
                }
                break;
            case AFTER_SPACE:
                if (*sentence >= 'A' && *sentence <= 'Z') {
                    currentState = AFTER_CAPITAL;
                } else {
                    return false;
                }
                break;
            case AFTER_LOWER:
                if (*sentence == ' ') {
                    currentState = AFTER_SPACE;
                } else {
                    return false;
                }
                break;
        }
        sentence++;
    }

    return false;
}

int main() {
    const char* sentences[] = {
        "I love to code.",
        "I love Football.",
        "My name is Cristiano.",
        "I love cenima.",
        "hi, is a quiz site.",
        "I love CSE.",
        "You are my friend.",
        nullptr
    };

    for (int i = 0; sentences[i] != nullptr; i++) {
        if(isValidSentence(sentences[i])){
           cout<<"'"<<sentences[i]<<"' is Valid"<< endl;
        }
        else if(!isValidSentence(sentences[i])){
           cout<<"'"<<sentences[i]<<"' is Invalid"<< endl;
        }
    }

    return 0;
}

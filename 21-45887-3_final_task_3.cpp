#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

class NFA {
public:
    int numStates;
    int startState;
    set<int> finalStates;
    map<pair<int, char>, set<int>> transitions;

    NFA(int n, int start, set<int> finals) : numStates(n), startState(start), finalStates(finals) {}

    void addTransition(int from, int to, char symbol) {
        transitions[{from, symbol}].insert(to);
    }

    set<int> move(const set<int>& states, char symbol) {
        set<int> result;
        for (int state : states) {
            if (transitions.find({state, symbol}) != transitions.end()) {
                result.insert(transitions[{state, symbol}].begin(), transitions[{state, symbol}].end());
            }
        }
        return result;
    }
};

class DFA {
public:
    set<set<int>> states;
    map<pair<set<int>, char>, set<int>> transitions;
    set<int> startState;
    set<set<int>> finalStates;
    DFA(set<int> start) : startState(start) {}

    void printDFA() {
        cout << "DFA States:\n";
        for (const auto& state : states) {
            cout << "(";
            for (int s : state) cout << s ;
            cout << ") ";
        }
        cout << endl;

        cout << "\nDFA Transitions:\n";
        for (const auto& trans : transitions) {
            cout << "(";
            for (int s : trans.first.first) cout << s;
            cout << ") --" << trans.first.second << "--> (";
            for (int s : trans.second) cout << s;
            cout << ")\n";
        }

        cout << "\nStart State: { ";
        for (int s : startState) cout << s << " ";
        cout << "}\n";

        cout << "\nFinal States:\n";
        for (const auto& state : finalStates) {
            cout << "( ";
            for (int s : state) cout << s << " ";
            cout << ") ";
        }
        cout << endl;
    }
};

DFA subsetConstruction(NFA& nfa, const vector<char>& alphabet) {
    set<set<int>> dfaStates;
    map<pair<set<int>, char>, set<int>> dfaTransitions;
    queue<set<int>> unmarkedStates;
    set<int> startState = {nfa.startState};
    dfaStates.insert(startState);
    unmarkedStates.push(startState);

    set<set<int>> dfaFinalStates;
    if (!nfa.finalStates.empty() && nfa.finalStates.count(*startState.begin())) {
        dfaFinalStates.insert(startState);
    }

    while (!unmarkedStates.empty()) {
        set<int> currentState = unmarkedStates.front();
        unmarkedStates.pop();

        for (char symbol : alphabet) {
            set<int> nextState = nfa.move(currentState, symbol);

            if (!nextState.empty() && dfaStates.find(nextState) == dfaStates.end()) {
                dfaStates.insert(nextState);
                unmarkedStates.push(nextState);
                for (int s : nextState) {
                    if (nfa.finalStates.count(s)) {
                        dfaFinalStates.insert(nextState);
                        break;
            }}}
            dfaTransitions[{currentState, symbol}] = nextState;
        }
    }

    DFA dfa(startState);
    dfa.states = dfaStates;
    dfa.transitions = dfaTransitions;
    dfa.finalStates = dfaFinalStates;
    return dfa;
}

int main() {
    NFA nfa(3, 0, {2});

    nfa.addTransition(0, 1, 'a');
    nfa.addTransition(0, 0, 'a');
    nfa.addTransition(0, 1, 'b');
    nfa.addTransition(1, 2, 'a');
    nfa.addTransition(1, 1, 'b');
    nfa.addTransition(2, 3, 'a');
    nfa.addTransition(2, 3, 'b');
    nfa.addTransition(3, 3, 'a');
    nfa.addTransition(3, 3, 'b');

    vector<char> alphabet = {'a', 'b'};
    DFA dfa = subsetConstruction(nfa, alphabet);
    dfa.printDFA();

    return 0;
}

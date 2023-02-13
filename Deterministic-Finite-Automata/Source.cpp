#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<set>
using namespace std;
class DFA {
private:
    map<string, int>statesId;
    map<string, int>alphabetId;
    vector<vector<int>>transitions;
    bool validMachine;
    int startState;
    set<int>acceptStates;
    void getStates() {
        cout << "What is the number of states in the language?\n";
        int num; cin >> num;
        vector<string>states(num);
        cout << "Enter the states\n";
        for (int i = 0; i < num; i++) {
            cin >> states[i];
        }
        storeStates(states);
    }
    void storeStates(vector<string>& states) {
        for (int i = 0; i < states.size(); i++) {
            statesId[states[i]] = i + 1;
        }
    }
    void getAlphabet() {
        cout << "What is the number of the characters in the alphabet?\n";
        int num; cin >> num;
        vector<string>alpha(num);
        cout << "Enter the alphabet\n";
        for (int i = 0; i < num; i++) {
            cin >> alpha[i];
        }
        storeAlphabet(alpha);
    }
    void storeAlphabet(vector<string>& alpha) {
        for (int i = 0; i < alpha.size(); i++) {
            alphabetId[alpha[i]] = i + 1;
        }
    }
    void getTransitions() {
        string nState;
        for (auto& i : statesId) {
            cout << "The current state is " + i.first << " :" << "\n";
            for (auto& j : alphabetId) {
                cout << "\tIf the input is " + j.first << " the edge goes to: ";
                cin >> nState;
                if (!validState(nState)) {
                    validMachine = 0;
                }
                else {
                    transitions[i.second][j.second] = statesId[nState];
                }
            }
        }
    }
    void getStartState() {
        startState = -1;
        string start;
        cout << "Enter the start state\n";
        cin >> start;
        if (!validState(start)) {
            validMachine = 0;
        }
        else {
            startState = statesId[start];
        }
    }
    void getAcceptStates() {
        cout << "What is the number of accept states?\n";
        int num; cin >> num;
        cout << "Enter the accept states\n";
        vector<string>states(num);
        for (int i = 0; i < num; i++) {
            cin >> states[i];
            if (!validState(states[i])) {
                validMachine = 0;
            }

        }
        if (validMachine)
            storeAcceptStates(states);
    }
    void storeAcceptStates(vector<string>& states) {
        for (auto& i : states)
            acceptStates.insert(statesId[i]);
    }
    bool validState(string state) {
        if (statesId.find(state) == statesId.end())return 0;
        return 1;
    }
    bool validCharacter(string alpha) {
        //check that the alphabet exists in the language or not
        if (alphabetId.find(alpha) == alphabetId.end())
            return 0;
        return 1;
    }
    bool isAccept(int endState) {
        if (acceptStates.find(endState) == acceptStates.end())
            return 0;
        return 1;
    }
public:
    DFA() {
        getStates();
        getAlphabet();
        validMachine = 1;
        transitions = vector<vector<int>>(statesId.size() + 1,
            vector<int>(alphabetId.size() + 1, -1));
        getTransitions();
        getStartState();
        getAcceptStates();
    }
    int check(string& str) {
        string input;
        int curState = startState;
        for (auto i : str) {
            input = i;
            if (!validCharacter(input))return -1;

            curState = transitions[curState][alphabetId[input]];
        }
        if (isAccept(curState))
            return 1;
        return 0;
    }
    bool valid() {
        return validMachine;
    }


};
int main() {
    DFA dfa = DFA();
    if (!dfa.valid()) {
        cout << "Invalid DFA\n";
        return 0;
    }
    cout << "What is the number of strings you want to check?\n";
    int num; cin >> num;
    string str;
    while (num--) {
        cout << "Enter the string you want to check\n";
        cin >> str;
        int valid = dfa.check(str);
        if (valid == -1)
            cout << "Unsupported string in the language\n";
        else if (valid == 1)
            cout << "Accept\n";
        else cout << "Reject\n";

    }
    return 0;
}

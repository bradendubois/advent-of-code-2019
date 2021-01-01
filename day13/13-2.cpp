#include <iostream>

#include "../Intcode.cpp"

using namespace std;

Intcode machine;

void display(vector<long> ins) {

    map<int, map<int, char>> screen;

    int cur, score, largest_x = 0, largest_y = 0;
    for (int i = 0; i < ins.size(); i += 3) {

        cur = ins[i+2];

        if (ins[i] == -1 && ins[i+1] == 0) {
            score = cur;
            continue;
        }

        if (cur == 0)
            screen[ins[i+1]][ins[i]] = ' ';
        else if (cur == 1)
            screen[ins[i+1]][ins[i]] = 'X';
        else if (cur == 2)
            screen[ins[i+1]][ins[i]] = 'C';
        else if (cur == 3)
            screen[ins[i+1]][ins[i]] = 'P';
        else if (cur == 4)
            screen[ins[i+1]][ins[i]] = 'O';
    
        if (ins[i] > largest_x) largest_x = ins[i]; 
        if (ins[i+1] > largest_y) largest_y = ins[i+1]; 
    }


    for (int i = 0; i <= largest_y; i++) {
        for (int j = 0; j <= largest_x; j++) {
            cout << screen[i][j];
        } cout << endl;
    }

    cout << endl;
    cout << "Score: " << score << endl << endl;

}

int main() {

    string instructions;
    cin >> instructions;

    machine.load_sequence(instructions);
    vector<long> output;
    machine.next = &output;

    for (int i = 1362; i <= 1397; i++) machine.set(i, 3);

    machine.set(0, 2);

    int joystick;

    while (!machine.halted_terminal()) {
        machine.execute();
        display(output);
        machine.receive(0);
    }
}
#include <iostream>

#include "../Intcode.cpp"

int main() {

    string instructions;
    cin >> instructions;

    Intcode machine;

    machine.load_sequence(instructions);

    vector<long> out;
    machine.next = &out;

    string program1 [] = {"NOT C J", "AND D J", "NOT A T", "OR T J", "WALK"};
    for (auto line: program1) {
        for (auto c: line) {
            machine.receive((char) c);
        }

        machine.receive('\n');
    }

    machine.execute();
    for (auto c: out) {
        if (c < 200) cout << (char) c;
        else cout << c;
    } cout << endl;

    out.clear();
    machine.in.clear();
    machine.reset();

    string program2 [] = {
        "NOT B J", "NOT C T", "OR T J", "AND D J", "AND H J", "NOT A T", "OR T J", "RUN"};
    for (auto line: program2) {
        for (auto c: line) {
            machine.receive((char) c);
        }

        machine.receive('\n');
    }

    machine.execute();
    for (auto c: out) {
        if (c < 200)
            cout << (char) c;

        else cout << c;
    } cout << endl;


}
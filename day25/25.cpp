#include <iostream>
#include <fstream>

#include "../Intcode.cpp"

void send(Intcode *machine, string command) {
    for (auto c: command) {
        machine->receive((char) c);
    } machine->receive('\n');
}

int main() {

    string instructions, in;

    ifstream f("25.txt");
    getline(f, instructions);

    Intcode machine;
    vector<long> output;
    machine.next = &output;

    machine.load_sequence(instructions);

    while (1) {

        output.clear();

        machine.execute();

        for (auto c: output) {
            if (c > 200) cout << c << endl;
            else cout << (char) c;
        }

        getline(cin, in);

        send(&machine, in);
    }
}
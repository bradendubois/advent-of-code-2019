#include <iostream>

#include "../Intcode.cpp"

int main() {
    string instructions;
    cin >> instructions;

    Intcode machine;

    machine.load_sequence(instructions);
    machine.receive(2);

    machine.execute();
}
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "../Intcode.cpp"

using namespace std;

int main() {
    string instructions;
    cin >> instructions;
    
    Intcode machine;

    machine.load_sequence(instructions);
    machine.receive(1);

    machine.execute();
}
#include <iostream>

#include "../Intcode.cpp"

using namespace std;

int main() {

    string instructions;
    cin >> instructions;

    Intcode machine;

    machine.load_sequence(instructions);
    vector<long> output;
    machine.next = &output;

    machine.execute();

    map<int, map<int, bool>> block;
    int blocks = 0;
    for (int i = 2; i < output.size(); i += 3) {
        if (output[i] == 2) blocks++;
    } cout << blocks << endl;

}
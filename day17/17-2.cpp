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


    vector<long> directions = {

        // Main Sequence: A B A A B C B C C B
        65, 44, 66, 44, 65, 44, 65, 44, 66, 44, 67, 44, 66, 44, 67, 44, 67, 44, 66, 10, 

        // A: L, 12, R, 8, L, 6, R, 8, L, 6
        76, 44, 49, 50, 44, 82, 44, 56, 44, 76, 44, 54, 44, 82, 44, 56, 44, 76, 44, 54, 10, 
        
        // B: R, 8, L, 12, L, 12, R, 8
        82, 44, 56, 44, 76, 44, 49, 50, 44, 76, 44, 49, 50, 44, 82, 44, 56, 10, 
        
        // C: L, 6, R, 6, L, 12
        76, 44, 54, 44, 82, 44, 54, 44, 76, 44, 49, 50, 10,
        
        // Video Feed off
        110, 10};

    machine.in = directions;

    machine.set(0, 2);
    machine.execute();

    long result = output.back();
    output.pop_back();

    char c;
    for (auto v: output) {

        c = (char) v;
        cout << c;

    }
    cout << result << endl;

}
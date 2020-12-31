#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "../Intcode.h"

using namespace std;

int main() {
    
    string sequence;
    cin >> sequence;

    for (int noun = 0; noun <= 99; noun++) {
        for (int verb = 0; verb <= 99; verb++) {

            Intcode machine;

            machine.load_sequence(sequence);
            
            machine.set(1, noun);
            machine.set(2, verb);

            machine.execute(); 

            if (machine.load(0) == 19690720) {
                cout << (100 * noun) + verb << endl;
                return 0;
            }
        }
    } cout << "Failure" << endl;
}
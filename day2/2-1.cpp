#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "../Intcode.h"

using namespace std;

int main() {
    
    string sequence;
    cin >> sequence;

    Intcode machine;

    machine.load_sequence(sequence);

    machine.set(1, 12);
    machine.set(2, 2);

    machine.execute(); 

    cout << machine.load(0) << endl;
}
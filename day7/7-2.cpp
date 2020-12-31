#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>

#include "../Intcode.cpp"

using namespace std;

int main() {
    
    string instructions;
    cin >> instructions;

    vector<int> phases{5, 6, 7, 8, 9};
    vector<long> signals;

    do {
        
        Intcode machines [5];
        
        for (int i = 0; i < 5; i++) {
            machines[i].load_sequence(instructions);
            machines[i].receive(phases[i]);
        
            if (i != 4) {
                machines[i].next = &(machines[i+1].in);
            }

        }

        machines[0].receive(0);
        machines[4].next = &signals;

        while (!machines[4].halted_terminal()) {
            for (int i = 0; i < 5; i++) 
               machines[i].execute();
               machines[0].receive(signals.back());
        }
        
    } while (std::next_permutation(phases.begin(), phases.end()));

    int best = 0;
    for (auto i : signals) {
        if (i > best) best = i;
    } cout << best << endl;
}
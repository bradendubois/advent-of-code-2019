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

    vector<int> phases{0, 1, 2, 3, 4};
    deque<long> signals;

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

        for (int i = 0; i < 5; i++) 
            machines[i].execute();

    } while (std::next_permutation(phases.begin(), phases.end()));

    int best = 0;

    for (auto i : signals) {
        if (i > best) best = i;
    } cout << best << endl;
}
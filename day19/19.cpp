#include <iostream>

#include "../Intcode.cpp"

using namespace std;

string instructions;
Intcode machine;
vector<long> output;

int pulled(int x, int y) {

    machine.reset();

    machine.receive(x);
    machine.receive(y);
    
    machine.execute();

    return output.back();

}

int main() {

    cin >> instructions;

    machine.load_sequence(instructions);
    machine.next = &output;

    /**************** Part One ****************/
    int x, y , pulled_positions = 0;

    for (x = 0; x < 50; x++) {
        for (y = 0; y < 50; y++) {

            if (pulled(x, y)) pulled_positions++;

        }
    }

    cout << pulled_positions << endl;

    /**************** Part Two ****************/
    int N = 100;

    x = 0, y = N-1;

    while (1) {

        while (!pulled(x, y)) x++;

        if (pulled(x + N-1, y - N+1) == 1) {
            cout << x * 10000 + y-N+1 << endl;
            break;
        }

        y++;
    }
}
#include <iostream>

#include "../Intcode.cpp"

using namespace std;

string instructions;

int pulled(int x, int y) {

    Intcode machine;

    machine.load_sequence(instructions);
    vector<long> output;
    machine.next = &output;

    machine.receive(x);
    machine.receive(y);
    machine.execute();

    return output.back();

}

int main() {

    cin >> instructions;

    int pulled_positions = 0;

    for (int x = 0; x < 50; x++) {

        for (int y = 0; y < 50; y++) {

            if (pulled(x, y)) pulled_positions++;
        }

    }

    cout << pulled_positions << endl;

    int N = 100;

    int x = 0, y = N-1;

    while (1) {

        while (pulled(x, y) == 0) x++;

        if (pulled(x + N-1, y - N+1) == 1) {
            cout << x * 10000 + y-N+1 << endl;
            break;
        }

        y++;
    }
}
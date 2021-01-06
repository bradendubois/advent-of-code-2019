#include <iostream>

#include "../Intcode.cpp"

using namespace std;

int main() {

    string instructions;
    cin >> instructions;

    Intcode machine;

    machine.load_sequence(instructions);
    machine.receive(0);

    deque<long> outputs;
    machine.next = &outputs;

    map<int, map<int, int>> panels;
    map<int, map<int, bool>> seen;
    
    int x = 0, y = 0, facing = 0;

    int paint, turn, paints = 0;

    while (!machine.halted_terminal()) {

        machine.execute();

        paint = outputs[0];
        turn = outputs[1];

        outputs.pop_back();
        outputs.pop_back();

        panels[y][x] = paint;

        if (!seen[y][x]) {
            seen[y][x] = true;
            paints++;
        }

        if (turn) facing++;
        else facing--;

        if (facing < 0) facing += 4;
        facing %= 4;

        switch (facing) {
            case 0:
                y++;
                break;

            case 1:
                x++;
                break;
            
            case 2:
                y--;
                break;

            case 3:
                x--;
                break;
        };

        machine.receive(panels[y][x]);
    }

    cout << paints << endl;
}
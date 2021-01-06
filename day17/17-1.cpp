#include <iostream>

#include "../Intcode.cpp"

using namespace std;

int main() {

    string instructions;
    cin >> instructions;

    Intcode machine;

    machine.load_sequence(instructions);
    deque<long> output;
    machine.next = &output;

    long x, y, alignment = 0;
    deque<deque<char>*> scaffold;
    deque<char> *current;

    char c, up, left, down, right;

    x = 0;
    y = 0;

    machine.execute();
    current = new deque<char>;

    for (auto v: output) {

        c = (char) v;

        if (c == '\n') {
            scaffold.push_back(current);
            current = new deque<char>;

        } else {
            current->push_back(c);
        }
    }

    for (int y = 0; y < scaffold.size(); y++) {
        for (int x = 0; x < scaffold[y]->size(); x++) {

            c = (*scaffold[y])[x];
            
            if (c != '#' || x == 0 || y == 0 || x == scaffold[y]->size() || y == scaffold.size()-2) {
                
                cout << c;

            } else {

                up = (*scaffold[y-1])[x];
                down = (*scaffold[y+1])[x];
                left = (*scaffold[y])[x-1];
                right = (*scaffold[y])[x+1];

                if (up ==  '#' && down ==  '#' && left ==  '#' && right ==  '#') {
                    cout << 'O';
                    alignment += (y * x);
                } else {
                    cout << c;
                }

            }

        }

        cout << endl;
    }

    cout << alignment << endl;
}
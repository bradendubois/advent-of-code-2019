#include <iostream>
#include <deque>

#include "../Intcode.cpp"

using namespace std;

long flood_oxygen(map<long, map<long, bool>> floor, long start_x, long start_y) {

    map<long, map<long, bool>> flooded;

    deque<long> *current, *next, *temp, a, b;
    current = &a;
    next = &b;

    a.push_back(start_x);
    a.push_back(start_y);

    long x, y, last_updated, minutes = 0;

    while (a.size() || b.size()) {

        while (current->size()) {
            x = current->front();
            current->pop_front();
            y = current->front();
            current->pop_front();

            if (!floor[y][x]) {
                continue;
            }

            if (!flooded[y][x]) {
                flooded[y][x] = true;

                last_updated = minutes;

                // Up
                next->push_back(x);
                next->push_back(y+1);

                // Down
                next->push_back(x);
                next->push_back(y-1);
                
                // Left
                next->push_back(x-1);
                next->push_back(y);
                
                // Right
                next->push_back(x+1);
                next->push_back(y);
                
            }
        }

        // Swap buffers
        temp = current;
        current = next;
        next = temp;

        minutes++;
    }

    return last_updated;

}

int main() {

    string instructions;
    cin >> instructions;

    vector<long> output;

    Intcode machine;
    machine.next = &output;

    machine.load_sequence(instructions);

    deque<vector<long>*> queue;
    vector<long> *current, *next_vector, *oxygen = nullptr;

    current = new vector<long>;

    current->push_back(0);
    current->push_back(0);

    queue.push_back(current);

    map<long, map<long, bool>> seen;

    long x, y, oxy_x, oxy_y;

    long response = -1, spaces = 0;

    while (queue.size()) {

        current = queue.front();
        queue.pop_front();

        // Get current location
        y = current->back();
        current->pop_back();
        x = current->back();
        current->pop_back();

        // Skip searching with empty vector
        if (current->size() == 0) goto generate;

        // Clear the machine / search
        machine.reset();
        machine.in = *current;
        machine.execute();

        // Result
        response = output.back();
        output.clear();
        
        // Dead-end
        if (response == 0) {
            free(current);
            continue;
        }

        if (current->back() == 1) y++;
        else if (current->back() == 2) y--;
        else if (current->back() == 3) x++;
        else if (current->back() == 4) x--;

        // Found the oxygen
        if (response == 2) {
            oxygen = current;
            oxy_x = x;
            oxy_y = y;
        }

        if (seen[y][x]) {
            free(current);
            continue;
        }

    generate:

        seen[y][x] = true;
        spaces ++;

        for (int direction = 1; direction <= 4; direction++) {

            next_vector = new vector<long>;
            for (auto v: *current) next_vector->push_back(v);

            next_vector->push_back(direction);
            next_vector->push_back(x); 
            next_vector->push_back(y); 

            queue.push_back(next_vector);
        }

        if (oxygen != current) {
            free(current);
        }
    }

    // Part One
    cout << oxygen->size() << endl;

    // Part Two
    cout << flood_oxygen(seen, oxy_x, oxy_y) << endl;
}
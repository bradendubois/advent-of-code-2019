#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

typedef pair<char, int> ci;
typedef pair<int, int> ii;

void trace(vector<ci> & directions, map<ii, int> & layout, map<ii, int> & other_wire, vector<ii> & overlaps) {
    ii position;
    position.first = 0, position.second = 0;
    int steps = 0;
    for (auto ins : directions) {
        if (ins.first == 'U') {
            while (ins.second--) {
                position.second++;
                steps++;
                ii cur;
                // layout[position]++;
                if (layout[position] == 0) layout[position] = steps;
                if (other_wire[position]) overlaps.push_back(position); 
            }
        }

        if (ins.first == 'D') {
            while (ins.second--) {
                position.second--;
                steps++;
                ii cur;
                // layout[position]++;
                if (layout[position] == 0) layout[position] = steps;
                if (other_wire[position]) overlaps.push_back(position); 
            }
        }

        if (ins.first == 'R') {
            while (ins.second--) {
                position.first++;
                steps++;
                ii cur;
                // layout[position]++;
                if (layout[position] == 0) layout[position] = steps;
                if (other_wire[position]) overlaps.push_back(position); 
            }
        }

        if (ins.first == 'L') {
            while (ins.second--) {
                position.first--;
                steps++;
                ii cur;
                // layout[position]++;
                if (layout[position] == 0) layout[position] = steps;
                if (other_wire[position]) overlaps.push_back(position); 
            }
        }
    }
}

// 2019 - Day 3 - Part 2
int main() {

    int x = 2;
    map<ii, int> first;
    map<ii, int> second;
    vector<map<ii, int>> wires;
    wires.push_back(first);
    wires.push_back(second);

    vector<ii> overlaps;

    while (x--) {
        string line;
        cin >> line;

        vector<ci> path;

        stringstream line_conv(line);
        while (line_conv.good()) {
            char direction;
            int magnitude;
            string instruction;
            getline(line_conv, instruction, ',');
            direction = instruction.at(0);
            stringstream converter(instruction.substr(1));
            converter >> magnitude;
            ci converted_instruction;
            converted_instruction.first = direction;
            converted_instruction.second = magnitude;
            path.push_back(converted_instruction);
        }

        // Bit of horror, switches wires 1 and 2 around, effectively.
        // Hoping no one ever looks at this part...
        trace(path, wires[0], wires[1], overlaps);
        auto temp = wires.back();
        wires.pop_back();
        auto temp2 = wires.back();
        wires.pop_back();
        wires.push_back(temp);
        wires.push_back(temp2);
    }

    int best = INT32_MAX;
    for (auto point : overlaps) {
        // int manhattan = abs(point.first) + abs(point.second);
        int manhattan = wires[0][point] + wires[1][point];
        // cout << wires[0][point] << " : " << wires[1][point] << endl;
        
        if (manhattan < best) best = manhattan;
    }

    cout << best << endl;
}
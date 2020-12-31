#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

typedef vector<vector<bool>> state;

int adj(state & in, int x, int y) {
    int count = 0;

    if (in[x-1][y]) count++;
    if (in[x+1][y]) count++;
    if (in[x][y-1]) count++;
    if (in[x][y+1]) count++;

    return count;
}

state process(state in) {
    state next(7, vector<bool>(7, false));

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            int adjacent = adj(in, i, j);
            if (in[i][j] && adjacent == 1) next[i][j] = true;
            else if (!in[i][j] && (adjacent == 1 || adjacent == 2)) next[i][j] = true; 
        }
    }

    return next;
}

int biodiversity(state in) {
    int count = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (in[i][j]) count += pow(2, ((j-1) +  ((i-1) * 5)));
        }
    } return count;
}

int main() {
    
    map<state, bool> seen;

    state layout(7, vector<bool>(7, false));

    string line;
    for (int i = 1; i <= 5; i++) {
        cin >> line;
        for (int j = 1; j <= 5; j++) {
            if (line.at(j-1) == '#') layout[i][j] = true;
        }
    }

    while (!seen[layout]) {
        seen[layout] = true;
        layout = process(layout);
    }

    cout << biodiversity(layout) << endl;

}
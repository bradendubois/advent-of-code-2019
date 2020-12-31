#include <iostream>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

typedef pair<int, int> asteroid;

int main() {

    vector<asteroid*> asteroids;
    asteroid *cur, *compare;

    int row = 0;
    string line;
    char c;
    while (getline(cin, line)) {

        for (int col = 0; col < line.size(); col++) {
            c = line[col];

            if (c == '#') {
                cur = (asteroid*) malloc(sizeof(asteroid));
                cur->first = row;
                cur->second = col;
                asteroids.push_back(cur);
            }
        }

        row++;
    }

    int best = 0, total, best_y, best_x;
    float result;
    set<float> blocked;
    for (int i = 0; i < asteroids.size(); i++) {

        total = 0;
        cur = asteroids[i];

        for (int j = 0; j < asteroids.size(); j++) {
            if (i == j) continue;
            compare = asteroids[j];
    
            result = atan2(cur->first - compare->first, cur->second - compare->second) * (180 / M_PIf32);

            if (blocked.count(result) == 0) {
                blocked.insert(result);
                total++;
            }
        }

        if (total > best) {
            best = total;
            best_y = cur->first;
            best_x = cur->second;
        }

        blocked.clear();
    }

    cout << best << " @ x = " << best_x << " & y = " << best_y << endl;
}
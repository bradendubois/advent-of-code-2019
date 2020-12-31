#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> asteroid;

int x = 28;
int y = 29;

float angle(asteroid *asteroid) {

    float rad = atan2(x - asteroid->first, y - asteroid->second);
    float degree = (180 / M_PIf32);

    float result = degree + 90.0;
    if (result > 360)
        result -= 360.0;

    return result;
}

float hypotenuse(asteroid *asteroid) {
    return hypot((float) abs(x - asteroid->second), (float) abs(y - asteroid->first));
}

int main() {

    vector<asteroid*> asteroids;
    asteroid *cur, *compare;

    int row = 0;
    string line;
    char c;
    while (getline(cin, line)) {

        for (int col = 0; col < line.size(); col++) {            
        
            if (row == y && col == x) {
                continue;
            }

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

    cur = nullptr;

    vector<bool> vaporized(asteroids.size(), false);

    int vaporize = 200;
    float start = 360.0;
    int j;
    while (vaporize--) {

        for (int i = 0; i < asteroids.size(); i++) {

            if (vaporized[i]) continue;

            compare = asteroids[i];
            if (angle(compare) < start) {

                if ((cur == nullptr) || angle(compare) > angle(cur) || 
                    (angle(cur) == angle(compare) && hypotenuse(compare) < hypotenuse(cur))) {
                    cur = compare;
                    j = i;
                }
            }
        }

        compare = nullptr;

        if (cur == nullptr) start = 360.0;
        else {
            vaporized[j] = true;
        }
    }    

    cout << cur->second * 100 + cur->first << endl;
}
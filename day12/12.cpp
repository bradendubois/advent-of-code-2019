#include <iostream>

#include "../Intcode.cpp"

long long GCD(long long a, long long b) {
    if (b == 0) {
        return a;
    }

    return GCD(b, a % b);
}

long long LCM(long long a, long long b) {
    return a * b / GCD(a, b);
}

int main() {


    int Io [] = {5, -1, 5, 0, 0, 0};
    int Europa [] = {0, -14, 2, 0, 0, 0};
    int Ganymede [] = {16, 4, 0, 0, 0, 0};
    int Callisto [] = {18, 1, 16, 0, 0, 0};

    int *moons[] = {Io, Europa, Ganymede, Callisto};

    map<string, long long> occur[3];
    long long LCMs [] = {0, 0, 0};

    long steps = 0, p1 = 0, p2;

    while (1) {

        // Velocity
        for (int first = 0; first < 4; first++) {
            for (int second = first + 1; second < 4; second++) {

                for (int axis = 0; axis < 3; axis++) {
                    
                    if (moons[first][axis] < moons[second][axis]) {

                        moons[first][axis+3]++;
                        moons[second][axis+3]--;

                    } else if (moons[first][axis] > moons[second][axis]) {

                        moons[first][axis+3]--;
                        moons[second][axis+3]++;

                    }

                }
            }
        }

        string reps[] = {"", "", ""};

        // Position
        for (int moon = 0; moon < 4; moon++) {
            for (int axis = 0; axis < 3; axis++) {
                moons[moon][axis] += moons[moon][axis+3];
                reps[axis] += to_string(moons[moon][axis]) + ",";
                reps[axis] += to_string(moons[moon][axis + 3]) + ",";
            }
        }

        steps++;

        // P1 - Energy
        if (steps == 1000) {
            for (int m = 0; m < 4; m++) {
                int *c = moons[m];
                int pos = abs(c[0]) + abs(c[1]) + abs(c[2]);
                int kin = abs(c[3]) + abs(c[4]) + abs(c[5]);
                p1 += pos * kin;
            }
        }
            

        // P2 - Break after each axis repeats
        for (int i = 0; i < 3; i++) {
            string rep = "";
            for (int moon = 0; moon < 4; moon++) {
                rep += to_string(moons[moon][i]) + "," + to_string(moons[moon][i+3]);
            }

            if (!LCMs[i] && occur[i][rep]) {
                LCMs[i] = steps - occur[i][rep];
            } else {
                occur[i][rep] = steps;
            }
        }


        if (steps >= 1000 && LCMs[0] && LCMs[1] && LCMs[2]) {
            break;
        }
    }


    cout << p1 << endl;
    cout << LCM(LCMs[0], LCM(LCMs[1], LCMs[2])) << endl;
}
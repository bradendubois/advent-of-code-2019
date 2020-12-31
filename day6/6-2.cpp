#include <iostream>
#include <map>
#include <vector>
#include <string.h>

using namespace std;

int main() {
    string in, s, t;
    map<string, string> orbit;
    map<string, int> count;
    vector<string> bodies;
    while (cin >> in) {
        s = in.substr(0,in.find(")")), t = in.substr(in.find(")") + 1);
        if (!count[s]) {
            count[s]++;
            bodies.push_back(s);
        }

        if (!count[t]) {
            count[t]++;
            bodies.push_back(t);
        }

        orbit[t] = s;
    }

    int orbits = 0;

    string body = orbit["SAN"];
    map<string, int> sanPath;
    int cost = 0;
    while (strcmp(body.c_str(), "COM") != 0) {
        cost++;
        body = orbit[body];
        sanPath[body] = cost;
    }

    body = orbit["YOU"];
    cost = 0;
    while (!sanPath[body]) {
        cost++;
        body = orbit[body];
    }

    cout << cost + sanPath[body] << endl;
}
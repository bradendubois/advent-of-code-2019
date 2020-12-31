#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int main() {
    string in;
    cin >> in;
    pair<int, int> best_count;
    best_count.first = INT32_MAX;
    while (in.size()) {
        map<int, int> pixel_count;
        int pixels = 25 * 6;
        while (pixels--) {
            int x = in.back();
            in.pop_back();

            // Pop_back gives a char, subtract to convert from char to int
            pixel_count[x - '0']++;
        }

        if (pixel_count[0] < best_count.first) {
            best_count.first = pixel_count[0];
            best_count.second = pixel_count[1] * pixel_count[2];
        }
    }

    cout << best_count.second << endl;
    
}
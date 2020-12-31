#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string in;
    cin >> in;
    pair<int, int> best_count;
    vector<vector<int>> layers;
    while (in.size()) {
        vector<int> layer;
        int pixels = 25 * 6;
        while (pixels--) {
            int x = in.back();
            in.pop_back();

            // Pop_back gives a char, subtract to convert from char to int
            layer.push_back(x - '0');
        }

        reverse(layer.begin(), layer.end());
        layers.push_back(layer);
    }

    reverse(layers.begin(), layers.end());


    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 25; col++) {
            for (int layer = 0; layer < 100; layer++) {
                int pixel = layers[layer][(row * 25) + col];
                if (pixel == 2) 
                    continue;
                else if (pixel == 1)
                    cout << "X";
                else
                    cout << " ";
                break;
            }
        } cout << endl;
    }
}
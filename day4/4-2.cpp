#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool repeat(vector<int> num) {
    for (int i = 0; i < num.size()-1; i++) {
        if (i == 0) {
            if (num[i] == num[i+1] && num[i+1] != num[i+2]) {
                return true;
            }
        } else if (i == num.size()-1) {
            if (num[i] == num[i+1] && num[i] != num[i-1]) {
                return true;
            }
        } else if (num[i-1] != num[i] && num[i] == num[i+1] && num[i+1] != num[i+2]) {
            return true;
        }
    }

    return false;
}

bool noDecrease(vector<int> num) {
    for (int i = 0; i < num.size()-1; i++) {
        if (num[i] > num[i+1]) return false;
    }
    return true;
}

int main() {
    int total = 0;
    for (int test = 124075; test <= 580769; test++) {
        int x = test;
        vector<int> in;
        while (x != 0) {
            int end = x % 10;
            in.push_back(end);
            x /= 10;
        } reverse(in.begin(), in.end());

        if (repeat(in) && noDecrease(in)) total++;
    }

    cout << total << endl;
}
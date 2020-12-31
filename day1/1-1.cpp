#include <iostream>

using namespace std;

int main() {
    int x, sum=0;
    while (cin >> x) sum += ((x / 3) - 2);
    cout << sum << endl;
}
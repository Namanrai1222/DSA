#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 5;
    vector<vector<int>> rows(n);
    int value = 1;

    for (int col = 1; col <= n; ++col) {
        for (int row = col; row <= n; ++row) {
            rows[row - 1].push_back(value++);
        }
    }

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < rows[row].size(); ++col) {
            cout << rows[row][col];
            if (col + 1 < rows[row].size()) {
                cout << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}

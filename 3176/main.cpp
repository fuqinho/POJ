#include <iostream>
#include <vector>
using namespace std;

int solve(vector< vector<int> > pins) {
    vector<int> dp(pins.size(), 0);
    for (int i = pins.size() - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = pins[i][j] + max(dp[j], dp[j+1]);
        }
    }
    return dp[0];
}

int main() {
    int N; cin >> N;
    vector< vector<int> > pins;
    for (int i = 0; i < N; i++) {
        vector<int> row;
        for (int j = 0; j <= i; j++) {
            int n; cin >> n;
            row.push_back(n);
        }
        pins.push_back(row);
    }
    cout << solve(pins) << endl;
}


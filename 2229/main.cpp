#include <iostream>
#include <vector>
using namespace std;

int solve(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        if (i % 2 == 0) dp[i] += dp[i / 2];
        dp[i] %= 1000000000;
    }
    return dp[n];
}

int main() {
    int n; cin >> n;
    cout << solve(n) << endl;
}

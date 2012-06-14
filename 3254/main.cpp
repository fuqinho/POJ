// Limit: 65536K  2000ms
// Used :   712K    16ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const int MOD = 100000000;

int solve(int M, int N, vector<int>& fertile) {
  vector<vector<int> > dp(2, vector<int>(1 << N));
  dp[0][0] = 1;

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < (1 << N); j++) {
      for (int k = 0; k < (1 << N); k++) {
        if (j & k) continue; // check vertical neighbor
        if (k & (k << 1)) continue; // check horizontal neighbor
        if (k & ~fertile[i]) continue; // check fertility

        dp[(i+1)&1][k] += dp[i&1][j];
        dp[(i+1)&1][k] %= MOD;
      }
    }
    fill(dp[i&1].begin(), dp[i&1].end(), 0);
  }

  return accumulate(dp[M&1].begin(), dp[M&1].end(), 0LL) % MOD;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int M, N; cin >> M >> N;
  vector<int> fertile(M);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int f; cin >> f;
      if (f == 1) fertile[i] |= (1 << j);
    }
  }

  int ans = solve(M, N, fertile);
  cout << ans << endl;
}

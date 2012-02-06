#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int solve(int T, int W, vector<int>& data) {
  VVI dp(W+1, VI(T+1, 0));
  REP(i, W+1) {
    for (int j = 1; j <= T; j++) {
      if (i == 0) {
        dp[i][j] = dp[i][j-1] + ((i % 2 == data[j-1] - 1) ? 1 : 0);
      } else {
        dp[i][j] = max(dp[i][j-1] + ((i % 2 == data[j-1] - 1) ? 1 : 0), 
            dp[i-1][j-1] + (((i-1) % 2 == data[j-1] - 1) ? 1 : 0));
      }
    }
  }
  /*
  REP(i, W+1) {
    REP(j, T+1) cerr << dp[i][j] << " ";
    cerr << endl;
  }
  */
  return dp[W][T];
}

int main() {
  int T, W;
  scanf("%d %d", &T, &W);
  vector<int> data(T);
  REP(i, T) {
    int t;
    scanf("%d", &t);
    data[i] = t;
  }
  int answer = solve(T, W, data);
  cout << answer << endl;
}


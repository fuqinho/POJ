#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dumpv(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d){return s<<"("<<d.first<<","<<d.second<<")";}

const int MAX_F = 1000;
const int MAX_N = 100;
const int MAX_V = MAX_F * MAX_N;
int dp[2][MAX_V * 2 + 2];

const int INF = 100000000;

int solve(int N, vector<int>& S, vector<int>& F) {
  vector<int> SUM(N);
  for (int i = 0; i < N; i++) SUM[i] = S[i] + F[i];

  // dp[i][MAX_V+j]: i番目の牛までの中で、TSをjにした時のTS+FSの最大値
  REP(i, 2) REP(j, MAX_V * 2 + 2) dp[i][j] = -INF;
  dp[0][MAX_V] = 0;

  for (int i = 1; i <= N; i++) {
    int prev = ((i-1) & 1);
    int cur = (i & 1);
    for (int j = 0; j <= 2 * MAX_V; j++) {
      if (dp[prev][j] != -INF) {
        dp[cur][j] = max(dp[cur][j], dp[prev][j]);
      }
      if (j-S[i-1] >= 0 && j - S[i-1] < MAX_V * 2 + 2 && dp[prev][j-S[i-1]] != -INF) {
        dp[cur][j] = max(dp[cur][j], dp[prev][j-S[i-1]] + SUM[i-1]);
      }
    }
  }

  int res = -INF;
  for (int i = MAX_V; i < MAX_V * 2 + 2; i++) {
    if(dp[N&1][i] != -INF && dp[N&1][i] >= (i-MAX_V)) {
      res = max(res, dp[N&1][i]);
    }
  }
  
  return res;
}

int main() {
  int N; scanf("%d", &N);
  vector<int> S(N), F(N);
  REP(i, N) scanf("%d %d", &S[i], &F[i]);

  int ans = solve(N, S, F);
  printf("%d\n", ans);
}


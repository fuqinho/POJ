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
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dumpv(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d){return s<<"("<<d.first<<","<<d.second<<")";}

const int MAX_T = 1000;
const int MAX_N = 100000;
const int MOD = 1000000;

LL dp[2][MAX_N+1];

LL solve(int T, int A, int S, int B, vector<int>& ants) {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  
  for (int i = 1; i <= T; i++) {
    int prev_idx = ((i-1) & 1);
    int idx = (i & 1);
    long long sum = 0;
    for (int j = 0; j <= B; j++) {
      sum += dp[prev_idx][j];
      dp[idx][j] = sum % MOD;
      if (j >= ants[i-1]) sum -= dp[prev_idx][j-ants[i-1]];
    }
  }
  
  LL res = 0;
  int t_idx = (T & 1);
  for (int i = S; i <= B; i++) {
    res += dp[t_idx][i];
    res %= MOD;
  }
  return res % MOD;
}

int main() {
  int T, A, S, B;
  scanf("%d %d %d %d", &T, &A, &S, &B);

  vector<int> ants(T, 0);
  REP(i, A) {
    int n; scanf("%d", &n);
    ants[n-1]++;
  }

  LL ans = solve(T, A, S, B, ants);
  printf("%lld\n", ans);
}

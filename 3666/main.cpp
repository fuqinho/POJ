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

vector<int> V;
vector<int> A;

const LL INF = 10000000000000000;

LL solve() {
  vector<vector<LL> > dp(A.size(), vector<LL>(V.size(), INF));

  for (int i = 0; i < A.size(); i++) {
    LL minVal = INF;
    for (int j = 0; j < V.size(); j++) {
      LL val = abs(V[A[i]] - V[j]);
      if (i > 0) val += dp[i-1][j];
      minVal = min(minVal, val);
      dp[i][j] = minVal;
    }
  }
  return dp[A.size()-1][V.size()-1];
}

int main() {
  int N; scanf("%d", &N);
  A = vector<int>(N);
  REP(i, N) scanf("%d", &A[i]);
  V = A;
  sort(V.begin(), V.end());
  V.erase(unique(V.begin(), V.end()), V.end());
  
  REP(i, N) A[i] = lower_bound(V.begin(), V.end(), A[i]) - V.begin();

  LL ans = solve();
  reverse(A.begin(), A.end());
  ans = min(ans, solve());

  printf("%lld\n", ans);
}


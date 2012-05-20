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

/*
int solve(int n, vector<PII>& sticks) {
  sort(sticks.begin(), sticks.end());
  vector<int> dp(n, 0);
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (sticks[j].second > sticks[i].second) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  return *max_element(dp.begin(), dp.end());
}
*/

const int INF = 100000000;

int solve(int n, vector<PII>& sticks) {
  sort(sticks.begin(), sticks.end());
  vector<int> dp(n, INF);
  for (int i = 0; i < n; i++) {
    int num = -sticks[i].second;
    *lower_bound(dp.begin(), dp.end(), num) = num;
  }
  return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

int main() {
  int T; scanf("%d", &T);
  for (int t = 0; t < T; t++) {
    int n; scanf("%d", &n);
    vector<PII> sticks(n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &sticks[i].first, &sticks[i].second);
    }

    int ans = solve(n, sticks);
    printf("%d\n", ans);
  }
}

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

const int MAX_N = 100;
const int MAX_M = 100000;
int dp[MAX_M+1];

int solve(int n, int m, vector<int>& A, vector<int>& C) {
  memset(dp, -1, sizeof(dp));

  dp[0] = C[0];
  
  REP(i, n) {
    for (int j = 0; j <= m; j++) {
      if (dp[j] != -1) dp[j] = C[i];

      if (dp[j] == -1) {
        if (j >= A[i] && dp[j-A[i]] != -1) {
          dp[j] = dp[j-A[i]] - 1;
        }
      }
    }
  }
  
  int sum = 0;
  for (int j = 1; j <= m; j++) if (dp[j] != -1) sum++;
  return sum;
}

int main() {
  while (true) {
    int n, m;
    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0) break;
    vector<int> A(n), C(n);
    REP(i, n) scanf("%d", &A[i]);
    REP(i, n) scanf("%d", &C[i]);

    int ans = solve(n, m, A, C);
    printf("%d\n", ans);
  }
}


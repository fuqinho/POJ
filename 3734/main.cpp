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
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& data) {
  return stream << "(" << data.first << "," << data.second << ")";
}

const int MOD = 10007;

VVI mul(VVI& m1, VVI& m2) {
  VVI res(m1.size(), VI(m2.size(), 0));
  REP(i, m1.size()) {
    REP(j, m2[i].size()) {
      REP(k, m1[i].size()) {
        res[i][j] += m1[i][k] * m2[k][j];
        res[i][j] %= MOD;
      }
    }
  }
  return res;
}

int solve(int n) {
  VVI res(3, VI(3, 0));
  res[0][0]=2; res[0][1]=1; res[0][2]=0;
  res[1][0]=2; res[1][1]=2; res[1][2]=2;
  res[2][0]=0; res[2][1]=1; res[2][2]=2;

  VVI ans(3, VI(3, 0));
  ans[0][0] = ans[1][1] = ans[2][2] = 1;

  while (n > 0) {
    if (n & 1) ans = mul(ans, res);
    res = mul(res, res);
    n >>= 1;
  }
  return ans[0][0];
}

int main() {
  int t; cin >> t;
  REP(i, t) {
    int n; cin >> n;
    cout << solve(n) << endl;
  }
}


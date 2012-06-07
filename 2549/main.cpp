#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)

#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

const int INF = 1000000000;

int solve(vector<int>& a) {
  int res = -INF;
  
  int n = a.size();
  vector<pair<int, PII> > ab;
  REP(i, n) REP(j, n) {
    if (i != j) ab.push_back(make_pair(a[i]+a[j], PII(i, j)));
  }
  sort(ab.begin(), ab.end());

  REP(i, n) {
    int d = a[i];
    REP(j, n) {
      if (j == i) continue;
      int c = a[j];
      int e = d - c;
      
      vector<pair<int, PII> >::iterator it_b = lower_bound(
          ab.begin(), ab.end(), make_pair(e, PII(0, 0)));
      vector<pair<int, PII> >::iterator it_e = lower_bound(
          ab.begin(), ab.end(), make_pair(e+1, PII(0, 0)));

      for (vector<pair<int, PII> >::iterator it = it_b; it != it_e; it++) {
        if (it->second.first != i && it->second.second != i &&
            it->second.first != j && it->second.second != j) {
          res = max(res, d);
        }
      }
    }
  }
  return res;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    VI a(n);
    REP(i, n) cin >> a[i];
    int ans = solve(a);
    if (ans == -INF) {
      cout << "no solution" << endl;
    } else {
      cout << ans << endl;
    }
  }
}

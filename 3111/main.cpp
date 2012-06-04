// Used : 3440K	5766MS
#include <iostream>
#include <vector>
#include <numeric>
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

bool C(int k, VI& v, VI& w, double s) {
  vector<double> c(v.size());
  REP(i, v.size()) {
    c[i] = (double)v[i] - s*w[i];
  }
  sort(c.rbegin(), c.rend());
  
  return accumulate(c.begin(), c.begin()+k, 0.0) >= 0.0;
}

VI jowels(int k, VI& v, VI& w, double s) {
  vector<pair<double, int> > c(v.size());
  REP(i, v.size()) {
    c[i] = make_pair((double)v[i] - s*w[i], i);
  }
  sort(c.rbegin(), c.rend());

  VI res(k);
  REP(i, k) res[i] = c[i].second + 1;
  return res;
}

VI solve(int k, VI& v, VI& w) {
  double lb = 0.0, ub = 1e7;
  while (ub - lb > 1e-9) {
    double mid = (ub + lb) / 2;
    if (C(k, v, w, mid)) lb = mid;
    else ub = mid;
  }
  return jowels(k, v, w, lb);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, k; cin >> n >> k;
  VI v(n), w(n);
  REP(i, n) cin >> v[i] >> w[i];

  VI ans = solve(k, v, w);
  REP(i, ans.size()) cout << ans[i] << " ";
  cout << endl;
}

// Used : 1112K	1766MS
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

int C(VI& a, int k, int min) {
  LL used_k = 0;
  REP(i, a.size()) {
    if (a[i] > (LL)k * min) return false;

    int over = a[i] - min;
    if (over > 0) used_k += (over-1) / (k-1) + 1;
  }
  return used_k <= min;
}

int solve(int n, VI& a, int k) {
  int lb = -1;
  int ub = *max_element(a.begin(), a.end());
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(a, k, mid)) ub = mid;
    else lb = mid;
  }
  return ub;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int n; cin >> n;
  VI a(n);
  REP(i, n) cin >> a[i];
  int k; cin >> k;

  int ans = solve(n, a, k);
  cout << ans << endl;
}

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
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


bool isInside(int i, int j, vector<double>& x, vector<double>& y, vector<double>& R) {
  bool res = sqrt((x[j]-x[i]) * (x[j]-x[i]) + (y[j]-y[i]) * (y[j]-y[i])) + R[i] < R[j];
  return res;
}

int main() {
  int N; scanf("%d", &N);
  vector<double> x(N), y(N), R(N);
  REP(i, N) {
    scanf("%lf %lf %lf", &R[i], &x[i], &y[i]);
  }

  vector<pair<double, int> > circles;
  REP(i, N) {
    circles.push_back(make_pair(x[i]-R[i], i));
    circles.push_back(make_pair(x[i]+R[i], i + N));
  }
  sort(ALL(circles));

  set<pair<double, int> > outers;
  VI ans;
  REP(i, circles.size()) {
    int idx = circles[i].second % N;
    if (circles[i].second < N) {
      set<pair<double, int> >::iterator itr = outers.lower_bound(make_pair(y[idx], idx));
      if (itr != outers.end() && isInside(idx, itr->second, x, y, R)) continue;
      if (itr != outers.begin() && isInside(idx, (--itr)->second, x, y, R)) continue;
      outers.insert(make_pair(y[idx], idx));
      ans.push_back(idx);
    } else {
      outers.erase(make_pair(y[idx], idx));
    }
  }

  sort(ALL(ans));
  cout << ans.size() << endl;
  REP(i, ans.size()) cout << ans[i]+1 << " "; cout << endl;
}


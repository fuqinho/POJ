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


bool solve(int n, VI& p) {
  int mask = 0;
  VI v;

  if (n % 2 == 0) {
    REP(i, n/2) {
      v.push_back(p[i*2+1] - p[i*2] - 1);
    }
  } else {
    v.push_back(p[0] - 1);
    REP(i, n/2) {
      v.push_back(p[i*2+2] - p[i*2+1] - 1);
    }
  }

  //dumpv(v);

  REP(i, v.size()) mask ^= v[i];

  return mask != 0;
}

int main() {
  int T; scanf("%d", &T);
  REP(t, T) {
    int n; scanf("%d", &n);
    VI p(n);
    REP(i, n) scanf("%d", &p[i]);
    sort(ALL(p));

    bool res = solve(n, p);
    cout << (res ? "Georgia" : "Bob") << " will win" << endl;
  }
}


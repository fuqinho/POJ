// Limit: 10000K 1000ms
// Used :   916K   47ms
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
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


int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while (cin >> N) {
    VVI d(N, VI(N));
    REP(i, N) REP(j, N) cin >> d[i][j];

    vector<bool> used(N, false);
    priority_queue<PII, vector<PII>, greater<PII> > que;
    que.push(PII(0, 0));

    int cost = 0;
    while (!que.empty()) {
      PII p = que.top(); que.pop();
      if (!used[p.second]) {
        used[p.second] = true;
        cost += p.first;
        REP(i, N) {
          if (!used[i]) que.push(PII(d[p.second][i], i));
        }
      }
    }
    cout << cost << endl;
  }
}

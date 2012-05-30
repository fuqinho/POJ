// Limit: 65536K  2000MS
// Used :   792K   391MS
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

const int INF = 1e9;

struct edge {
  int to, dist;
  edge(int t, int d) : to(t), dist(d) {}
};

bool solve(int N, vector<vector<edge> >& G) {
  vector<int> dist(N, INF);
  dist[0] = 0;
  REP(k, N) {
    bool updated = false;
    REP(i, N) if (dist[i] != INF) {
      REP(j, G[i].size()) {
        edge& e = G[i][j];
        if (dist[i] + e.dist < dist[e.to]) {
          dist[e.to] = dist[i] + e.dist;
          updated = true;
        }
      }
    }
    if (!updated) break;
    if (k == N-1) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int F; cin >> F;
  REP(f, F) {
    int N, M, W; cin >> N >> M >> W;
    vector<vector<edge> > G(N);
    REP(i, M) {
      int S, E, T; cin >> S >> E >> T;
      G[S-1].push_back(edge(E-1, T));
      G[E-1].push_back(edge(S-1, T));
    }
    REP(i, W) {
      int S, E, T; cin >> S >> E >> T;
      G[S-1].push_back(edge(E-1, -T));
    }
    
    bool ans = solve(N, G);
    cout << (ans ? "YES" : "NO") << endl;
  }
}


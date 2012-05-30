// Limit: 65536K 2000MS
// Used :   988K	 94MS
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

struct edge {
  int to, cost;
  edge(int t, int c): to(t), cost(c) {}
};

const int INF = 1e9;

vector<int> dijkstra(int N, int X, vector<vector<edge> >& G) {
  vector<int> dist(N, INF);
  priority_queue<PII, vector<PII>, greater<PII> > que;

  que.push(PII(0, X-1));
  while (!que.empty()) {
    PII p = que.top(); que.pop();
    int d = p.first;
    int v = p.second;
    if (dist[v] == INF) {
      dist[v] = d;
      REP(i, G[v].size()) {
        edge& e = G[v][i];
        if (dist[e.to] == INF) {
          que.push(PII(dist[v] + e.cost, e.to));
        }
      }
    }
  }
  return dist;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int N, M, X; cin >> N >> M >> X;
  vector<vector<edge> > G1(N), G2(N);
  REP(i, M) {
    int A, B, T; cin >> A >> B >> T;
    G1[A-1].push_back(edge(B-1, T));
    G2[B-1].push_back(edge(A-1, T));
  }

  vector<int> dist1 = dijkstra(N, X, G1);
  vector<int> dist2 = dijkstra(N, X, G2);
  int ans = 0;
  REP(i, N) ans = max(ans, dist1[i] + dist2[i]);
  cout << ans << endl;
}


// Used : 1032K	188MS
#include <iostream>
#include <vector>
#include <queue>
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

struct Edge {
  int to, cost;
  Edge(int t, int c): to(t), cost(c) {}
};

const int INF = 1000000000; 
const int MAX_N = 1000;
int N, P, K;
vector<Edge> G[MAX_N];

int dijkstra(int x) {
  vector<int> dist(N, INF);
  priority_queue<PII, vector<PII>, greater<PII> > que;
  
  dist[0] = 0;
  que.push(PII(0, 0));

  while (!que.empty()) {
    int d = que.top().first;
    int v = que.top().second;
    que.pop();
    if (d > dist[v]) continue;

    REP(i, G[v].size()) {
      Edge& e = G[v][i];
      int cost = e.cost > x ? 1 : 0;
      if (dist[e.to] > d + cost) {
        dist[e.to] = d + cost;
        que.push(PII(d + cost, e.to));
      }
    }
  }
  return dist[N-1];
}

int solve() {
  int lb = -1, ub = 1000001;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (dijkstra(mid) <= K) {
      ub = mid;
    } else {
      lb = mid;
    }
  }
  return (ub == 1000001 ? -1 : ub);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> N >> P >> K;
  REP(i, P) {
    int a, b, l; cin >> a >> b >> l;
    G[a-1].push_back(Edge(b-1, l));
    G[b-1].push_back(Edge(a-1, l));
  }

  int ans = solve();
  cout << ans << endl;
}

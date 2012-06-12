// Limit: 65536K 2000ms
// Used :  4364K 1282ms
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

const int INF = 1000000000;
const int MAX_N = 50000;

struct Edge {
  int from, to, cost;
  Edge(int f, int t, int c): from(f), to(t), cost(c) {}
};

// d[50000] から d[0] への最短距離を求める
int bellman_ford(vector<Edge>& edges) {
  // dist[50000]を0とすると、コスト0の辺が全体に貼られてるので、
  // 明らかにdist[i]は0以下にはなる。よって0で初期化する。
  vector<int> dist(MAX_N+1, 0);
  REP(i, MAX_N+1) {
    bool updated = false;
    REP(j, edges.size()) {
      Edge& e = edges[j];
      if (dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        updated = true;
      }
    }
    if (!updated) {
      return dist[0];
    }
  }
  return INF;
}

int solve(vector<int>& a, vector<int>& b, vector<int>& c) {
  vector<Edge> edges;
  // d[i+1] - d[i] <= 1 より、iからi+1にコスト1の辺を張る
  for (int i = 0; i < MAX_N; i++) {
    edges.push_back(Edge(i, i+1, 1));
  }
  // d[i+1] >= d[i] より、iからi+1にコスト0の辺を張る
  for (int i = 0; i < MAX_N; i++) {
    edges.push_back(Edge(i+1, i, 0));
  }
  // d[b] - d[a-1] >= c より、bからa-1にコスト-cの辺を張る
  for (int i = 0; i < a.size(); i++) {
    edges.push_back(Edge(b[i], a[i]-1, -c[i]));
  }

  int min_dist = bellman_ford(edges);
  return -min_dist;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n), b(n), c(n);
  REP(i, n) cin >> a[i] >> b[i] >> c[i];

  int ans = solve(a, b, c);
  cout << ans << endl;
}

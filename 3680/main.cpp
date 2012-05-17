#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

static const int INF = 100000000;

class MinCostFlowGraph {
public:
  MinCostFlowGraph(int n) {
    G = vector<vector<edge> >(n);
    h = vector<int>(n);
    dist = vector<int>(n);
    prevv = vector<int>(n);
    preve = vector<int>(n);
  }
  void AddEdge(int from, int to, int cap, int cost) {
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
  }
  int MinCostFlow(int s, int t, int f) {
    fill(h.begin(), h.end(), 0);
    int cost = 0;
    while (f > 0) {
      // ダイクストラで最短パスを求める
      priority_queue<PII, vector<PII>, greater<PII> > que;
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      que.push(PII(dist[s], s));
      while (!que.empty()) {
        PII p = que.top(); que.pop();
        int v = p.second;
        if (p.first <= dist[v]) {
          for (int i = 0; i < G[v].size(); i++) {
            edge& e = G[v][i];
            if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
              dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
              prevv[e.to] = v;
              preve[e.to] = i;
              que.push(PII(dist[e.to], e.to));
            }
          }
        }
      }
      if (dist[t] == INF) return -1;
      for (int i = 0; i < dist.size(); i++) h[i] += dist[i];

      // 最短パスに目一杯流す
      int d = f;
      for (int v = t; v != s; v = prevv[v]) {
        d = min(d, G[prevv[v]][preve[v]].cap);
      }
      f -= d;
      cost += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        G[prevv[v]][preve[v]].cap -= d;
        G[v][G[prevv[v]][preve[v]].rev].cap += d;
      }
    }
    return cost;
  }
private:
  struct edge {
    int to, cap, cost, rev;
    edge(int t, int c, int co, int r):to(t),cap(c),cost(co),rev(r){}
  };
  typedef pair<int, int> PII;
  vector<vector<edge> > G;
  vector<int> h;
  vector<int> dist;
  vector<int> prevv;
  vector<int> preve;
};

int solve(int N, int K, vector<int>& a, vector<int>& b, vector<int>& w) {
  vector<int> pos;
  for (int i = 0; i < N; i++) {
    pos.push_back(a[i]);
    pos.push_back(b[i]);
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());

  int S = pos.size();
  int T = pos.size() + 1;
  MinCostFlowGraph graph(pos.size() + 2);
  graph.AddEdge(S, 0, K, 0);
  graph.AddEdge(pos.size()-1, T, K, 0);
  for (int i = 0; i < pos.size()-1; i++) {
    graph.AddEdge(i, i+1, INF, 0);
  }
  int res = 0;
  for (int i = 0; i < N; i++) {
    int apos = lower_bound(pos.begin(), pos.end(), a[i]) - pos.begin();
    int bpos = lower_bound(pos.begin(), pos.end(), b[i]) - pos.begin();
    graph.AddEdge(bpos, apos, 1, w[i]);
    graph.AddEdge(S, bpos, 1, 0);
    graph.AddEdge(apos, T, 1, 0);
    res -= w[i];
  }

  int cost = graph.MinCostFlow(S, T, K + N);
  res += cost;

  return -res;
}

int main() {
  int T; scanf("%d", &T);
  for (int i = 0; i < T; i++) {
    int N, K; scanf("%d %d", &N, &K);
    vector<int> a(N), b(N), w(N);
    for (int j = 0; j < N; j++) {
      scanf("%d %d %d", &a[j], &b[j], &w[j]);
    }
    int ans = solve(N, K, a, b, w);
    cout << ans << endl;
  }
}

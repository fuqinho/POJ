#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

static const int INF = 100000000;
static const int MAX_V = 10000;

typedef pair<int, int> PII;
struct edge {
  int to, cap, cost, rev;
  edge(int t, int ca, int co, int r):to(t),cap(ca),cost(co),rev(r){}
};

int V;
vector<edge> G[MAX_V];
int h[MAX_V]; // potential
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
  G[from].push_back(edge(to, cap, cost, G[to].size()));
  G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
}

int min_cost_flow(int s, int t, int f) {
  int res = 0;
  fill(h, h + V, 0); // ポテンシャルを初期化
  while (f > 0) {

    // ダイクストラ法を用いてポテンシャルを更新する
    priority_queue<PII, vector<PII>, greater<PII> > que;
    fill(dist, dist + V, INF);
    dist[s] = 0;
    que.push(PII(0, s)); // pairは(最短距離, 頂点のindex)
    while (!que.empty()) {
      PII p = que.top(); que.pop();
      int v = p.second;
      if (dist[v] < p.first) continue;

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
    // Sinkまでのパスが無くなればもうこれ以上流せない
    if (dist[t] == INF) {
      return -1;
    }
    // ポテンシャル更新
    for (int v = 0; v < V; v++) h[v] += dist[v];

    // s-t間最短路(最小コストのパス)に沿って目一杯流す
    int d = f;
    for (int v = t; v != s; v = prevv[v]) {
      d = min(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for (int v = t; v != s; v = prevv[v]) {
      edge& e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}


int main() {
  int N, M; scanf("%d %d", &N, &M);
  V = N;
  for (int i = 0; i < M; i++) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    add_edge(a-1, b-1, 1, c);
    add_edge(b-1, a-1, 1, c);
  }

  int ans = min_cost_flow(0, N-1, 2);
  cout << ans << endl;
}

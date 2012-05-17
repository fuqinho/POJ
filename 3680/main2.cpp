#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

static const int INF = 100000000;
static const int MAX_V = 402;

typedef pair<int, int> P;
struct edge{ int to, cap, cost, rev; };

vector<edge> G[MAX_V];
int V;
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
  G[from].push_back((edge){to, cap, cost, G[to].size()});
  G[to].push_back((edge){from, 0, -cost, G[from].size()-1});
}

int min_cost_flow(int s, int t, int f) {
  int res = 0;
  fill(h, h + V, 0);
  while (f > 0) {
    priority_queue<P, vector<P>, greater<P> > que;
    fill(dist, dist + V, INF);
    dist[s] = 0;
    que.push(P(0, s));
    while (!que.empty()) {
      P p = que.top(); que.pop();
      int v = p.second;
      if (dist[v] < p.first) continue;
      for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
          dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
          prevv[e.to] = v;
          preve[e.to] = i;
          que.push(P(dist[e.to], e.to));
        }
      }
    }
    if (dist[t] == INF) return -1;
    for (int v = 0; v < V; v++) h[v] += dist[v];

    int d = f;
    for (int v = t; v != s; v = prevv[v]) {
      d = min(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for (int v = t; v != s; v = prevv[v]) {
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}

int solve(int N, int K, vector<int>& a, vector<int>& b, vector<int>& w) {

  vector<int> pos;
  for (int i = 0; i < N; i++) {
    pos.push_back(a[i]);
    pos.push_back(b[i]);
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());

  // init data
  V = pos.size() + 2;
  for (int i = 0; i < V; i++) G[i].clear();

  int S = pos.size();
  int T = pos.size() + 1;
  add_edge(S, 0, K, 0);
  add_edge(pos.size()-1, T, K, 0);
  for (int i = 0; i < pos.size()-1; i++) {
    add_edge(i, i+1, INF, 0);
  }
  int res = 0;
  for (int i = 0; i < N; i++) {
    int apos = find(pos.begin(), pos.end(), a[i]) - pos.begin();
    int bpos = find(pos.begin(), pos.end(), b[i]) - pos.begin();
    add_edge(bpos, apos, 1, w[i]);
    add_edge(S, bpos, 1, 0);
    add_edge(apos, T, 1, 0);
    res -= w[i];
  }

  int cost = min_cost_flow(S, T, K + N);
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
    printf("%d\n", ans);
  }
}

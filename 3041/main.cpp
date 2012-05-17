#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

static const int INF = 100000000;
static const int MAX_V = 10000;

struct edge {
  int to, cap, rev;
  edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

vector<edge> G[MAX_V];
vector<bool> used(MAX_V);

void add_edge(int from, int to, int cap) {
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size()-1));
}

int find_arg_path(int v, int t, int f) {
  if (v == t) return f;

  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    edge& e = G[v][i];
    if (!used[e.to] && e.cap > 0) {
      int d = find_arg_path(e.to, t, min(f, e.cap));
      if (d != 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  
  return 0;
}

int max_flow(int s, int t) {
  int flow = 0, f;
  do {
    fill(used.begin(), used.end(), 0);
    f = find_arg_path(s, t, INF);
    flow += f;
  } while (f != 0);
  return flow;
}

int main() {
  int N, K; scanf("%d %d", &N, &K);
  vector<pair<int, int> > P(K);
  for (int i=0; i<K; i++) scanf("%d %d", &P[i].first, &P[i].second);

  for (int i=0; i<N; i++) {
    add_edge(2*N, i, 1);
    add_edge(N+i, 2*N+1, 1);
  }

  for (int i=0; i<K; i++) {
    add_edge((P[i].first-1), N+(P[i].second-1), 1);
  }

  int ans = max_flow(2*N, 2*N+1);
  cout << ans << endl;
}

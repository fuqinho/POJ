#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

static const int INF = 1000000000;
static const int MAX_V = 200002;

struct edge {
  int to, cap, rev;
  edge(int t, int c, int r):to(t),cap(c),rev(r){}
};

vector<edge> G[MAX_V];
vector<int> level(MAX_V);
vector<int> iter(MAX_V);

void add_edge(int from, int to, int cap) {
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size()-1));
}

void bfs(int s) {
  fill(level.begin(), level.end(), -1);
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    for (int i = 0; i < G[v].size(); i++) {
      edge& e = G[v][i];
      if (e.cap > 0 && level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int dfs(int v, int t, int f) {
  if (v == t) return f;
  for (int& i = iter[v]; i < G[v].size(); i++) {
    edge& e = G[v][i];
    if (e.cap > 0 && level[v] < level[e.to]) {
      int d = dfs(e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

long long max_flow(int s, int t) {
  long long flow = 0;
  while (true) {
    bfs(s);
    if (level[t] < 0) break;
    fill(iter.begin(), iter.end(), 0);
    int f;
    while ((f = dfs(s, t, INF)) > 0) {
      flow += f;
    }
  }
  return flow;
}

int main() {
  int N, M; scanf("%d %d", &N, &M);
  int s = N, t = N+1;
  for (int i = 0; i < N; i++) {
    int A, B; scanf("%d %d", &A, &B);
    add_edge(s, i, B);
    add_edge(i, t, A);
  }
  for (int i = 0; i < M; i++) {
    int a, b, w; scanf("%d %d %d", &a, &b, &w);
    add_edge(a-1, b-1, w);
    add_edge(b-1, a-1, w);
  }

  long long answer = max_flow(s, t);
  cout << answer << endl;
}

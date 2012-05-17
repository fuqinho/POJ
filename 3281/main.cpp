#include <iostream>
#include <vector>
using namespace std;

static const int INF = 100000000;
static const int MAX_V = 1000;

struct edge {
  int to, cap, rev;
  edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

vector<edge> G[MAX_V];
vector<bool> used(MAX_V, false);

void add_edge(int from, int to, int cap) {
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size()-1));
}

int dfs(int v, int t, int f) {
  if (v == t) return f;
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    edge& e = G[v][i];
    if (!used[e.to] && e.cap > 0) {
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

int max_flow(int s, int t) {
  int flow = 0;
  for (;;) {
    fill(used.begin(), used.end(), false);
    int f = dfs(s, t, INF);
    if (f == 0) break;
    flow += f;
  }
  return flow;
}

int main() {
  int N, F, D; cin >> N >> F >> D;

  int FOOD_TOP = 2;
  int COW1_TOP = FOOD_TOP + F;
  int COW2_TOP = COW1_TOP + N;
  int DRINK_TOP = COW2_TOP + N;

  for (int i = 0; i < F; i++) {
    add_edge(0, FOOD_TOP + i, 1);
  }
  for (int i = 0; i < N; i++) {
    add_edge(COW1_TOP + i, COW2_TOP + i, 1);
  }
  for (int i = 0; i < D; i++) {
    add_edge(DRINK_TOP + i, 1, 1);
  }

  for (int i = 0; i < N; i++) {
    int fnum, dnum; cin >> fnum >> dnum;
    for (int j = 0; j < fnum; j++) {
      int f; cin >> f; f--;
      add_edge(FOOD_TOP + f, COW1_TOP + i, 1);
    }
    for (int j = 0; j < dnum; j++) {
      int d; cin >> d; d--;
      add_edge(COW2_TOP + i, DRINK_TOP + d, 1);
    }
  }

  int answer = max_flow(0, 1);
  cout << answer << endl;
}

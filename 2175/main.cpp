#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;

class MinCostFlowGraph {
public:
  MinCostFlowGraph(int n) : INF(100000000) {
    G = vector<vector<edge> >(n);
    h = vector<int>(n);
    dist = vector<int>(n);
    prevv = vector<int>(n);
    preve = vector<int>(n);
  }
  void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
  }
  int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill(h.begin(), h.end(), 0);
    while (f > 0) {
      priority_queue<PII, vector<PII>, greater<PII> > que;
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      que.push(PII(0, s));
      while (!que.empty()) {
        PII p = que.top(); que.pop();
        int v = p.second;
        if (dist[v] >= p.first) {
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
      for (int v = 0; v < h.size(); v++) h[v] += dist[v];
      int d = f;
      for (int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
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
  int get_cap(int v, int e) {
    return G[v][e].cap;
  }
private:
  const int INF;
  typedef pair<int, int> PII;
  struct edge {
    int to, cap, cost, rev;
    edge(int t, int ca, int co, int r):to(t),cap(ca),cost(co),rev(r){}
  };
  vector<vector<edge> > G;
  vector<int> h, dist, prevv, preve;
};

int main() {
  int N, M; scanf("%d %d", &N, &M);

  int S = 0, T = 1, BS = 2, SS = BS + N; 
  MinCostFlowGraph graph(2 + N + M);
  int peopleNum = 0;

  vector<pair<int, int> > building;
  for (int i = 0; i < N; i++) {
    int x, y, c; scanf("%d %d %d", &x, &y, &c);
    building.push_back(make_pair(x, y));
    graph.add_edge(S, BS+i, c, 0);
    peopleNum += c;
  }

  vector<pair<int, int> > shelter;
  for (int i = 0; i < M; i++) {
    int x, y, c; scanf("%d %d %d", &x, &y, &c);
    shelter.push_back(make_pair(x, y));
    graph.add_edge(SS+i, T, c, 0);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int cost = abs(building[i].first - shelter[j].first) + 
        abs(building[i].second - shelter[j].second) + 1;
      graph.add_edge(BS+i, SS+j, 1000000, cost);
    }
  }

  int pcost = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int d; scanf("%d", &d);
      pcost += d * (abs(building[i].first - shelter[j].first) + 
        abs(building[i].second - shelter[j].second) + 1);
    }
  }

  int mincost = graph.min_cost_flow(S, T, peopleNum);
  if (mincost < pcost) {
    cout << "SUBOPTIMAL" << endl;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int cap = graph.get_cap(SS+j, i+1);
        cout << cap << " ";
      }
      cout << endl;
    }
  } else {
    cout << "OPTIMAL" << endl;
  }
}

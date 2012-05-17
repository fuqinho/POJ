#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int INF = 100000000;
const int MAX_N = 100;
const int MAX_M = 100;
int N, M;
int X[MAX_N], Y[MAX_N], B[MAX_N];
int P[MAX_M], Q[MAX_M], C[MAX_M];
int E[MAX_N][MAX_M];

const int MAX_V = MAX_N + MAX_M + 1;
int g[MAX_V][MAX_V];
int prev[MAX_V][MAX_V];

void printE() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (j < M - 1) cout << E[i][j] << " ";
      else cout << E[i][j] << endl;
    }
  }
}

void solve() {
  int V = N + M + 1;

  // init graph
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) g[i][j] = INF;
  }

  // construct graph
  for (int j = 0; j < M; j++) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
      int cost = abs(X[i]-P[j]) + abs(Y[i]-Q[j]) + 1;
      g[i][N+j] = cost;
      if (E[i][j] > 0) g[N+j][i] = -cost;
      sum += E[i][j];
    }
    if (sum > 0) g[N+M][N+j] = 0;
    if (sum < C[j]) g[N+j][N+M] = 0;
  }

  // init previous vertex for path g[i][j]
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      prev[i][j] = i;
    }
  }

  // find negative cycle by floyd-warshall
  for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        if (g[i][j] > g[i][k] + g[k][j]) {
          g[i][j] = g[i][k] + g[k][j];
          prev[i][j] = prev[k][j];
          if (i == j && g[i][j] < 0) {
            // negative cycle is found
            vector<bool> used(V, false);
            for (int v = i; !used[v]; v = prev[i][v]) {
              used[v] = true;
              int u = prev[i][v];
              if (u == N+M || v == N+M) continue;
              if (v < N) {
                E[v][u-N]--;
              } else {
                E[u][v-N]++;
              }
            }
            cout << "SUBOPTIMAL" << endl;
            printE();
            return;
          }
        }
      }
    }
  }

  cout << "OPTIMAL" << endl;
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d %d %d", &X[i], &Y[i], &B[i]);
  }
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &P[i], &Q[i], &C[i]);
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &E[i][j]);
    }
  }

  solve();
}

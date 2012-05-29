// Limit: 65535K 1000ms
// Used :   788K	 16ms
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e+9;

int solve(int N, int M, vector<vector<int> >& V) {
  vector<vector<int> > dist(N, vector<int>(N, INF));
  for (int i = 0; i < V.size(); i++) {
    for (int j = 0; j < V[i].size(); j++) {
      for (int k = j+1; k < V[i].size(); k++) {
        int u = V[i][j] - 1;
        int v = V[i][k] - 1;
        dist[u][v] = 1;
        dist[v][u] = 1;
      }
    }
  }

  // warshall-floyd
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  int min_sum = INF;
  for (int i = 0; i < N; i++) {
    int sum = 0;
    for (int j = 0; j < N; j++) {
      if (i != j) sum += dist[i][j];
    }
    min_sum = min(min_sum, sum);
  }

  return min_sum * 100 / (N-1);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, M; cin >> N >> M;
  vector<vector<int> > V(M);
  for (int i = 0; i < M; i++) {
    int c; cin >> c;
    V[i].resize(c);
    for (int j = 0; j < c; j++) cin >> V[i][j];
  }

  int ans = solve(N, M, V);
  cout << ans << endl;
}

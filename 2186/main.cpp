#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

const int MAX_V = 10000;
int V;
VI G[MAX_V];
VI rG[MAX_V];
VI vs;
int cmp[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to) {
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  REP(i, G[v].size()) {
    int next_v = G[v][i];
    if (!used[next_v]) dfs(next_v);
  }
  vs.push_back(v);
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  REP(i, rG[v].size()) {
    int next_v = rG[v][i];
    if (!used[next_v]) rdfs(next_v, k);
  }
}

int scc() {
  // 1st DFS
  vs.clear();
  fill(used, used+V, false);
  for (int v = 0; v < V; v++) {
    if (!used[v]) dfs(v);
  }

  // 2nd DFS
  fill(used, used+V, false);
  int k = 0;
  for (int i = vs.size()-1; i >= 0; i--) {
    int v = vs[i];
    if (!used[v]) {
      rdfs(v, k);
      k++;
    }
  }

  return k;
}

int main() {
  int N, M; scanf("%d %d", &N, &M);
  vector<int> A(M), B(M);
  REP(i, M) scanf("%d %d", &A[i], &B[i]);

  // construct directed graph
  V = N;
  REP(i, M) add_edge(A[i]-1, B[i]-1);
  
  // decompose scc
  int n = scc();

  // find sum of leaf component
  int num = 0;
  int idx = 0;
  REP(i, N) {
    if (cmp[i] == n-1) {
      num++;
      idx = i;
    }
  }

  // check if the leaf can be reached from all vertex
  fill(used, used+V, false);
  rdfs(idx, 0);
  REP(i, N) {
    if (!used[i]) {
      num = 0;
      break;
    }
  }

  cout << num << endl;
}


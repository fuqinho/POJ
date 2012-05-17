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
#include <cstring>
#include <climits>
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

struct edge { int to, length; };

const int MAX_N = 10000;

int N, K;
vector<edge> G[MAX_N];
bool centroid[MAX_N];
int subtree_size[MAX_N]; // その頂点を根とする部分木のサイズ

// 部分木のサイズを計算する再帰関数
int compute_subtree_size(int v, int p) {
  int c = 1;
  REP(i, G[v].size()) {
    int w = G[v][i].to;
    if (w == p || centroid[w]) continue;
    c += compute_subtree_size(G[v][i].to, v);
  }
  subtree_size[v] = c;
  return c;
}

// 重心となる頂点を探す再帰関数。tは連結部分全体の大きさ
// v以下で、削除により残る最大の部分木の頂点数が最小となる頂点の、
// (残る最大の部分木の頂点数, 頂点番号)のペアを返す
PII search_centroid(int v, int p, int t) {
  PII res(INT_MAX, -1);
  int s = 1, m = 0;
  REP(i, G[v].size()) {
    int w = G[v][i].to;
    if (w == p || centroid[w]) continue;

    res = min(res, search_centroid(w, v, t));

    m = max(m, subtree_size[w]);
    s += subtree_size[w];
  }
  m = max(m, t - s);
  res = min(res, PII(m, v));
  return res;
}

// 部分木に含まれる全頂点の重心までの距離を列挙する再帰関数
void enumerate_paths(int v, int p, int d, VI& ds) {
  ds.push_back(d);
  REP(i, G[v].size()) {
    int w = G[v][i].to;
    if (w == p || centroid[w]) continue;
    enumerate_paths(w, v, d + G[v][i].length, ds);
  }
}

// 和がK以下となる組の数を求める
int count_pairs(VI& ds) {
  int res = 0;
  sort(ALL(ds));
  int j = ds.size();
  REP(i, ds.size()) {
    while (j > 0 && ds[i] + ds[j-1] > K) --j;
    res += j - (j > i ? 1 : 0); // 自分自身とのペアは除く
  }
  return res / 2;
}

// 頂点vが属する部分木に関して、重心を探し木を分割し問題を解く再帰関数
int solve_problem(int v) {
  int ans = 0;

  // 重心となる頂点sを探す
  compute_subtree_size(v, -1);
  int s = search_centroid(v, -1, subtree_size[v]).second;
  centroid[s] = true;

  // (1): 頂点sにより分割した部分木のなかに関して数える
  REP(i, G[s].size()) {
    if (centroid[G[s][i].to]) continue;
    ans += solve_problem(G[s][i].to);
  }

  // (2), (3): 頂点sを通る頂点の組みに関して数える
  VI ds;
  ds.push_back(0); // 頂点sの分
  REP(i, G[s].size()) {
    if (centroid[G[s][i].to]) continue;

    VI tds;
    enumerate_paths(G[s][i].to, s, G[s][i].length, tds);

    ans -= count_pairs(tds); // 重複して数えてしまう分をあらかじめ引いておく
    ds.insert(ds.end(), tds.begin(), tds.end());
  }
  ans += count_pairs(ds);
  centroid[s] = false;

  return ans;
}

void solve() {
  int ans = solve_problem(0);
  printf("%d\n", ans);
}

void add_edge(int a, int b, int length) {
  G[a].push_back((edge){b, length});
  G[b].push_back((edge){a, length});
}

int main() {
  while (true) {
    scanf("%d %d", &N, &K);
    if (N == 0 && K == 0) break;

    // clear data
    REP(i, N) {
      G[i].clear();
      centroid[i] = false;
      subtree_size[i] = 0;
    }

    REP(i, N-1) {
      int a, b, l; scanf("%d %d %d", &a, &b, &l);
      add_edge(a-1, b-1, l);
    }
    solve();
  }
}


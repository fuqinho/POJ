// Limit: 65536K 1000ms
// Used :   872K  235ms
#include <iostream>
#include <iomanip>
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

struct DisjointSet {
  vector<int> par;
  vector<int> rank;

  DisjointSet(int n) {
    par = vector<int>(n);
    rank = vector<int>(n, 1);
    REP(i, n) par[i] = i;
  }

  int same(int x, int y) {
    return root(x) == root(y);
  }

  void unite(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    if (rank[rx] == rank[ry]) {
      par[rx] = ry;
      rank[ry]++;
    } else {
      if (rank[rx] < rank[ry]) par[rx] = ry;
      else par[ry] = rx;
    }
  }

  int root(int x) {
    if (par[x] == x) return x;
    return par[x] = root(par[x]);
  }
};

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, M; cin >> N >> M;
  vector<pair<int, pair<int, int> > > edges(M);
  REP(i, M) {
    int A, B, L; cin >> A >> B >> L;
    edges[i] = make_pair(L, make_pair(A-1, B-1));
  }

  sort(edges.begin(), edges.end());
  DisjointSet ds(N);
  int maxLength = 0;
  for (int i = 0; i < edges.size(); i++) {
    int a = edges[i].second.first;
    int b = edges[i].second.second;
    if (!ds.same(a, b)) {
      ds.unite(a, b);
      maxLength = max(maxLength, edges[i].first);
    }
  }
  cout << maxLength << endl;
}

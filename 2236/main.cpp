// Limit: 65536K / 10000ms
// Used :   624K /  3344ms
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

class UnionFindTree {
public:
  UnionFindTree(int n) {
    rank = vector<int>(n, 0);
    par = vector<int>(n);
    for (int i = 0; i < n; i++) par[i] = i;
  }
  int find(int x) {
    if (x == par[x]) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rank[rx] < rank[ry]) par[rx] = ry;
    else {
      par[ry] = rx;
      if (rank[rx] == rank[ry]) rank[rx]++;
    }
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
private:
  vector<int> par;
  vector<int> rank;
};

int main() {
  int N, d; scanf("%d %d", &N, &d);
  vector<pair<int, int> > pos(N);
  for (int i = 0; i < N; i++) scanf("%d %d", &pos[i].first, &pos[i].second);

  UnionFindTree tree(N);
  vector<bool> repaired(N, false);

  char buf[2];
  while (scanf("%s", buf) != EOF) {
    if (strcmp(buf, "O") == 0) {
      int c; scanf("%d", &c); c--;
      repaired[c] = true;
      for (int i = 0; i < N; i++) {
        if (i != c && repaired[i]) {
          if ((pos[c].first - pos[i].first) * (pos[c].first - pos[i].first) +
              (pos[c].second - pos[i].second) * (pos[c].second - pos[i].second) <= d * d) {
            tree.unite(c, i);
          }
        }
      }
    }
    if (strcmp(buf, "S") == 0) {
      int a, b; scanf("%d %d", &a, &b);
      printf("%s\n", tree.same(a-1, b-1) ? "SUCCESS" : "FAIL");
    }
  }
}

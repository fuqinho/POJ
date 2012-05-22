// Limit: 10000K / 1000ms
// Used :  2980K /  688ms
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
  int T; scanf("%d", &T);
  for (int t = 0; t < T; t++) {
    int N, M; scanf("%d %d", &N, &M);
    UnionFindTree tree(N * 2);

    for (int i = 0; i < M; i++) {
      char type[2];
      int a, b;
      scanf("%s %d %d", type, &a, &b);
      if (strcmp(type, "D") == 0) {
        tree.unite(a-1, N+(b-1));
        tree.unite(N+(a-1), b-1);
      } else {
        if (tree.same(a-1, b-1)) {
          printf("In the same gang.\n");
        } else if (tree.same(a-1, N+(b-1))) {
          printf("In different gangs.\n");
        } else {
          printf("Not sure yet.\n");
        }
      }
    }
  }
}

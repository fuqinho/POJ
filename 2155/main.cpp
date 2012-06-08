// Used: 8464K	1766MS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

struct BIT {
  vector<int> bit;
  BIT(int n) {
    bit = vector<int>(n+1);
  }
  int sum(int i) {
    int res = 0;
    while (i > 0) {
      res += bit[i];
      i -= (i & -i);
    }
    return res;
  }
  int sum(int i, int j) {
    return sum(j) - sum(i-1);
  }
  void add(int i, int x) {
    while (i < bit.size()) {
      bit[i] += x;
      i += (i & -i);
    }
  }
};

struct BITBIT {
  vector<BIT> bits;
  BITBIT(int n, int m) {
    bits = vector<BIT>(n, BIT(m));
  }
  int sum(int i, int j) {
    int res = 0;
    while (i > 0) {
      res += bits[i].sum(j);
      i -= (i & -i);
    }
    return res;
  }
  void add(int i, int j, int x) {
    while (i < bits.size()) {
      bits[i].add(j, x);
      i += (i & -i);
    }
  }
};

int main() {
  int X; scanf("%d", &X);
  REP(x, X) {
    int N, T; scanf("%d %d", &N, &T);
    
    BITBIT bits(N+1, N+1);
    for (int i = 0; i < T; i++) {
      char type[2]; scanf("%s", type);
      if (type[0] == 'C') {
        // change
        int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        bits.add(x1, y1, 1);
        bits.add(x1, y2+1, 1);
        bits.add(x2+1, y1, 1);
        bits.add(x2+1, y2+1 ,1);
      } else {
        int x, y; scanf("%d %d", &x, &y);
        int sum = bits.sum(x, y);
        printf("%d\n", (sum % 2 == 0 ? 0 : 1));
      }
    }
    printf("\n");
  }
}

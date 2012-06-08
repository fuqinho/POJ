// Used: 16464K	2125MS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)

#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

struct BIT {
  vector<LL> bit;
  BIT(int n) {
    bit = vector<LL>(n+1);
  }
  LL sum(int i) {
    LL res = 0;
    while (i > 0) {
      res += bit[i];
      i -= (i & -i);
    }
    return res;
  }
  LL sum(int i, int j) {
    return sum(j) - sum(i-1);
  }
  void add(int i, LL x) {
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
  LL sum(int i, int j) {
    LL res = 0;
    while (i > 0) {
      res += bits[i].sum(j);
      i -= (i & -i);
    }
    return res;
  }
  void add(int i, int j, LL x) {
    while (i < bits.size()) {
      bits[i].add(j, x);
      i += (i & -i);
    }
  }
};

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  
  int X; scanf("%d", &X);
  REP(x, X) {
    int N, T; scanf("%d %d", &N, &T);
    
    //vector<BIT> bits(N, BIT(N+1));
    BITBIT bits(N+1, N+1);
    for (int i = 0; i < T; i++) {
      char type[2]; scanf("%s", type);
      if (type[0] == 'C') {
        // change
        int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        /*
        for (int i = y1; i <= y2; i++) {
          bits[i-1].add(x1, 1);
          bits[i-1].add(x2+1, 1);
        }
        */
        bits.add(x1, y1, 1);
        bits.add(x1, y2+1, 1);
        bits.add(x2+1, y1, 1);
        bits.add(x2+1, y2+1 ,1);
      } else {
        int x, y; scanf("%d %d", &x, &y);
        //int sum = bits[y-1].sum(1, x);
        int sum = bits.sum(x, y);
        cout << (sum % 2 == 0 ? 0 : 1) << endl;
      }
    }
    cout << endl;
  }
}

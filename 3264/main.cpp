// Used: 3812K	4766MS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
#define REP(i,n) for(int i=0;i<(n);++i)

const int MAX_N = 50000;
const int MAX_Q = 200000;
const int INF = 1000000000;

// data structure for range minimum query
struct SegTree {
  int size;
  vector<int> dat;
  SegTree(int n) {
    size = 1;
    while (size < n) size <<= 1;
    dat = vector<int>(size * 2 - 1, INF);
  }
  void update(int k, int a) {
    k += size-1;
    dat[k] = a;
    while (k > 0) {
      k = (k-1) / 2;
      dat[k] = min(dat[k*2+1], dat[k*2+2]);
    }
  }
  int query(int a, int b) {
    return query(a, b, 0, 0, size);
  }
  int query(int a, int b, int k, int l, int r) {
    if (a >= r || b <= l) return INF;
    if (a <= l && r <= b) return dat[k];
    return min(query(a, b, k*2+1, l, (l+r)/2),
               query(a, b, k*2+2, (l+r)/2, r));
  }
};

void solve(int N, int Q, VI& heights, VI& A, VI& B) {
  SegTree sgMin(N);
  REP(i, N) sgMin.update(i, heights[i]);
  SegTree sgMax(N);
  REP(i, N) sgMax.update(i, -heights[i]);

  REP(i, Q) {
    int minH = sgMin.query(A[i]-1, B[i]);
    int maxH = -sgMax.query(A[i]-1, B[i]);
    cout << maxH - minH << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, Q; cin >> N >> Q;
  VI heights(N);
  REP(i, N) cin >> heights[i];
  VI A(Q), B(Q);
  REP(i, Q) cin >> A[i] >> B[i];

  solve(N, Q, heights, A, B);
}

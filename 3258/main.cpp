// Used: 924K	329MS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
#define REP(i,n) for(int i=0;i<(n);++i)

bool isOK(int L, VI& D, int distance, int needcount) {
  int curPos = 0;
  int count = 0;
  for (int i = 0; i < D.size(); i++) {
    if (i == D.size()-1 && L - D[i] < distance) break;
    if (D[i] >= curPos + distance) {
      curPos = D[i];
      count++;
    }
  }
  return count >= needcount;
}

int solve(int L, int N, int M, VI& D) {
  sort(D.begin(), D.end());

  int lb = 0;
  int ub = L+1;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (isOK(L, D, mid, N-M))  lb = mid;
    else ub = mid;
  }
  return lb;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int L, N, M; cin >> L >> N >> M;
  vector<int> D(N);
  REP(i, N) cin >> D[i];
  
  int ans = solve(L, N, M, D);
  cout << ans << endl;
}

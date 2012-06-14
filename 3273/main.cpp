// Used: 1112K	329MS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
#define REP(i,n) for(int i=0;i<(n);++i)

bool C(VI& money, int budget, int M) {
  int sum = 0;
  int periods = 1;
  REP(i, money.size()) {
    if (money[i] > budget) return false;
    sum += money[i];
    if (sum > budget) {
      periods++;
      sum = money[i];
    }
  }
  return periods <= M;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int N, M; cin >> N >> M;
  vector<int> money(N);
  REP(i, N) cin >> money[i];
  
  int lb = -1;
  int ub = 1000000001;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(money, mid, M)) ub = mid;
    else lb = mid;
  }
  cout << ub << endl;
}

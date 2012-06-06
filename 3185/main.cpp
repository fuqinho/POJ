// Used: 740K	0MS
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
#define REP(i,n) for(int i=0;i<(n);++i)
const int INF = 10000;

int flip(VI v) {
  int count = 0;
  REP(i, 19) {
    if (v[i] == 1) {
      count++;
      for (int j = i; j < min(i+3, 20); j++) {
        v[j] = (v[j] == 0 ? 1 : 0);
      }
    }
  }
  if (v[19] == 1) return INF;
  else return count;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  VI v(20);
  REP(i, 20) cin >> v[i];

  VI v2 = v;
  v2[0] = (v2[0] == 0 ? 1 : 0);
  v2[1] = (v2[1] == 0 ? 1 : 0);
  
  cout << min(flip(v), flip(v2) + 1) << endl;
}

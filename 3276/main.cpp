#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

PII solve(int N, vector<char>& input) {
  //check(input);
  int minCount = 10000;
  int minW = 0;

  vector<bool> f(N, false); // 区間[i, i+K-1]を反転させたならば1

  for (int w = 1; w <= N; w++) {
    //debug(w);
    REP(i, N) f[i] = false;
    int count = 0;
    bool flipped = false;
    for (int i = 0; i + w <= N; i++) {
      if (i >= w) {
        if (f[i-w] == true) flipped = !flipped;
      }
      if ((!flipped && input[i] == 'B') || (flipped && input[i] != 'B')) {
        flipped = !flipped;
        f[i] = true;
        count++;
      }
    }
    bool isSuccess = true;
    for (int i = N - w + 1; i < N; i++) {
      if (i >= w) {
        if (f[i-w] == true) flipped = !flipped;
      }
      if ((!flipped && input[i] == 'B') || (flipped && input[i] != 'B')) {
        isSuccess = false;
        break;
      }
    }
    if (isSuccess) {
      if (count < minCount) {
        minCount = count;
        minW = w;
      }
    }
    //check(f);
  }
  return make_pair(minCount, minW);
}

int main() {
  int N;
  scanf("%d", &N);

  vector<char> input(N);
  REP(i, N) {
    char c;
    cin >> c;
    input[i] = c;
  }

  PII answer = solve(N, input);
  cout << answer.second << " " << answer.first << endl;

}


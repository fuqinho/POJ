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
#include <string>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int num_cows(vector<int>& x, int interval) {
  int cowPos = 0;
  int res = 0;
  REP(i, x.size()){
    if (i == 0 || x[i] >= cowPos + interval) {
      res++;
      cowPos = x[i];
    }
  }
  return res;
}

int solve(int N, int M, vector<int> x) {
  int lb = 0;
  int ub = *max_element(x.begin(), x.end());
  sort(x.begin(), x.end());

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    int numCows = num_cows(x, mid);
    if (numCows >= M) {
      lb = mid;
    } else {
      ub = mid;
    }
  }
  return lb;
}

int main() {
  int N, C;
  scanf("%d %d", &N, &C);
  vector<int> X(N);
  REP(i, N) {
    int x;
    scanf("%d", &x);
    X[i] = x;
  }

  int answer = solve(N, C, X);
  cout << answer << endl;
}



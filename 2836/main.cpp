// Limit: 65536K  1000ms
// Used :   816K   157ms
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

const int INF = 1000000000;

struct Rect {
  int covering, area;
  Rect(int c, int a): covering(c), area(a) {}
};

bool isCovered(int p, int p1, int p2, vector<int>& x, vector<int>& y) {
  return (x[p]-x[p1])*(x[p]-x[p2]) <= 0 &&
         (y[p]-y[p1])*(y[p]-y[p2]) <= 0;
}

int solve(int n, vector<int>& x, vector<int>& y) {
  // list up rectangles
  vector<Rect> rectangles;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {

      // make rectangle by i-th point and j-th point,
      // and check covering points and its area (width and height must not be 0)
      int area = max(1, abs(x[i]-x[j])) * max(1, abs(y[i]-y[j]));
      Rect rect = Rect((1 << i)|(1 << j), area);
      for (int k = 0; k < n; k++) {
        if (isCovered(k, i, j, x, y)) rect.covering |= (1 << k);
      }
      rectangles.push_back(rect);
    }
  }

  // DP for state S: which point are covered
  // dp[S]: minimum area to cover points in S
  vector<int> dp(1 << n, INF);
  dp[0] = 0;
  for (int i = 0; i < rectangles.size(); i++) {
    int covering = rectangles[i].covering;
    for (int s = 0; s < (1 << n); s++) {
      if (dp[s] != INF && (s|covering) != s) {
        dp[s|covering] = min(dp[s|covering], dp[s] + rectangles[i].area);
      }
    }
  }
  return dp[(1 << n) - 1];
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    int ans = solve(n, x, y);
    cout << ans << endl;
  }
}

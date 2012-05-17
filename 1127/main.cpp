#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

static const double EPS = 1e-10;

typedef pair<double, double> Vec2;

double inner_prod(const Vec2& a, const Vec2& b) {
  return a.first * b.first + a.second * b.second;
}

double exter_prod(const Vec2& a, const Vec2& b) {
  return a.first * b.second - a.second * b.first;
}

Vec2 add(const Vec2& a, const Vec2& b) {
  return Vec2(a.first + b.first, a.second + b.second);
}

Vec2 sub(const Vec2& a, const Vec2& b) {
  return Vec2(a.first - b.first, a.second - b.second);
}

Vec2 mul(const Vec2& a, double t) {
  return Vec2(a.first * t, a.second * t);
}

bool isParallel(const Vec2& a, const Vec2& b) {
  return fabs(exter_prod(a, b)) <= EPS;
}

// qが線分(p1, p2)上にあるかどうか
bool on_seg(const Vec2& p1, const Vec2& p2, const Vec2& q) {
  return isParallel(sub(p1, q), sub(p2, q)) && 
    inner_prod(sub(p1, q), sub(p2, q)) <= 0;
}

// 直線(p1-p2)と直線(q1-q2)の交点
Vec2 intersection(const Vec2& p1, const Vec2& p2, const Vec2& q1, const Vec2& q2) {
  double t = exter_prod(sub(q2, q1), sub(q1, p1)) / exter_prod(sub(q2, q1), sub(p2, p1));
  return add(p1, mul(sub(p2, p1), t)); 
}

void solve(int N, vector<pair<Vec2, Vec2> >& s, vector<pair<int, int> >& q)
{
  vector<vector<bool> > connected(N, vector<bool>(N, false));
  for (int i = 0; i < N; i++) connected[i][i] = true;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        bool c = false;
        if (isParallel(sub(s[i].second, s[i].first), sub(s[j].second, s[j].first))) {
          c = on_seg(s[i].first, s[i].second, s[j].first) ||
              on_seg(s[i].first, s[i].second, s[j].second) ||
              on_seg(s[j].first, s[j].second, s[i].first) ||
              on_seg(s[j].first, s[j].second, s[i].second);
        } else {
          Vec2 d = intersection(s[i].first, s[i].second, s[j].first, s[j].second);
          c = on_seg(s[i].first, s[i].second, d) && on_seg(s[j].first, s[j].second, d);
        }
        connected[i][j] = connected[j][i] = c;
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        connected[i][j] = connected[i][j] || (connected[i][k] && connected[k][j]);
      }
    }
  }

  for (int i = 0; i < q.size(); i++) {
    cout << (connected[q[i].first][q[i].second] ? "CONNECTED" : "NOT CONNECTED") << endl;
  }
}

int main() {
  while (true) {
    int N; scanf("%d", &N);
    if (N == 0) break;

    vector<pair<Vec2, Vec2> > s(N);
    for (int i = 0; i < N; i++) {
      int a, b, c, d;
      scanf("%d %d %d %d", &a, &b, &c, &d);
      s[i].first = Vec2(a, b);
      s[i].second = Vec2(c, d);
    }
    vector<pair<int, int> > q;
    while (true) {
      int a, b; scanf("%d %d", &a, &b);
      if (a == 0 && b == 0) break;

      q.push_back(pair<int, int>(a-1, b-1));
    }

    solve(N, s, q);
  }
}

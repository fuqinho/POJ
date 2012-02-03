#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;

#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

const double EPS = 1e-10;
const double PI  = acos(-1.0);

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

PII getNext(VVI& maze, int x, int y, int dx, int dy) {
  bool isFirst = true;
  while (true) {
    x += dx;
    y += dy;
    if (x < 0 || x >= maze[0].size() || y < 0 || y >= maze.size()) return PII(-1, -1);
    if (maze[y][x] == 3) return PII(x, y);
    if (maze[y][x] == 1) {
      if (isFirst) return PII(-1, -1);
      else return PII(x, y);
    }
    isFirst = false;
  }
  return PII(-1, -1);
}

int dfs(VVI& maze, int x, int y, int depth) {
  /*
  dump(x);
  dump(y);
  REP(i,maze.size()) {
    REP(j,maze[i].size()) {
      cerr << maze[i][j];
    }
    cerr << endl;
  }
  */

  if (depth >= 10) return -1;
  if (maze[y][x] == 3) return depth;

  int minStep = -1; 
  REP(i, 4) {
    PII next = getNext(maze, x, y, dx[i], dy[i]);
    int nx = next.first;
    int ny = next.second;
    if (nx != -1 && ny != -1) {
      if (maze[ny][nx] == 1) {
        maze[ny][nx] = 0;
        int step = dfs(maze, nx-dx[i], ny-dy[i], depth+1);
        if (step != -1) {
          if (minStep == -1 || minStep > step) minStep = step;
        }
        maze[ny][nx] = 1;
      }
      if (maze[ny][nx] == 3) {
        if (minStep == -1 || minStep > (depth + 1)) minStep = depth + 1;
      }
    }
  }
  return minStep;
}

int solve(VVI& maze) {
  PII start;
  REP(i, maze.size()) REP(j,maze[i].size()) {
    if (maze[i][j] == 2) start = PII(j, i);
  }
  return dfs(maze, start.first, start.second, 0);
}

int main() {
  int w, h;
  while (true) {
    //cerr << "#########################################" << endl;
    cin >> w >> h;
    if (w == 0 && h == 0) break;
    VVI maze(h, VI(w));
    REP(i, h) REP(j, w) cin >> maze[i][j];

    int answer = solve(maze);
    cout << answer << endl;
  }
}


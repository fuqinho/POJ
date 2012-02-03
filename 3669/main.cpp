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
#include <cstdio>
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

static const int INF = 1000000;
static const int SIZE = 310;

int bfs(VVI& area) {
  if (area[0][0] == 0) return -1;
  VVI dist(SIZE, VI(SIZE, INF));
  queue<PII> q;
  q.push(PII(0, 0));
  dist[0][0] = 0;

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    if (area[x][y] == INF) {
      return dist[x][y];
    }
    REP(i, 4) {
      static const int dx[] = {-1, 1, 0, 0};
      static const int dy[] = {0, 0, -1, 1};
      int nx = x + dx[i];
      int ny = y + dy[i];
      int nt = dist[x][y] + 1;
      if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
        if (area[nx][ny] > nt && dist[nx][ny] > nt) {
          dist[nx][ny] = nt;
          q.push(PII(nx, ny));
        }
      }
    }
  }
  return -1;
}

int solve(VVI& area) {
  return bfs(area);
}

int main() {
  int M;
  scanf("%d", &M);
  VVI area(SIZE, VI(SIZE, INF));
  REP(i, M) {
    int x, y, t;
    scanf("%d %d %d", &x, &y, &t);
    REP(j, 5) {
      static const int dx[] = {0, 0, 0, -1, 1};
      static const int dy[] = {0, -1, 1, 0, 0};
      int xx = x + dx[j];
      int yy = y + dy[j];
      if (xx >= 0 && xx < SIZE && yy >= 0 && yy < SIZE) {
        area[xx][yy] = min(area[xx][yy], t);
      }
    }
  }
  int answer = solve(area);
  cout << answer << endl;
}


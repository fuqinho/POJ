#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;

// 定数
static const int MAX_X = 12;
static const int MAX_Y = 12;
static const int INF = 100000000;
static const int DX[4] = {-1, 0, 0, 1};
static const int DY[4] = { 0,-1, 1, 0};


/////////////////////////////////////
//static const int INF = 100000000;
static const int MAX_V = 10000;
int V;

vector<int> G[MAX_V];
vector<bool> used(MAX_V);
vector<int> match(MAX_V);

void add_edge(int from, int to) {
  //cerr << "edge " << from << " -> " << to << endl;
  G[from].push_back(to);
  G[to].push_back(from);
}

bool find_arg_path(int v) {
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    int u = G[v][i];
    int w = match[u];
    if (w < 0 || (!used[w] && find_arg_path(w))) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

int bipartite_matching() {
  int res = 0;
  fill(match.begin(), match.end(), -1);
  for (int v = 0; v < V; v++) {
    if (match[v] < 0) {
      fill(used.begin(), used.end(), 0);
      if (find_arg_path(v)) res++;
    }
  }
  return res;
}

/////////////////////////////////////


// 時間tで全員が脱出可能か判定する
bool C(int t, vector<PII>& door, vector<PII>& person, int dist[MAX_X][MAX_Y][MAX_X][MAX_Y]) {
  // 0 ~ (d-1): 時刻1に対応するドア
  // d ~ (2d-1): 時刻2に対応するドア
  // (t-1)d ~ (td-1): 時刻tに対応するドア
  // td ~ td+p-1: 人
  
  V = t * door.size() + person.size();

  for (int v=0; v<V; v++) G[v].clear();
  
  for (int i=0; i<door.size(); i++) {
    for (int j=0; j<person.size(); j++) {
      int distance = dist[door[i].first][door[i].second][person[j].first][person[j].second];
      if (distance >= 0) {
        //cerr << "Distance: " << distance << endl;
        for (int k = distance; k <= t; k++) {
          //cerr << "  Edge: " << "(Door: " << i << ", t: " << k << ") -> (P: " << j << ")" << endl;
          add_edge((k-1) * door.size() + i, t * door.size() + j);

        }
      }
    }
  }

  return bipartite_matching() == person.size();
}

// (x, y)から各座標への距離を求める
void bfs(int x, int y, int W, int H, int d[MAX_X][MAX_Y], vector<string>& field) {
  queue<PII> q;
  d[x][y] = 0;
  q.push(PII(x, y));
  while (!q.empty()) {
    PII p = q.front(); q.pop();
    for (int k=0; k<4; k++) {
      PII p2 = PII(p.first + DX[k], p.second + DY[k]);
      if (p2.first >= 0 && p2.first < W &&
          p2.second >= 0 && p2.second < H &&
          field[p2.second][p2.first] == '.' && d[p2.first][p2.second] < 0) {
        d[p2.first][p2.second] = d[p.first][p.second] + 1;
        q.push(p2);
      }
    }
  }
}

int solve(int H, int W, vector<string>& field) {
  vector<PII> door; // ドアの座標
  vector<PII> person; // 人の座標
  int dist[MAX_X][MAX_Y][MAX_X][MAX_Y]; // 最短距離
  memset(dist, -1, sizeof(dist));

  // 各ドアからの最短距離を求める
  // dist[x1][y1][x2][y2]が(x1,y1)から(x2,y2)への距離になる
  for (int x=0; x<W; x++) {
    for (int y=0; y<H; y++) {
      if (field[y][x] == 'D') {
        door.push_back(PII(x, y));
        //cerr << "Door: (" << x << ", " << y << ")" << endl;
        bfs(x, y, W, H, dist[x][y], field);
      }
      else if (field[y][x] == '.') {
        person.push_back(PII(x, y));
        //cerr << "Person: (" << x << ", " << y << ")" << endl;
      }
    }
  }

  int lb = -1, ub = W * H + 1;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid, door, person, dist)) ub = mid;
    else lb = mid;
  }

  if (ub > W * H) {
    return -1;
  } else {
    return ub;
  }
}

int main() {
  int T; cin >> T;
  for (int i=0; i<T; i++) {
    int H, W; cin >> H >> W;
    vector<string> field(H);
    for (int j=0; j<H; j++) {
      cin >> field[j];
    }
    int answer = solve(H, W, field);
    if (answer == -1) {
      cout << "impossible" << endl;
    } else {
      cout << answer << endl;
    }
  }
}


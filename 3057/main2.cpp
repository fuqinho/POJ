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


/////////////////////////////////////


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

  for (int v = 0; v < (H * W) * door.size() + person.size(); v++) {
    G[v].clear();
  }

  // グラフを作成
  for (int i=0; i<door.size(); i++) {
    for (int j=0; j<person.size(); j++) {
      int distance = dist[door[i].first][door[i].second][person[j].first][person[j].second];
      //cerr << "Distance: " << distance << endl;
      if (distance >= 0) {
        for (int k = distance; k <= (W * H); k++) {
          //cerr << "  Edge: " << "(Door: " << i << ", t: " << k << ") -> (P: " << j << ")" << endl;
          add_edge((k-1) * door.size() + i, (W * H) * door.size() + j);
        }
      }
    }
  }

  // 全員が脱出するための最小時間を計算
  if (person.size() == 0) {
    return 0;
  }
  int num = 0;
  fill(match.begin(), match.end(), -1);
  for (int v = 0; v < (W * H) * door.size(); v++) {
    fill(used.begin(), used.end(), false);
    if (find_arg_path(v)) {
      if (++num == person.size()) {
        return v / door.size() + 1;
      }
    }
  }
  return -1;
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


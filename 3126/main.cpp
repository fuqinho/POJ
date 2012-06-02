// Limit: 65536K  1000ms
// Used :   812K    16ms
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int INF = 1e9;
int isPrime[10000];
const int MUL[] = {1000, 100, 10, 1};

int bfs(int start, int goal) {
  vector<int> d(10000, INF);
  queue<PII> que;
  que.push(PII(start, 0));

  int res = INF;
  while (!que.empty()) {
    int x = que.front().first;
    int depth = que.front().second;
    que.pop();
    if (d[x] == INF) {
      d[x] = depth;
      if (x == goal) {
        res = depth;
        break;
      }
      for (int k = 0; k < 4; k++) {
        int digit = x;
        for (int i = 0; i < (3-k); i++) digit /= 10;
        digit %= 10;

        int x2 = x - digit * MUL[k];
        for (int i = 0; i <= 9; i++) {
          if (i != digit && !(k == 0 && i == 0)) {
            int nx = x2 + i * MUL[k];
            if (isPrime[nx] && d[nx] == INF) {
              que.push(PII(nx, depth+1));
            }
          }
        }
      }
    }
  }
  return res;
}

int solve(int a, int b) {
  return bfs(a, b);
}

void init_prime() {
  for (int i = 2; i < 10000; i++) isPrime[i] = true;
  for (int i = 2; i < 10000; i++) {
    if (isPrime[i]) {
      for (int j = i * 2; j < 10000; j += i) isPrime[j] = false;
    }
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  init_prime();

  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int a, b; cin >> a >> b;
    int ans = solve(a, b);
    if (ans == INF) {
      cout << "Impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}

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

struct State {
    VVI maze;
    PII pos;
    int step;
    void print() {
        cerr << "===== " << step << " =====" << endl;
        REP(i, maze.size()) {
            REP(j, maze[i].size()) {
                if (i == pos.first && j == pos.second)
                    cerr << "*";
                else
                    cerr << maze[i][j];
            }
            cerr << endl;
        }
    }
};

State getNextState(State state, int dy, int dx) {
    state.step++;
    int y = state.pos.first;
    int x = state.pos.second;
    bool immediately = true;
    while (true) {
        y += dy;
        x += dx;
        if (y < 0 || y >= state.maze.size() || 
                x < 0 || x >= state.maze[0].size()) {
            state.pos = PII(-1, -1);
            return state;
        }
        if (state.maze[y][x] == 3) {
            state.pos = PII(y, x);
            return state;
        }
        if (state.maze[y][x] == 1) {
            if (immediately) { 
                state.pos = PII(-1, -1);
            } else {
                state.maze[y][x] = 0;
                state.pos = PII(y - dy, x - dx);
            }
            return state;
        }
        immediately = false;
    }
    return state;
}

int solve(VVI& maze) {
    int h = maze.size();
    int w = maze[0].size();
    PII start, goal, current;
    REP(i, h) REP(j,w) {
        if (maze[i][j] == 2) start = PII(i, j);
        if (maze[i][j] == 3) goal = PII(i, j);
    }
    State state;
    state.maze = maze;
    state.pos = start;
    state.step = 0;
    queue<State> q;
    q.push(state);
    while (!q.empty()) {
        State s = q.front(); q.pop();
        if (s.step >= 10) break;
        REP(i, 4) {
            State ns = getNextState(s, dy[i], dx[i]);
            if (ns.pos == goal) return ns.step;
            if (ns.pos != PII(-1, -1)) {
                q.push(ns);
                //ns.print();
            }
        }
    }
    return -1;
}

int main() {
    int w, h;
    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;
        VVI maze(h, VI(w));
        REP(i, h) REP(j, w) cin >> maze[i][j];

        int answer = solve(maze);
        cout << answer << endl;
    }
}


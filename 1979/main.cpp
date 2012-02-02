#include <iostream>
#include <vector>
using namespace std;

int dirx[] = {0, 0, 1, -1};
int diry[] = {1, -1, 0, 0};

int dfs(vector<string>& tiles, int r, int c) {
    int answer = 0;
    for (int i = 0; i < 4; i++) {
        int x = c + dirx[i];
        int y = r + diry[i];
        if (x >= 0 && x < tiles[0].size() && y >= 0 && y < tiles.size()) {
            if (tiles[y][x] == '.') {
                tiles[y][x] = '@';
                answer++;
                answer += dfs(tiles, y, x);
            }
        }
    }
    return answer;
}

int solve(int W, int H, vector<string> tiles) {
    int r, c;
    for (int i = 0; i < tiles.size(); i++)
        for (int j = 0; j < tiles[i].size(); j++)
            if (tiles[i][j] == '@') {
                r = i;
                c = j;
            }
    int res = dfs(tiles, r, c);
    return res;
}

int main() {
    int W, H;
    while (true) {
        cin >> W >> H;
        if (W == 0 && H == 0) break;
        vector<string> tiles;
        for (int i = 0; i < H; i++) {
            vector<int> row;
            string s;
            cin >> s;
            tiles.push_back(s);
        }
        int answer = solve(W, H, tiles);
        cout << answer + 1 << endl;
    }
}

// Limit: 65536K  1000ms
// Used : 12412K   110ms
#include <iostream>
#include <vector>
using namespace std;

const int MAX_H = 1000001;
vector<int> accum(MAX_H + 1, 0);

void init_prime() {
  vector<int> number(MAX_H + 1, 1);
  for (int i = 0; i <= MAX_H; i++) number[i] = i;

  vector<int> fac_num(MAX_H + 1, 0);

  int cnt = 0;
  for (int i=5; i<=MAX_H; i+=4) {
    if (fac_num[i] == 0) {
      fac_num[i] = 1;
      for (int j=i*2; j <= MAX_H; j+=i) if ((j-1)%4==0) {
        while (number[j] % i == 0) {
          number[j] /= i;
          fac_num[j]++;
        }
      }
    }
    if (fac_num[i] == 2) cnt++;
    accum[i] = cnt;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  init_prime();

  while (true) {
    int H; cin >> H;
    if (H == 0) break;
    
    cout << H << " " << accum[H] << endl;
  }
}

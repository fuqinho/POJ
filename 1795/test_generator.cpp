#include <iostream>
using namespace std;

char C[] = {'A', 'C', 'G', 'T'};

void gen() {
  //int n = rand() % 15;
  int n = 15;
  cout << n << endl;
  for (int i = 0; i < n; i++) {
    int len = rand() % 100 + 1;
    for (int j = 0; j < len; j++) cout << C[rand()%4];
    cout << endl;
  }
}

int main() {
  int tests = 20;
  cout << tests << endl;
  for (int i = 0; i < tests; i++) gen();
}

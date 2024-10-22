#include<iostream>
using namespace std;
const int maxm = 6;
const int maxn = 1000;
long long arrack[maxm][maxn];
int t=0;
long long A(int m, int n) {
	if (arrack[m][n] != -1) {
		return arrack[m][n];
	}
	if (m == 0) {
		arrack[m][n] = n + 1;
		t++;
	}
	else if (m > 0 && n == 0) {
		arrack[m][n] = A(m - 1, 1);
		t++;
	}
	else if (m > 0 && n > 0) {
		arrack[m][n] = A(m - 1, A(m, n - 1));
		t++;
	}
	return arrack[m][n];
}
int main() {
	int m, n;
	long long d;
	cout << "¿é¤Jm,n¡G";
	cin >> m >> n;
	for (int i = 0; i < maxm; i++) {
		for (int j = 0; j < maxn; j++) {
			arrack[i][j] = -1;
		}
	}
	d = A(m, n);
	cout << d << endl;
	cout << t << endl;
	return 0;
}
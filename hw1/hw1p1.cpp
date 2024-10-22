#include<iostream>
using namespace std;
int t = 0;
int A(int m, int n) {

	if (m == 0) {
		t++;
		return n + 1;
	}
	else if (m > 0 && n == 0) {
		t++;
		return A(m - 1, 1);
	}
	else if (m > 0 && n > 0) {
		t++;
		return A(m - 1, A(m, n - 1));
	}
}
int main() {
	int m, n;
	int d;
	cin >> m >> n;
	d = A(m, n);
	cout << d << endl;
	cout << t << endl;
	return 0;
}
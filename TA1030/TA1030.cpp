#include<iostream>
using namespace std;
void c(int*& arr, int size, int newsize) {
	int* newarr = new int[newsize];
	copy(arr, arr + size, newarr);
	delete[] arr;
	arr = newarr;
}
int main() {
	int* arr;
	int n,nb;
	cout << "�п�J�}�C�j�p�G";
	cin >> n;
	arr = new int[n];
	cout << "�п�J�}�C�����G"<<endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	char w='Y';
	while (w=='Y') {
		cout << "�п�J�٭n��J�����ƶq�G";
		cin >> nb;
		int a = n;
		n = n + nb;
		c(arr, a, n);
		cout << "�п�J�s�W�����G" << endl;
		for (int i = a; i < n; i++) {
			cin >> arr[i];
		}
		cout << "�O�_�ٶ��n��J�s�������H(Y/N)";
		cin >> w;
		if (w == 'N') break;
	}
	cout << "�̲װ}�C�G" << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
	return 0;
}
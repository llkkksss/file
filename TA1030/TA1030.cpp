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
	cout << "請輸入陣列大小：";
	cin >> n;
	arr = new int[n];
	cout << "請輸入陣列元素："<<endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	char w='Y';
	while (w=='Y') {
		cout << "請輸入還要輸入元素數量：";
		cin >> nb;
		int a = n;
		n = n + nb;
		c(arr, a, n);
		cout << "請輸入新增元素：" << endl;
		for (int i = a; i < n; i++) {
			cin >> arr[i];
		}
		cout << "是否還須要輸入新的元素？(Y/N)";
		cin >> w;
		if (w == 'N') break;
	}
	cout << "最終陣列：" << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
	return 0;
}
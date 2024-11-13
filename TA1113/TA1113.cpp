#include<iostream>
using namespace std;
template <class T>
class C {
private:
	T* array;
	T find;
	T da;
	int size;
public:
	C(int n) : size(n) {
		array = new T[size];
	}
	void print(int i) { cout << array[i]; }
	void getf(T f) {
		find = f;
	}
	int binary() {
		int low = 0;
		int high = size - 1;
		while (low <= high) {
			int mid = low + (high - low) / 2;

			if (array[mid] == find) {
				return mid;
			}
			else if (array[mid] < find) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}

		return -1;
	}
	void inarray(int i) {
		cin >> da;
		array[i] = da;
	}
};
int main() {
	char T;
	int x, y;
	cout << "�п�J(��ƫ��A �}�C�j�p ���մX��)�G";
	cin >> T>>x>>y;
	if (T == 'i') {
		C<int> c(x);
		cout << "�п�J�}�C����(�}�C�j�p"<<x<<")�G";
		for (int i = 0; i < x; i++) {
			c.inarray(i);
		}
		cout << "�п�J�d�߭ȡG";
		for (int i = 0; i < y; i++) {
			int f;
			cin >> f;
			c.getf(f);
			int w = c.binary();
			cout << w << endl;
		}
	}
	else if (T == 's') {
		C<string> c(x);
		cout << "�п�J�}�C����(�}�C�j�p" << x << ")�G";
		for (int i = 0; i < x; i++) {
			c.inarray(i);
		}
		cout << "�п�J�d�߭ȡG";
		for (int i = 0; i < y; i++) {
			string f;
			cin >> f;
			c.getf(f);
			int w = c.binary();
			cout << w << endl;
		}
	}
	return 0;
}
#include <iostream>
using namespace std;
int t = 0;
void printSubset(char subset[], int size) {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << subset[i] << " ";
    }
    cout << "}" << endl;
}
void powerset(char S[], int n, char subset[], int subsetSize, int index) {
    t++;
    if (index == n) {
        printSubset(subset, subsetSize);
        return;
    }
    powerset(S, n, subset, subsetSize, index + 1);
    subset[subsetSize] = S[index];
    powerset(S, n, subset, subsetSize + 1, index + 1);
}

int main() {
    char* S;
    int n;
    cout << "請輸入集合大小：" << endl;
    cin >> n;
    cin.ignore();
    S = new char[n];
    cout << "請輸入集合成員：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    char* subset;
    subset= new char[n];
    cout << "Powerset: " << endl;
    powerset(S, n, subset, 0, 0);
    cout << t << endl ;
    delete[] S;
    delete[] subset;
    return 0;
}

#include "Solution.h"

void main() {
	int num = 4;
	vector<int> a = vector<int>(num);
	for (int i = 0; i < num; i++) {
		cin >> a[i];
	}
	Solution func;
	func.moveZeroes(a);
	for(int i = 0; i < num; i++)
		cout << a[i];
	system("pause");
}
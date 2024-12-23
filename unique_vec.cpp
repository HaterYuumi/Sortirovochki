#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;


void FillArray(vector<int>& vec, size_t size) {
	for (int i = 0; i < size; i++)
		vec.push_back(rand() % 100); // Заполним массив числами от 0 - 100

	return;
}


void PrintVector(const vector<int>& vec) {
	for (auto p : vec)
		cout << p << " ";

	cout << endl;

	return;
}


int main() {
	srand(time(NULL));
	
	vector<int> v1;
	vector<int> v2;
	size_t size = 10;

	FillArray(v1, size);
	// PrintVector(v1);

	// Специально добавлю одинаковые эл-ты в массив
	v1.push_back(2);
	v1.push_back(2);

	for (auto i : v1) {
		bool flag = true;

		for (auto j : v2) {
			if (i == j) flag = false;
		}

		if (flag) {
			v2.push_back(i);
		}
	}
	
	PrintVector(v1);
	PrintVector(v2);

	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& vec) {
	for (auto p : vec)
		cout << p << " ";

	cout << endl;

	return;
}


int main() {
    vector<int> fibonacci;
    vector<int> oddNumbers;
    size_t size = 20;

    // Первые два числа в посл-ности Фимозачи
    fibonacci.push_back(0);
    fibonacci.push_back(1);


    for (int i = 2; i < size; i++) {
        fibonacci.push_back(fibonacci[i - 2] + fibonacci[i - 1]);
    }

    PrintVector(fibonacci);

    for (auto p : fibonacci) {
        if (p % 2 == 0) oddNumbers.push_back(p);
    }

    PrintVector(oddNumbers);

    return 0;
}
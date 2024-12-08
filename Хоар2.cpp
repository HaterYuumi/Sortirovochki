#include <algorithm>
#include <bitset>
#include <iostream>
#include <ctime> 
#include <cmath>

using namespace std;

class Array {
    int* a;
    size_t n;

public:

    Array(int* arr, int len) {
        n = len;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = arr[i];
        }
    }

    Array(Array& other) {
        n = other.n;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = other.a[i];
        }
    }

    ~Array() {
        delete[] a;
        a = NULL;
    }

    Array& operator=(Array& other) {
        if (this != &other) {
            delete[] a;
            n = other.n;
            a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = other.a[i];
            }
        }
        return *this;
    }

    int& operator[](int index) {
        if (index >= 0 && index < n) {
            return a[index];
        }
        throw out_of_range("Index out of range");
    }

    friend istream& operator>>(istream& in, Array& arr) {
        for (int i = 0; i < arr.n; ++i) {
            in >> arr.a[i];
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, Array& arr) {
        out << "[ ";
        for (int i = 0; i < arr.n; ++i) {
            out << arr.a[i] << " ";
        }
        out << "]" << endl;
        return out;
    }

    void Hoar_sort(){
        Hoar2(a, 0, n-1);
    }
    
    void Hoar2(int *arr, int left, int right){
        if (left >= right) return;
        
        int i = left+1;
        int j = right;
        int xm = arr[left];
        
        cout << "Диапазон: [" << left << ", " << right << "] ";
        cout << "Опорный элемент: " << xm << "[" << left << "]"<< endl;
        
        while (i <= j){
            while (arr[i] < xm) i++;
            while (arr[j] > xm) j--;
            
            cout << "i = " << i << ", j = " << j << ", сравниваем: arr[i] = " << arr[i] << " и arr[j] = " << arr[j] << endl;
            
            if (i <= j){
                swap(arr[i], arr[j]);
                cout << "Обмен: arr[" << i << "] = " << arr[i] << " и arr[" << j << "] = " << arr[j] << endl;
                i++;
                j--;
            }
        }
        
        swap(arr[left], arr[j]);
        cout << "Массив после итерации: " << *this << endl;
        
        Hoar2(arr, left, j);
        Hoar2(arr, i, right);
    }
};

int main() {
    int size;
    cout << "Размер массива: ";
    cin >> size;
    int a[size];
    cout << "Элементы массива: ";
    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }
    Array arr1(a, size);
    cout << "Массив до сортировки: ";
    cout << arr1 << endl;
    arr1.Hoar_sort();
    cout << "Массив после сортировки: ";
    cout << arr1 << endl;

    return 0;
}

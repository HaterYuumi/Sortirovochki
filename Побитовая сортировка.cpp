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

    void Bit(int *arr, int left, int right, int k, int size) {
        if (left >= right || k < 0) return;
        int i = left;
        int j = right;
        int tmp = arr[i];
        while (i <= j){
            while (arr[j] & (1 << k)) j--;
            while (~(tmp) & (1 << k)){ 
                i++;
                tmp = arr[i];
            }
            if(i <= j){
                swap(arr[i], arr[j]);
                i++;
                tmp = arr[i];
                j--;
            }
            for (int i = left; i<=right; i++){
                cout << arr[i] << " <-> ";
                print_binary(arr[i], size);
            }
            cout << "----------\n";
        }
        
        Bit(arr, left, j, k-1, size);
        Bit(arr, i, right, k-1, size);
        return;
    }
    
    void Bit_sort(){
        int k = -1;
        for(int i = 0; i < n; i++){
            if (a[i] > k) k = a[i];
        }
        int const size = (int)log2(k)+1;
        
        Bit(a, 0, n-1, size-1, size);
    }    
            
    
    void print_binary(int num, int const size) {
        bitset<32> bin(num);  // Используем 32 бита для отображения числа
        cout << bin.to_string().substr(32 - size) << endl;
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
    arr1.Bit_sort();
    cout << "Массив после сортировки: ";
    cout << arr1 << endl;

    return 0;
}

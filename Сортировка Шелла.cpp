#include <algorithm>
#include <bitset>
#include <iostream>
#include <ctime> 
#include <cmath>

using namespace std;

class Array{
    int *a;
    size_t n;
    
    public:
    
    Array(int *arr, int len){
        n = len;
        a = new int[n];
        for (int i = 0; i < n; i++){
            a[i] = arr[i];
        }
    }
    
    Array(Array &other){
        n = other.n;
        a = new int[n];
        for (int i = 0; i < n; i++){
            a[i] = other.a[i];
        }
    }
    
    ~Array() {
        delete[] a;
        a = NULL;
    }
    
    Array& operator = (Array &other){
        if (this != &other){
            delete []a;
            n = other.n;
            a = new int[n = other.n];
            for (int i = 0; i < n; i++){
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
    
    void Shell_sort(){
        for (int step = n / 2; step > 0; step /= 2) {
            cout << "h = " << step << endl;
            cout << "---------------------" << endl;
            for (int i = step; i < n; i++) {
                int tmp = a[i];
                cout << "buff = " << tmp << endl;
                int j = i;
                for ( ; j >= step; j -= step) {
                    if (a[j - step] > tmp) {
                        cout << a[j - step] << " > " << tmp << endl;
                        cout << a[j] << "[" << j << "] <-> " << a[j - step] << "[" << j - step << "]" << endl;
                        swap(a[j], a[j - step]); 
                    } else {
                        break; 
                    }
                }
                a[j] = tmp;
                cout << "После замены:" << endl;
                cout << *this << endl;
            }
        }
    }


};

int main() {
    int size;
    cout << "Размер массива: ";
    cin >> size;
    int a[size];
    cout << "Эл массива: ";
    for (int i = 0; i < size; i++){
        cin >> a[i];
    }
    Array arr1(a, size);
    cout << arr1 << endl;
    arr1.Shell_sort();
    cout << arr1 << endl;
    
}

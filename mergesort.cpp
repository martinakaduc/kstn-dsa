#include <iostream>
using namespace std;

template typename <T>
class MergeSort {
private:
  T* array;
  int array_size;

  void merge(T arr[], int left, int mid, int right) {
  	int range = right - left + 1;
  	int i = left;
  	int j = mid + 1;
    int k = 0;

  	T* temp = new T[range];

    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k] = arr[i];
        i++;
      } else {
        temp[k] = arr[j];
        j++;
      }
      k++;
    }

    while (i <= mid) {
      temp[k] = arr[i];
      i++;
      k++;
    }

    while (j <= right) {
      temp[k] = arr[j];
      j++;
      k++;
    }

  	for (int k = 0; k < range; k++)
  		arr[left + k] = temp[k];

    delete[] temp;
  }
public:
  MergeSort() : array(nullptr), array_size(0) {}
  MergeSort(T* _array, int _array_size) : array(_array), array_size(_array_size) {}
  ~MergeSort() {
    this->clean();
  }

  void clean() {
    delete[] this->array;
    this->array_size = 0;
  }

  void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
      cout << array[i] << ' ';
      if (size % 10 == 0) cout << '\n';
    }
  	cout << '\n';
  }

  void sort(int l, int r) {
      if (l < r) {
          int m = (r + l) / 2;
          this->sort(this->array, l, m);
          this->sort(this->array, m + 1, r);
          this->merge(this->array, l, m, r);
  				// printArray(arr, array_size);
      }
  }

  void sort(T* arr, int l, int r) {
    this->array = arr;
    this->array_size = sizeof(this->array) / sizeof(T);
    this->sort(l, r);
  }
}

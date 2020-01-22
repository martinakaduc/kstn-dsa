class MergeSort {
  T* array;
  int array_size;
public:
  MergeSort();
  MergeSort(T* _array, int _array_size);
  ~MergeSort();
  void clean();
  void printArray(T* array, int size);
  void sort(int l, int r);
  void sort(T* arr, int l, int r);
}

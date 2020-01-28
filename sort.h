#ifndef _SORT_
#define _SORT_

#include <cstring>
using namespace std;
template <typename T>
class MergeSort
{
    private:
        static void _sort(T* arr, int size, bool (*compare)(T, T, int), int axis);
    public:
        MergeSort() = delete;
        static void  sort(T* arr, int size, bool (*compare)(T, T, int), int axis = -1);
};


template <typename T>
void MergeSort<T>::_sort(T* arr, int size, bool (*compare)(T, T, int), int axis)
{
    if (size > 1)
    {
        int mid = size / 2;
        int sizeL = mid, sizeR = size - mid;
        T* lArr = new T[sizeL];
        T* rArr = new T[sizeR];
        memcpy(lArr, arr, sizeof(T) * sizeL);
        memcpy(rArr, arr + sizeL, sizeof(T) * sizeR);
        _sort(lArr, sizeL, compare, axis);
        _sort(rArr, sizeR, compare, axis);
        int i, j, k;
        i = j = k = 0;
        while (i < sizeL && j < sizeR)
        {
            if (compare(lArr[i], rArr[j], axis))
            {
                arr[k++] = lArr[i++];
            }
            else
            {
                arr[k++] = rArr[j++];
            }
        }
        while (i < sizeL)
            arr[k++] = lArr[i++];
        while (j < sizeR)
            arr[k++] = rArr[j++];
        delete [] lArr;
        delete [] rArr;
        lArr = rArr = nullptr;
        sizeL = sizeR = 0;
    }
}

template <typename T>
void MergeSort<T>::sort(T* arr, int size, bool (*compare)(T, T, int), int axis)
{
    _sort(arr, size, compare, axis);
}

#endif 
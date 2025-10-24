#ifndef TIMSORT_H
#define TIMSORT_H

#include "DinamicArray.h"

template<typename T>
class Timsort{
private:
    const int RUN = 32;
    void insertionSort(DynamicArray<T>& arr, int left, int right, bool ascending = true)
    {
        for (int i = left + 1; i <= right; i++) {
            int temp = arr[i];
            int j = i - 1;
            if (ascending) {
                while (j >= left && arr[j] > temp) {
                    arr[j + 1] = arr[j];
                    j--;
                }
            } else {
                while (j >= left && arr[j] < temp) {
                    arr[j + 1] = arr[j];
                    j--;
                }
            }
            arr[j + 1] = temp;
        }
    }

    void merge(DynamicArray<T>& arr, int l, int m, int r, bool ascending = true)
    {

        int len1 = m - l + 1, len2 = r - m;
        T* left = new T[len1];
        T* right = new T[len2];
        for (int i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (int i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        int i = 0;
        int j = 0;
        int k = l;

        while (i < len1 && j < len2) {
            if (ascending) {
                if (left[i] <= right[j]) {
                    arr[k] = left[i];
                    i++;
                }
                else {
                    arr[k] = right[j];
                    j++;
                }
            } else {
                if (left[i] >= right[j]) {
                    arr[k] = left[i];
                    i++;
                }
                else {
                    arr[k] = right[j];
                    j++;
                }
            }
            k++;
        }

        while (i < len1) {
            arr[k] = left[i];
            k++;
            i++;
        }

        while (j < len2) {
            arr[k] = right[j];
            k++;
            j++;
        }
        delete[] left;
        delete[] right;
    }
public:
void sort(DynamicArray<T>& arr, int n, bool ascending = true)
{

    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, std::min((i + RUN - 1), (n - 1)), ascending);
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right, ascending);
        }
    }
}
};

#endif
#ifndef TIMSORT_H
#define TIMSORT_H

#include "DinamicArray.h"

template<typename T>
class Timsort{
private:
    const int MIN_GALLOP = 7;  
    int minGallop = MIN_GALLOP;
    
    int computeMinrun(int n) {
        int r = 0;  
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        return n + r;
    }

    void reverse(DynamicArray<T>& arr, int left, int right) {
        while (left < right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    int findAscendingRun(DynamicArray<T>& arr, int start, int end, bool ascending) {
        if (start >= end) return 1;
        
        int runLength = 1;
        if (ascending) {
            while (start + runLength < end && start + runLength - 1 < arr.get_size() && 
                   start + runLength < arr.get_size() && 
                   arr[start + runLength - 1] <= arr[start + runLength]) {
                runLength++;
            }
        } else {
            while (start + runLength < end && start + runLength - 1 < arr.get_size() && 
                   start + runLength < arr.get_size() && 
                   arr[start + runLength - 1] >= arr[start + runLength]) {
                runLength++;
            }
        }
        return runLength;
    }

    int findDescendingRun(DynamicArray<T>& arr, int start, int end, bool ascending) {
        if (start >= end) return 1;
        
        int runLength = 1;
        if (ascending) {
            while (start + runLength < end && start + runLength - 1 < arr.get_size() && 
                   start + runLength < arr.get_size() && 
                   arr[start + runLength - 1] > arr[start + runLength]) {
                runLength++;
            }
        } else {
            while (start + runLength < end && start + runLength - 1 < arr.get_size() && 
                   start + runLength < arr.get_size() && 
                   arr[start + runLength - 1] < arr[start + runLength]) {
                runLength++;
            }
        }
        return runLength;
    } 

    int gallopRight(const T& key, DynamicArray<T>& array, int base, int len, int hint, bool ascending) {
        if (len <= 0 || hint < 0 || hint >= len) return 0;
        
        int lastOfs = 0;
        int ofs = 1;
        
        if (ascending) {
            if (key > array[base + hint]) {
                int maxOfs = len - hint;
                while (ofs < maxOfs && key > array[base + hint + ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                lastOfs += hint;
                ofs += hint;
            } else {
                int maxOfs = hint + 1;
                while (ofs < maxOfs && key <= array[base + hint - ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                int tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            }
        } else {
            if (key < array[base + hint]) {
                int maxOfs = len - hint;
                while (ofs < maxOfs && key < array[base + hint + ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                lastOfs += hint;
                ofs += hint;
            } else {
                int maxOfs = hint + 1;
                while (ofs < maxOfs && key >= array[base + hint - ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                int tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            }
        }
        
        lastOfs++;
        while (lastOfs < ofs) {
            int m = lastOfs + ((ofs - lastOfs) >> 1);
            if (ascending) {
                if (key > array[base + m]) {
                    lastOfs = m + 1;
                } else {
                    ofs = m;
                }
            } else {
                if (key < array[base + m]) {
                    lastOfs = m + 1;
                } else {
                    ofs = m;
                }
            }
        }
        return ofs;
    }
    
    int gallopLeft(const T& key, DynamicArray<T>& array, int base, int len, int hint, bool ascending) {
        if (len <= 0 || hint < 0 || hint >= len) return 0;
        
        int lastOfs = 0;
        int ofs = 1;
        
        if (ascending) {
            if (key < array[base + hint]) {
                int maxOfs = hint + 1;
                while (ofs < maxOfs && key < array[base + hint - ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                int tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            } else {
                int maxOfs = len - hint;
                while (ofs < maxOfs && key >= array[base + hint + ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                lastOfs += hint;
                ofs += hint;
            }
        } else {
            if (key > array[base + hint]) {
                int maxOfs = hint + 1;
                while (ofs < maxOfs && key > array[base + hint - ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                int tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            } else {
                int maxOfs = len - hint;
                while (ofs < maxOfs && key <= array[base + hint + ofs]) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;
                    if (ofs <= 0) ofs = maxOfs;
                }
                if (ofs > maxOfs) ofs = maxOfs;
                lastOfs += hint;
                ofs += hint;
            }
        }
        lastOfs++;
        while (lastOfs < ofs) {
            int m = lastOfs + ((ofs - lastOfs) >> 1);
            if (ascending) {
                if (key < array[base + m]) {
                    ofs = m;
                } else {
                    lastOfs = m + 1;
                }
            } else {
                if (key > array[base + m]) {
                    ofs = m;
                } else {
                    lastOfs = m + 1;
                }
            }
        }
        return ofs;
    }
    
    void insertionSort(DynamicArray<T>& arr, int left, int right, bool ascending = true)
    {
        for (int i = left + 1; i <= right; i++) {
            T temp = arr[i];
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
        
        int leftWins = 0;
        int rightWins = 0;
        bool galloping = false;

        while (i < len1 && j < len2) {
            if (!galloping) {
                if (ascending) {
                    if (left[i] <= right[j]) {
                        arr[k] = left[i];
                        i++;
                        k++;
                        leftWins++;
                        rightWins = 0;
                    }
                    else {
                        arr[k] = right[j];
                        j++;
                        k++;
                        rightWins++;
                        leftWins = 0;
                    }
                } else {
                    if (left[i] >= right[j]) {
                        arr[k] = left[i];
                        i++;
                        k++;
                        leftWins++;
                        rightWins = 0;
                    }
                    else {
                        arr[k] = right[j];
                        j++;
                        k++;
                        rightWins++;
                        leftWins = 0;
                    }
                }
                
                if (leftWins >= minGallop || rightWins >= minGallop) {
                    galloping = true;
                }
            } else {
                if (leftWins >= minGallop) {
                    // Создаем временный массив для gallopRight
                    DynamicArray<T> rightArray;
                    rightArray.clear();
                    for (int x = 0; x < len2; x++) {
                        rightArray.push_back(right[x]);
                    }
                    int skip = gallopRight(left[i], rightArray, 0, len2, j, ascending);
                    // Ограничиваем skip, чтобы не выйти за границы
                    skip = std::min(skip, len2 - j);
                    for (int x = 0; x < skip; x++) {
                        arr[k] = right[j + x];
                        k++;
                    }
                    j += skip;
                    leftWins = 0;
                    rightWins = 0;
                } else if (rightWins >= minGallop) {
                    // Создаем временный массив для gallopLeft
                    DynamicArray<T> leftArray;
                    leftArray.clear();
                    for (int x = 0; x < len1; x++) {
                        leftArray.push_back(left[x]);
                    }
                    int skip = gallopLeft(right[j], leftArray, 0, len1, i, ascending);
                    // Ограничиваем skip, чтобы не выйти за границы
                    skip = std::min(skip, len1 - i);
                    for (int x = 0; x < skip; x++) {
                        arr[k] = left[i + x];
                        k++;
                    }
                    i += skip;
                    leftWins = 0;
                    rightWins = 0;
                } else {
                    galloping = false;
                    minGallop++;
                    continue;
                }
            }
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
        
        if (minGallop < 1) {
            minGallop = 1;
        } else if (minGallop > MIN_GALLOP) {
            minGallop = MIN_GALLOP;
        }
        
        delete[] left;
        delete[] right;
    }
public:
void sort(DynamicArray<T>& arr, int n, bool ascending = true)
{
    if (n < 2) return;
    
    int minrun = computeMinrun(n);
    int i = 0;
    while (i < n) {
        int ascendingRun = findAscendingRun(arr, i, n, ascending);
        if (ascendingRun < minrun && i + ascendingRun < n) {
            int descendingRun = findDescendingRun(arr, i + ascendingRun, n, ascending);
            int totalRun = ascendingRun + descendingRun;

            if (totalRun < minrun) {
                totalRun = std::min(minrun, n - i);
            }

            if (descendingRun > 0) {
                reverse(arr, i + ascendingRun, i + totalRun - 1);
            }

            if (totalRun > ascendingRun) {
                insertionSort(arr, i, i + totalRun - 1, ascending);
            }
            
            i += totalRun;
        } else {
            if (ascendingRun < minrun) {
                ascendingRun = std::min(minrun, n - i);
                insertionSort(arr, i, i + ascendingRun - 1, ascending);
            }
            i += ascendingRun;
        }
    }
    for (int size = minrun; size < n; size = 2 * size) {
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
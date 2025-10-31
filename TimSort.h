#ifndef TIMSORT_H
#define TIMSORT_H

#include "DinamicArray.h"
#include "Stack.h"
#include "stdafx.h"

template<typename T>
class Timsort {
private:
    const int MIN_GALLOP = 7;  
    int minGallop = MIN_GALLOP;
    
    struct Run {
        int start;
        int length;
        Run(int s, int len) : start(s), length(len) {}
    };
    
    Stack<Run> runs;
    
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

    void insertionSort(DynamicArray<T>& arr, int left, int right, bool ascending = true) {
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

    int gallopRight(const T& key, DynamicArray<T>& array, int base, int len, int hint, bool ascending) {
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

    void merge(DynamicArray<T>& arr, int l, int m, int r, bool ascending = true) {
        int len1 = m - l + 1, len2 = r - m;
        
        
        T* left = new T[len1];
        T* right = new T[len2];
        
        for (int i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (int i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        int i = 0, j = 0, k = l;
        int leftWins = 0, rightWins = 0;
        bool galloping = false;

        while (i < len1 && j < len2) {
            if (!galloping) {
                bool condition = ascending ? (left[i] <= right[j]) : (left[i] >= right[j]);
                
                if (condition) {
                    arr[k++] = left[i++];
                    leftWins++;
                    rightWins = 0;
                } else {
                    arr[k++] = right[j++];
                    rightWins++;
                    leftWins = 0;
                }
                
                if (leftWins >= minGallop || rightWins >= minGallop) {
                    galloping = true;
                    minGallop++;
                }
            } else {
                if (leftWins >= minGallop) {
                    
                    DynamicArray<T> tempRight;
                    for (int x = 0; x < len2 - j; x++) {
                        tempRight.push_back(right[j + x]);
                    }
                    
                    int skip = gallopRight(left[i], tempRight, 0, tempRight.get_size(), 0, ascending);
                    skip = std::min(skip, len2 - j);
                    
                    for (int x = 0; x < skip; x++) {
                        arr[k++] = right[j + x];
                    }
                    j += skip;
                    leftWins = 0;
                    galloping = false;
                } else if (rightWins >= minGallop) {
                    
                    DynamicArray<T> tempLeft;
                    for (int x = 0; x < len1 - i; x++) {
                        tempLeft.push_back(left[i + x]);
                    }
                    
                    int skip = gallopLeft(right[j], tempLeft, 0, tempLeft.get_size(), 0, ascending);
                    skip = std::min(skip, len1 - i);
                    
                    for (int x = 0; x < skip; x++) {
                        arr[k++] = left[i + x];
                    }
                    i += skip;
                    rightWins = 0;
                    galloping = false;
                } else {
                    galloping = false;
                }
            }
        }

        
        while (i < len1) arr[k++] = left[i++];
        while (j < len2) arr[k++] = right[j++];

        delete[] left;
        delete[] right;
        
    
        if (minGallop > MIN_GALLOP) {
            minGallop = MIN_GALLOP;
        }
    }

    void mergeCollapse(DynamicArray<T>& arr, bool ascending) {
        while (runs.size() > 1) {
            Run Z = runs.top();
            runs.pop();
            Run Y = runs.top();
            runs.pop();
            
            bool hasX = !runs.empty();
            Run X = hasX ? runs.top() : Run(0, 0);
            
      
            if (hasX && X.length <= Y.length + Z.length) {
                
                if (X.length < Z.length) {
                    
                    runs.pop();
                    merge(arr, X.start, X.start + X.length - 1, X.start + X.length + Y.length - 1, ascending);
                    runs.push(Run(X.start, X.length + Y.length));
                    runs.push(Z);
                } else {
                   
                    merge(arr, Y.start, Y.start + Y.length - 1, Y.start + Y.length + Z.length - 1, ascending);
                    runs.push(Run(Y.start, Y.length + Z.length));
                }
            } else if (Y.length <= Z.length) {
               
                merge(arr, Y.start, Y.start + Y.length - 1, Y.start + Y.length + Z.length - 1, ascending);
                runs.push(Run(Y.start, Y.length + Z.length));
            } else {
                
                runs.push(Y);
                runs.push(Z);
                break;
            }
        }
    }

    void forceMergeCollapse(DynamicArray<T>& arr, bool ascending) {
        while (runs.size() > 1) {
            Run Z = runs.top();
            runs.pop();
            Run Y = runs.top();
            runs.pop();
            
            bool hasX = !runs.empty();
            
           
            if (hasX) {
                Run X = runs.top();
                if (X.length < Z.length) {
                 
                    runs.pop(); 
                    merge(arr, X.start, X.start + X.length - 1, X.start + X.length + Y.length - 1, ascending);
                    runs.push(Run(X.start, X.length + Y.length));
                    runs.push(Z);
                } else {
                   
                    merge(arr, Y.start, Y.start + Y.length - 1, Y.start + Y.length + Z.length - 1, ascending);
                    runs.push(Run(Y.start, Y.length + Z.length));
                }
            } else {
                
                merge(arr, Y.start, Y.start + Y.length - 1, Y.start + Y.length + Z.length - 1, ascending);
                runs.push(Run(Y.start, Y.length + Z.length));
            }
        }
    }

    int findNextRun(DynamicArray<T>& arr, int start, int end, bool ascending) {
        if (start >= end - 1) return end - start;
        
        
        int runLength = 2;
        
        
        bool isIncreasing = (ascending && arr[start] <= arr[start + 1]) || 
                           (!ascending && arr[start] >= arr[start + 1]);
        
        if (isIncreasing) {
            
            for (int i = start + 2; i < end; i++) {
                if ((ascending && arr[i-1] > arr[i]) || (!ascending && arr[i-1] < arr[i])) {
                    break;
                }
                runLength++;
            }
        } else {
            
            for (int i = start + 2; i < end; i++) {
                if ((ascending && arr[i-1] < arr[i]) || (!ascending && arr[i-1] > arr[i])) {
                    break;
                }
                runLength++;
            }
         
            reverse(arr, start, start + runLength - 1);
        }
        
        return runLength;
    }

public:
    void sort(DynamicArray<T>& arr, int n, bool ascending = true) {
        if (n < 2) return;
        
        while (!runs.empty()) runs.pop();
        
        minGallop = MIN_GALLOP;
        int minrun = computeMinrun(n);
        int current = 0;
        
        while (current < n) {
            int remaining = n - current;
            if (remaining < 2) {
                runs.push(Run(current, 1));
                current++;
                continue;
            }
            
            int runLength = findNextRun(arr, current, n, ascending);
            
            if (runLength < minrun) {
                int targetLength = std::min(minrun, n - current);
                insertionSort(arr, current, current + targetLength - 1, ascending);
                runLength = targetLength;
            }
            
            runs.push(Run(current, runLength));
            
            mergeCollapse(arr, ascending);
            
            current += runLength;
        }
        
        forceMergeCollapse(arr, ascending);
        
        if (runs.size() != 1) {
            while (runs.size() > 1) {
                Run Z = runs.top();
                runs.pop();
                Run Y = runs.top();
                runs.pop();
                
                merge(arr, Y.start, Y.start + Y.length - 1, Y.start + Y.length + Z.length - 1, ascending);
                runs.push(Run(Y.start, Y.length + Z.length));
            }
        }
    }
};

#endif
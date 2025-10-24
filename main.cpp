#include "TimSort.h"
#include "DinamicArray.h"
#include "stdafx.h"
using namespace std;

int main() {
    
    int dataType = 0;
    while(dataType != 5){
        cout << "\n=== Data type ===" << endl;
        cout << "1. int" << endl;
        cout << "2. char" << endl;
        cout << "3. float" << endl;
        cout << "4. double" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose option (1-5): ";

        
        while (!(cin >> dataType) || dataType < 1 || dataType > 5) {
            cout << "Error! Input number from 1 to 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (dataType == 5){
            cout << "Exit..." << endl;
            return 0;
        }
        
        int choice;
        bool arrayCreated = false;
        bool ascending = true; // true for ascending, false for descending
        
        DynamicArray<int> intArray;
        DynamicArray<char> charArray;
        DynamicArray<float> floatArray;
        DynamicArray<double> doubleArray;
        
        Timsort<int> intSorter;
        Timsort<char> charSorter;
        Timsort<float> floatSorter;
        Timsort<double> doubleSorter;
        
        do {
            cout << "\n=== TimSort ===" << endl;
            cout << "1. Input array" << endl;
            cout << "2. Sort array" << endl;
            cout << "3. Ouput array" << endl;
            cout << "4. Change sort direction" << endl;
            cout << "5. Back" << endl;
            cout << "Choose option (1-5): ";
            
            while (!(cin >> choice) || choice < 1 || choice > 5) {
                cout << "Error! Input number from 1 to 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (choice) {
                case 1: 
                    if (arrayCreated) {
                        cout << "\nArray is created! New array creation..." << endl;
                    }
                    
                    switch (dataType) {
                        case 1: 
                            intArray.clear();
                            
                            int size;
                            cout << "\nInput array size: ";
                            while (!(cin >> size) || size <= 0) {
                                cout << "Error! Input a positive number: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            cout << "Input " << size << " integers:" << endl;
                            for (int i = 0; i < size; i++) {
                                int value;
                                cout << "Elem " << (i + 1) << ": ";
                                while (!(cin >> value)) {
                                    cout << "Error! Input integer: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                intArray.push_back(value);
                            }
                            break;
                            
                        case 2: 
                            charArray.clear();
                            
                            cout << "\nInpur array size: ";
                            while (!(cin >> size) || size <= 0) {
                                cout << "Error! Input a positive number: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            cout << "Input " << size << " chars:" << endl;
                            for (int i = 0; i < size; i++) {
                                char value;
                                cout << "Elem " << (i + 1) << ": ";
                                cin >> value;
                                charArray.push_back(value);
                            }
                            break;
                            
                        case 3: 
                            floatArray.clear();
                            
                            cout << "\nInput array size: ";
                            while (!(cin >> size) || size <= 0) {
                                cout << "Error! Input a positive number:  ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            cout << "Input " << size << " float numbers:" << endl;
                            for (int i = 0; i < size; i++) {
                                float value;
                                cout << "Elem " << (i + 1) << ": ";
                                while (!(cin >> value)) {
                                    cout << "Error! Input float number: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                floatArray.push_back(value);
                            }
                            break;
                            
                        case 4: 
                            doubleArray.clear();
                            
                            cout << "\nInput array size: ";
                            while (!(cin >> size) || size <= 0) {
                                cout << "Error! Input a positive number:  ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            cout << "Input " << size << " double numbers:" << endl;
                            for (int i = 0; i < size; i++) {
                                double value;
                                cout << "Elem " << (i + 1) << ": ";
                                while (!(cin >> value)) {
                                    cout << "Error! Input double number: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                doubleArray.push_back(value);
                            }
                            break;
                    }
                    arrayCreated = true;
                    cout << "\nArray created!" << endl;
                    break;
                    
                case 2: 
                    if (!arrayCreated) {
                        cout << "\nError! First create array." << endl;
                        break;
                    }
                    
                    switch (dataType) {
                        case 1: 
                            if (!intArray.empty()) {
                                auto start_time = std::chrono::steady_clock::now();
                                intSorter.sort(intArray, intArray.get_size(), ascending);
                                auto end_time = std::chrono::steady_clock::now();
                                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
                                cout << "\nArray sorted! Sort time: " << elapsed_ns.count() << " ns" << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 2: 
                            if (!charArray.empty()) {
                                auto start_time = std::chrono::steady_clock::now();
                                charSorter.sort(charArray, charArray.get_size(), ascending);
                                auto end_time = std::chrono::steady_clock::now();
                                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
                                cout << "\nArray sorted! Sort time: " << elapsed_ns.count() << " ns" << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 3: 
                            if (!floatArray.empty()) {
                                auto start_time = std::chrono::steady_clock::now();
                                floatSorter.sort(floatArray, floatArray.get_size(), ascending);
                                auto end_time = std::chrono::steady_clock::now();
                                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
                                cout << "\nArray sorted! Sort time: " << elapsed_ns.count() << " ns" << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 4: 
                            if (!doubleArray.empty()) {
                                auto start_time = std::chrono::steady_clock::now();
                                doubleSorter.sort(doubleArray, doubleArray.get_size(), ascending);
                                auto end_time = std::chrono::steady_clock::now();
                                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
                                cout << "\nArray sorted! Sort time: " << elapsed_ns.count() << " ns" << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                    }
                    break;
                    
                case 3: 
                    if (!arrayCreated) {
                        cout << "\nError! First create array." << endl;
                        break;
                    }
                    
                    switch (dataType) {
                        case 1: 
                            if (!intArray.empty()) {
                                cout << "\n=== Array (int) ===" << endl;
                                cout << "Size: " << intArray.get_size() << endl;
                                cout << "Elems: ";
                                for (size_t i = 0; i < intArray.get_size(); i++) {
                                    cout << intArray[i] << " ";
                                }
                                cout << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 2: 
                            if (!charArray.empty()) {
                                cout << "\n=== Array (char) ===" << endl;
                                cout << "Size: " << charArray.get_size() << endl;
                                cout << "Elems: ";
                                for (size_t i = 0; i < charArray.get_size(); i++) {
                                    cout << charArray[i] << " ";
                                }
                                cout << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 3: 
                            if (!floatArray.empty()) {
                                cout << "\n=== Array (float) ===" << endl;
                                cout << "Size: " << floatArray.get_size() << endl;
                                cout << "Elems: ";
                                for (size_t i = 0; i < floatArray.get_size(); i++) {
                                    cout << floatArray[i] << " ";
                                }
                                cout << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                        case 4: 
                            if (!doubleArray.empty()) {
                                cout << "\n=== Array (double) ===" << endl;
                                cout << "Size: " << doubleArray.get_size() << endl;
                                cout << "Elems: ";
                                for (size_t i = 0; i < doubleArray.get_size(); i++) {
                                    cout << doubleArray[i] << " ";
                                }
                                cout << endl;
                            } else {
                                cout << "\nArray empty!" << endl;
                            }
                            break;
                    }
                    break;
                    
                case 4:
                    cout << "\n=== Sort Direction ===" << endl;
                    cout << "Current direction: " << (ascending ? "Ascending" : "Descending") << endl;
                    cout << "1. Ascending (A to Z, 1 to 9)" << endl;
                    cout << "2. Descending (Z to A, 9 to 1)" << endl;
                    cout << "Choose direction (1-2): ";
                    
                    int direction;
                    while (!(cin >> direction) || direction < 1 || direction > 2) {
                        cout << "Error! Input number from 1 to 2: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    ascending = (direction == 1);
                    cout << "\nSort direction changed to: " << (ascending ? "Ascending" : "Descending") << endl;
                    break;
                    
                case 5:
                    break;
                    
                default:
                    cout << "\nWrong input!" << endl;
                    break;
            }
            
        } while (choice != 5);
    }
    
}


#include " TimSort.h\
#include \DinamicArray.h\
#include \stdafx.h\
using namespace std;
int main(){ DynamicArray<int> a; Timsort<int> s; for(int i=0;i<400;i++) a.push_back(400-i); s.sort(a, (int)a.get_size(), true); for(size_t i=1;i<a.get_size();++i){ if(a[i-1]>a[i]){ cout<<\bad\; return 1;} } cout<<\ok\; return 0; }

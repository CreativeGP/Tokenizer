#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>

using namespace std;

template <typename T>
void showv(vector<T> &v) {
    cout << "{";
    for (int i = 0, len = v.size(); i < len; i++) 
        cout << v[i] << ",";
    cout << "}" << endl;
}

#endif

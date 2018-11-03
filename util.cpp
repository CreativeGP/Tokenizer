/* ========================================================================
   $File: util.cpp $
   $Date: Nov 11 2018 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP. All Rights Reserved. $
   ======================================================================== */

#include "util.h"


template <typename T>
void showv(vector<T> &v) {
    cout << "{";
    for (int i = 0, len = v.size(); i < len; i++) 
        cout << v[i] << ",";
    cout << "}" << endl;
}
template void showv<string>(vector<string>&);

string ctos(char c) {
    char tmp[] = {c, '\0'};
    return string(tmp);
}


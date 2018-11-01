#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <string>
#include <vector>

#define MAX_FILE_SIZE 100000

#define PARSE_MODE_DQUOT 1
#define PARSE_MODE_QUOT 2

using namespace std;

vector<string> tokens;


template <typename T>
void showv(vector<T> &v) {
    cout << "{";
    for (T e : v) 
        cout << e << ",";
    cout << "}" << endl;
}

void add_token(string a) {
    if (a != "") tokens.push_back(a);
}

int main(int args, char **argv) {
    ifstream ifs("main.cpp");
    
    if (!ifs) return -1;

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char *buffer = new char[length];
    ifs.read(buffer, length);

    // parse
    string specials = "!\"#$%&'()-^\\@[;:],./=~|`{+*}<>?";
    string ignores = "";
    string ignoresplit = " \t\n";
    string little = "";
    int mode = 0;
    for (int i = 0; i < length; ++i) {
        if (ignores.find(buffer[i]) != string::npos) continue;
        if (ignoresplit.find(buffer[i]) != string::npos) {
            add_token(little);
            little = "";
            continue;
        }

        if (mode == PARSE_MODE_QUOT) {
            if ((buffer[i-2] == '\\' || buffer[i-1] != '\\') && buffer[i] == '\'') {
                mode = 0;
                add_token(little);
                tokens.push_back("'");
                little = "";
            } else little += buffer[i];
        } else if (mode == PARSE_MODE_DQUOT) {
            if ((buffer[i-2] == '\\' || buffer[i-1] != '\\') && buffer[i] == '"') {
                mode = 0;
                add_token(little);
                tokens.push_back("\"");
                little = "";
            } else little += buffer[i];
        } else {
            if (buffer[i] == '"')
                mode = PARSE_MODE_DQUOT;
            else if (buffer[i] == '\'')
                mode = PARSE_MODE_QUOT;
            
            if (specials.find(buffer[i]) != string::npos) {
                add_token(little);
                little = "";

                char tmp[] = {buffer[i], '\0'};
                tokens.push_back(tmp);
            } else little += buffer[i];
        }
    }

    showv(tokens);

    delete[] buffer;
}

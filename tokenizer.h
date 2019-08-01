#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#define MAX_FILE_SIZE 100000
typedef unsigned int uint;

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Token {
    string val;
    uint  line = 1
        , col  = 0;
};

class Tokenizer {
    public:
    vector<Token> tokens;
    vector<string> tokenvals; // TODO: Should I use string& instead?
    map<string, string> settings;    
    
    Tokenizer();
    ~Tokenizer();
    int tokenize(string code);
    int tokenize_file(string filename);
    int set(string key, string value);
    int preset(string name);

    private:
    int add_token(string value, uint line, uint col);

    const int escape_mode_padding = 100;
};

#endif

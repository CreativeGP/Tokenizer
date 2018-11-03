#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#define MAX_FILE_SIZE 100000
#define PARSE_MODE_DQUOT 1
#define PARSE_MODE_QUOT 2

#include <string>
#include <vector>
#include <map>

using namespace std;

class Tokenizer {
    public:
    vector<string> tokens;
    map<string, string> settings;    
    
    Tokenizer();
    ~Tokenizer();
    int tokenize(string code);
    int tokenize_file(string filename);
    int set(string key, string value);
    int preset(string name);

    private:
    int add_token(string value);
};

#endif

#include <iostream>
#include "tokenizer.h"
#include "util.h"

#define MAX_FILE_SIZE 100000
#define PARSE_MODE_DQUOT 1
#define PARSE_MODE_QUOT 2

int main(int args, char **argv) {
    Tokenizer tkn;
    tkn.preset("cpp");
    tkn.tokenize_file("main.cpp");
    showv(tkn.tokens);
    return 0;
}

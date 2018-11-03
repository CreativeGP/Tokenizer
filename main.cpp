#include "util.h"
#include "tokenizer.h"
#include <iostream>

int main(int args, char **argv) {
    Tokenizer tkn;
    tkn.preset("cpp");
    tkn.tokenize_file("main.cpp");
    showv(tkn.tokens);
    return 0;
}

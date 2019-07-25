#include "tokenizer.h"
#include "util.h"
#include <fstream>

Tokenizer::Tokenizer() {}
Tokenizer::~Tokenizer() {}

int Tokenizer::add_token(string value) {
    if (value == "")
        return -1;
    
    tokens.push_back(value);
    return 0;
}

int Tokenizer::set(string key, string value) {
    settings.insert(make_pair(key, value));
    return 0;
}

int Tokenizer::preset(string name) {
    if (name == "c" || name == "cpp") {
        set("specials", "!#$%&()-^\\@[;:],./=~|`{+*}<>?");
        set("escaper", "\"'");
        set("ignores", "");
        set("ignoresplit", " \t\n");
        return 0;
    }

    return -1;
}

int Tokenizer::tokenize(string code) {
    string specials = settings.at("specials");
    string ignores = settings.at("ignores");
    string escaper = settings.at("escaper");
    string ignoresplit = settings.at("ignoresplit");

    tokens.clear();
    
    string little = "";
    int mode = 0;
    for (int i = 0; i < code.length(); ++i) {
        if (ignores.find(code[i]) != string::npos) continue;
        if (ignoresplit.find(code[i]) != string::npos) {
            add_token(little);
            little = "";
            continue;
        }

        if (mode != 0) {
            char escape_chr = escaper[mode-escape_mode_padding];
            if ((code[i-2] == '\\' || code[i-1] != '\\') && code[i] == escape_chr) {
                add_token(little);
                tokens.push_back(ctos(escape_chr));
                mode = 0;
                little = "";
            } else little += code[i];
        } else {
            if (escaper.find(code[i]) != string::npos) {
                mode = escape_mode_padding + escaper.find(code[i]);
                add_token(ctos(code[i]));
                continue;
            }
            
            if (specials.find(code[i]) != string::npos) {
                add_token(little);
                little = "";

                tokens.push_back(ctos(code[i]));
            } else little += code[i];
        }
    }

    return 0;
}

int Tokenizer::tokenize_file(string filename) {
    ifstream ifs(filename);

    if (!ifs) return -1;

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char *buffer = new char[length+1];
    ifs.read(buffer, length+1);
    buffer[length] = '\0';

    tokenize(buffer);

    delete[] buffer;

    return 0;
}

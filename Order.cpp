#include"Dictionary.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Please enter 2 arguments.\n Ex: Lex <input file> <output file>\n");
        return 1;
    }
    std::ifstream input;
    input.open(argv[1]);

    std::ofstream output;
    output.open(argv[2]);

    std::string key;
    int i = 1;
    Dictionary d;
    while(true){
        
        input >> key;
        if(input.eof()){
            break;
        }
        d.setValue(key, i);
        i++;
    }

    output << d;
    output << "\n";

    output << d.pre_string();
    output << "\n";
    return 0;
}
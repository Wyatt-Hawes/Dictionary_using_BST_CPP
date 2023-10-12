#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include"Dictionary.h"
#include<iostream>
#include<string>

int main(){

    //std::cout << "hello\n";
    /*
    Dictionary d;
    d.setValue("a", 1);
    d.setValue("b", 2);
    d.setValue("f", 7);
    d.setValue("g", 8);
    d.setValue("h", 9);
    d.setValue("c", 3);
    d.setValue("d", 4);
    d.setValue("e", 5);


    printf("------------------\n");
    std::cout << d.pre_string();
    printf("------------------\n");

    //d.remove("e");
    //d.remove("g");
    d.remove("f");

    printf("size: %d\n", d.size());
    printf("------------------\n");
    std::cout << d;
    printf("------------------\n");
    std::cout << d.pre_string();
    printf("------------------\n");
    */
   Dictionary A;
   Dictionary B;

    A.setValue("d", 2);
    A.setValue("d", 5);
    std::cout << "hi\n";
    if (A.size() != 1)
      std::cout << "fail 1\n";
      return 1;
    std::cout << "2\n";
    std::cout << "("+ std::to_string(A.getValue("d")) + ")\n";
    if (A.getValue("d") != 5)
      return 2;

    A.setValue("d", 1);

    if (A.getValue("d") != 1)
      return 3;

    A.remove("d");

    if (A.size() != 0)
      return 4;

    return 0;
}
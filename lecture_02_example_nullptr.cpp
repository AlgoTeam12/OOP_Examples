// example_nullptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//#define NULL 0

int* macro_null_ptr = NULL; // can work fine without explisit definition, as it can be defined in system library
                            //(vcruntime.h in my case, but can be in many others, as cstdio, cstring, etc)

#include "lecture_02_doingsomewrongstuffhere.h"
//You will get warning, if it will be ignored and not investigated it can crash you code

int* lucky_null_ptr = NULL; // it will crash your code that based on NULL == 0 assumption

#undef NULL
//Yeap, we can do it, no NULL for us now


// int* error_ptr = NULL; //error undeclared NULL

//So the nullptr is the way, as it is keyword and no one can mess with it 
int* proper_null_ptr = nullptr;

//and from C++11 NULL can be define as nullptr or 0, to repair our mess, but it is still better do not use it
//#define NULL nullptr 
#define NULL 0
//so NULL is implementation defined (0 in C++, nullptr in C++11 (or still 0), ((void*)0) in C)

//Also, there are some possible glitches with int 0 to pointer type conversion.  

template <typename T>
constexpr T copy(const T& x) { return x; }

void g(const int* p)
{
    if (p)
        std::cout << "Address is " << p << "; value by address is " << *p << std::endl;
    else
        std::cout << "Address is " << p << "; so no value for us" << std::endl;
}

int main()
{
    std::cout << "Macro:  " << macro_null_ptr << std::endl;
    std::cout << "Lucky:  " << lucky_null_ptr << std::endl;
    std::cout << "Proper: " << proper_null_ptr << std::endl;
    //int x = nullptr; //wrong conversion
    int x = 0;
    //int* ptr = x; //wrong conversion;
    int* ptr = 0; //work fine, as 0 is literal not int with 0 value
    int* ptr2 = &x;
    g(ptr);
    g(ptr2);
    g(nullptr);
    g(0);
    g(NULL);
    g(copy(ptr));
    g(copy(ptr2));
    g(copy(nullptr));
    // g(copy(0)); //error conversion int -> to int *
    // g(copy(NULL)); // error conversion
}


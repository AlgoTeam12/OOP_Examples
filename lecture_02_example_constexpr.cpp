// example_constexpr.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IN VS FOR THIS EXAMPLE YOU SHOULD USE CLANG, NOT MSVC compiler
// as it hit the wall with function(31) by Ñ1060 error (heap size problem),
// use option -Xclang -fconstexpr-steps -Xclang 200000000 to increase steps for constexpr evaluation and wait for a while...
// ....
// after that try evaluate how fast your code will execute first and second call of function and function2 with the same parameters

#include <iostream>
#include <chrono>


constexpr int function(int x)
{
    return x <= 1 ? 1 : function(x - 2) + function(x - 1);
}


int function2(int x)
{
    return x <= 1 ? 1 : function2(x - 2) + function2(x - 1);
}


int main()
{
    //compiler will precalculate it in compile time 
    auto start = std::chrono::high_resolution_clock::now();
    constexpr int x[10] = { function(26), function(27), function(28), function(29), function(30),
                        function(31), function(32), function(33), function(34), function(35) };
    int s = 0;
    for(int i = 0; i < 10; ++i)
        s += x[i];
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Result " << s << " - Elapsed time: " << elapsed.count() << " s\n";
    auto start2 = std::chrono::high_resolution_clock::now();
    //it will be calculated in run time 
    const int xx[10] = { function2(26), function2(27), function2(28), function2(29), function2(30),
                       function2(31), function2(32), function2(33), function2(34), function2(35) };
    int ss = 0;
    for (int i = 0; i < 10; ++i)
        ss += xx[i];
    auto finish2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = finish2 - start2;
    std::cout << "Result " << ss << " - Elapsed time: " << elapsed2.count() << " s\n";

}

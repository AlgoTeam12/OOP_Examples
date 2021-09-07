// example_namespaces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int commonnamevariable = 0;

namespace MEPhI2021 {
    int commonnamevariable = 2021;
    namespace dozen12 {
        int commonnamevariable = 12;
        int someothervariable = 29;
    }
}

int somevariabletobreakthenamespace = 30;
//int anothervariable = 1; //2

namespace MEPhI2021
{
    namespace dozen12 {
        int anothervariable = 42;
    }
}

//just try to uncomment or comment some strings and learn about outcome

int main()
{
    std::cout << "Global namespace\n";
    std::cout << commonnamevariable << std::endl;
    std::cout << ::commonnamevariable << std::endl;
    std::cout << MEPhI2021::commonnamevariable << std::endl;
    std::cout << MEPhI2021::dozen12::commonnamevariable << std::endl;
    //std::cout << anothervariable << std::endl; //error

    using MEPhI2021::commonnamevariable;
    //using namespace MEPhI2021; //1

    std::cout << "commonnamevariable from MEPhI namespace\n";
    std::cout << commonnamevariable << std::endl;
    std::cout << ::commonnamevariable << std::endl;
    std::cout << MEPhI2021::commonnamevariable << std::endl;
    std::cout << MEPhI2021::dozen12::commonnamevariable << std::endl;
    //std::cout << dozen12::anothervariable << std::endl; //error without 1
    //std::cout << anothervariable << std::endl; //error without 2

    using namespace MEPhI2021::dozen12;
    
    
    //{
    //using MEPhI2021::dozen12::commonnamevariable;

        std::cout << "MEPhI::dozen namespace\n";
        std::cout << commonnamevariable << std::endl;
        std::cout << ::commonnamevariable << std::endl;
        std::cout << MEPhI2021::commonnamevariable << std::endl;
        std::cout << MEPhI2021::dozen12::commonnamevariable << std::endl;
        std::cout << anothervariable << std::endl; //would be error with 2
    //}

}



// example_exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
// It shows some trivial errors handling techniques
// We do not provide advanced examples with complex error types or 'global' error states, accessible by some functions
// (for example, as it done in COM API with HRESULT and GetLastError())

#include <iostream>

//C++ style enum is here, you can remove 'class' but probably will receive some warnings from compiler or IDE
enum class errorcode {jobdone, indexerror, invalidpointer};

// some errors 'handling', we just report about it
void dosomethingwitherror(const errorcode& check)
{
    switch (check)
    {
        case errorcode::invalidpointer:
        {
            std::cerr << "Null pointer is passed as the string argument" << std::endl;
            break;
        }
        case errorcode::indexerror:
        {
            std::cerr << "The index is higher (or equal) then the string length" << std::endl;
            break;
        }
        case errorcode::jobdone:
        {
            // it will not fire with proper use of this function, but who knows... we just ignore error handling in case if job was done, nothing to report
            break;
        }
        default:
        {
            std::cerr << "Unknown error" << std::endl; // it is not possible, but who knows if someone will touch our code with dirty hands
        }
    }  
}

//errors hadling without exceptions V1

errorcode dangerousfunctionwithoutexceptions (const char* str, size_t index, char& result) noexcept
{
    // if you have dirty hands, uncomment string below
    // throw 12; //try to throw something, it should be warned by compiler due noexcept specification, you will crash your code by this
    if (!str)
    {
        result = 0; // you can do nothing here, sometimes is better do not touch result at all, but 0 value is ok too
        return errorcode::invalidpointer;
    }
    if (index >= strlen(str))
    {
        result = 0; // same story
        return errorcode::indexerror;
    }
    result = str[index];
    return errorcode::jobdone;
}

void handler1(const char* str, size_t index)
{
    std::cout << "V1: ";
    char result = 0;
    errorcode check = dangerousfunctionwithoutexceptions(str, index, result);
    if (check == errorcode::jobdone) // we should try positive variant first if it is more frequent than others to generate slightly faster code 
        std::cout << "Result is '" << result << "'" << std::endl;
    else
        dosomethingwitherror(check);
}

//errors hadling without exceptions V2, slightly different than V1

char dangerousfunctionwithoutexceptions(const char* str, size_t index, errorcode& error) noexcept
{
    if (!str)
    {
        error = errorcode::invalidpointer;
        return 0; //you shoud return something, zero value is ok, but we didn't trust result if error code is not jobdone
    }
    if (index >= strlen(str))
    {
        error = errorcode::indexerror; 
        return 0; // same story
    }
    error = errorcode::jobdone;
    return str[index];

}

void handler2(const char* str, size_t index)
{
    std::cout << "V2: ";
    errorcode check = errorcode::jobdone;
    char result = dangerousfunctionwithoutexceptions(str, index, check);
    if (check == errorcode::jobdone) // we should try positive variant first if it is more frequent than others to generate slightly faster code 
        std::cout << "Result is '" << result << "'" << std::endl;
    else
        dosomethingwitherror(check);
}

//errors handling with exceptions V1 (V3 for illustration)

char dangerousfunctionwithexceptions(const char* str, size_t index) // we can provide throw(...) or throw(errorcode) (deprecated) specification,
                                                                   // but it is better (according C++17) do not provide it at all 
{
    // if you have dirty hands, uncomment string below
    // throw 12; //try to throw something unexpected, it should work as we have catch(...)

    if (!str)
        throw errorcode::invalidpointer;
    if (index >= strlen(str))
        throw errorcode::indexerror;
    return str[index];
}

void handler3(const char* str, size_t index)
{
    std::cout << "V3: ";
    try 
    {
        char result = dangerousfunctionwithexceptions(str, index);
        std::cout<<"Result is '" << result << "'" << std::endl;
        // You can write it without 'result' variable (as one line code), and effect, probably, would be the same, but think what can be wrong here in that case
    }
    catch (errorcode& check)
    {
        dosomethingwitherror(check);
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl; // it is not possible, but who knows if someone will touch our code with dirty hands 
    }
    //The code is pretty, isn't it?
}

// errors handling with exceptions V2 (V4 for illustration)
// (with use of exceptions from standard library) 
#include <exception>
#include <string>
char dangerousfunctionwithexceptions2(const char* str, size_t index) // we can provide throw(...) or throw(errorcode) (deprecated) specification,
                                                                     // but it is better (according C++17) do not provide it at all 
{
    // if you have dirty hands, uncomment string below
    // throw 12; //try to throw something unexpected, it should work as we have catch(...)

    if (!str)
        throw std::invalid_argument("Null pointer is passed as the string argument");
    if (index >= strlen(str))
        //throw std::out_of_range("The index is higher then the string length");
        //you can try do make it more fancy (and useful) with a small touch of strings and c++11  
        throw std::out_of_range("The index (" + std::to_string(index) + 
            ") is higher (or equal) then the string length (" + 
            std::to_string(strlen(str)) + ")");

    return str[index];
}

void handler4(const char* str, size_t index)
{
    std::cout << "V4: ";
    try
    {
        char result = dangerousfunctionwithexceptions2(str, index);
        std::cout << "Result is '" << result << "'" << std::endl;
        // You can write it without 'result' variable (as one line code), and effect, probably, would be the same, but think what can be wrong here in that case
    }
    catch (std::invalid_argument& check)
    {
        std::cerr << check.what() << std::endl;
    }
    catch (std::out_of_range& check)
    {
        std::cerr << check.what() << std::endl;
    }
    catch (std::exception& check)
    {
        // just show the what message in case unexpected std::exception
        // BTW, you can leave only this string, and comment catchers for invalid_argument and out_of_range
        std::cerr << check.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl; // it is not possible, but who knows if someone touch our code with dirty hands 
    }
}

//exceptions and dynamic resources allocation by new

void complexfunction(bool condition) {
    //you need some resources with c-(old-)style pointers to do the job
    //it is better to use some wrapper (hello, OOP...) or standard stl pointers
    const int sz = 10;
    int* a = new int[sz]; // please, be aware that new can throw std::bad_alloc if it can give you requested memory
                          // otherwise use new (std::nothrow) int[sz] from <new> header (#include <new>)
                          // the situatuation can became more grim if you have multiple pointers to multiple dynamicly allocated memory pieces
    
    //.... we do something useful here....
    
    //oops, we forget to check some condition
    //so now the time to check it and abort mission
    // (obviously, it chould be checked before, but we do it here to show the problem)
    
    if (!condition)
    {
        delete[] a; // <- DO NOT FORGET TO CLEAN UP ALLOCATED RESOURCES, OTHERWISE YOU'LL GET MEMORY LEAK
        throw std::logic_error("The condition is not meet");
    }
    //....continue you job...
    delete[] a;
}

//EXERCISE: handle all potential memory leaks here, but not temper the function 'logic'
void veryleakycomplexfunction(bool condition1, bool condition2) {
    const int sz = 10;
    int* a = new int[sz];
    int** b = new int*[sz];

    //.....doing something with a and b .....

    if (!condition1)
    {
        throw std::logic_error("The condition 1 is not meet");
    }
    for (size_t i = 0; i < sz; ++i)
        b[i] = new int[sz];
 
    //.....doing something with a and b.....
    
    if (!condition2)
    {
        throw std::logic_error("The condition 2 is not meet");
    }
    int* c = new int[sz];

    //..... doing something with a and b and c.....

}


int main()
{
    //PART 1: errors handling examples
    // A lot of C++11 "magic" here, just ignore it for now or try understand if you dare ^_^
    // Here we call all or functions with ("mephi", 4), ("mipt", 4) and (nullptr, 4) arguments, and handle the errors. 
    const char* strs[] = {"mephi", "mipt", nullptr};
    decltype (handler1) (*handlers[]) = {&handler1, &handler2, &handler3, &handler4};
    size_t index = 4;

    for (auto str : strs)
    {
        for (auto handler : handlers)
        {
            handler(str, index);
        }
        
    }
    std::cout << "...................................................................." << std::endl;
    //PART 2: new and exceptions 
    try {
        complexfunction(false); // will throw for sure
    }
    catch (std::logic_error& error)
    {
        std::cerr << error.what() << std::endl;
    }
    catch (std::bad_alloc& error)
    {
        // we should add it, if we don't want to crashed ours program in case of memory allocation problem
        std::cerr << "Memory exhausted: there is no place for 'a' array" << std::endl;
    }
}

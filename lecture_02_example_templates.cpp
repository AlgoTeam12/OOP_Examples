// example_templates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T> void swap(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}

struct SomeDataType {
    int a; double b;
};

template <typename Key, typename Value>
void print_key_value(const Key& k, const Value& v)
{
    std::cout << "Key - " << k << ", value - " << v << std::endl; 
    //attention: overload of << for std::ostream Key and Value should be defined, otherwise if will be error (see SomeDataType)
    //see the next definition
 
}

// a bit of "street magic", uncomment it if required 
//std::ostream& operator<<(std::ostream& os, const SomeDataType& data)
//{
//    os << "<" << data.a << ", " << data.b << ">";
//    return os;
//}

int main()
{
    int a = 12, b = 42;
    double c = 0.12, d = 0.42;
    SomeDataType x = {1, .2}, y = {3, .4};

    std::cout << a <<" "<< b <<std::endl;
    swap(a, b);
    std::cout << a << " " << b << std::endl;

    std::cout << c << " " << d << std::endl;
    swap(c, d);
    std::cout << c << " " << d << std::endl;
    
    std::cout << a << " " << b << std::endl;
    std::swap(a, b); // <- standard swap from std namespace. It worked fine, so we do almost useless work with our own swap ^_~
    std::cout << a << " " << b << std::endl;
    
    //std::cout << x << " " << y << std::endl; // the street magic is required
    swap(x, y); // is ok, you can check the value, default = it is working fine for SomeDataType, but not a case in general
    //std::cout << x << " " << y << std::endl; // the street magic is required
    
    
    //error
    //std::cout << a << " " << d << std::endl;
    //swap(a, d); // error
    //std::cout << a << " " << d << std::endl;
    //std::swap()

    print_key_value(a, b);
    print_key_value(b, c);
    print_key_value(c, d);
    print_key_value(d, a);

    //print_key_value(x, y); // will be error without "a bit of street magic", as << is not defined for std::ostream and SomeDataType
    //uncomment it separatelly and together 

   
}

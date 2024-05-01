#include "String.h"
#include <iostream>

int main()
{
    String s("aaa");
    String s2 = s;
    std::cout << s2 << std::endl;
    String s3("bbb");
    std::cout << s2 + s3 << std::endl;
    s2 += s3;
    std::cout << s2 << std::endl;
}
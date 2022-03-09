#include <iostream>

#include "matrix.h"

int main() {
    TMatrix a, b;
    std::cin >> a;
    b = a;
    std::cout << b << b.det() << std::endl;
    std::cout << a * b;
    b *= a;
    std::cout << b;
    std::cout << (a == b) << std::endl;
    return 0;
}

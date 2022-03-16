#include <iostream>
#include <cmath>

#include "matrix.h"

int main() {
    TMatrix a, b;
    std::cin >> a;
    b = a;
    std::cout << b << b.det() << std::endl;
    std::cout << pow(a, 2);
    std::cout << std::pow(3, 2) << std::endl;
    b *= a;
    std::cout << b;
    std::cout << (a == b) << std::endl;
    return 0;
}

#include <iostream>
#include <string>

#include "matrix.h"

void MainMenu();

int main() {
    MainMenu();
    return 0;
}

void MainMenu() {
    std::string input;
    std::getline(std::cin, input);
    while (input[0] != 'q') {
        // ...
        std::getline(std::cin, input);
    }
}

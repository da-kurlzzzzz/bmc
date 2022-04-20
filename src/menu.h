#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include <vector>

#include "matrix.h"

class TMenu {
private:
    std::string input;
    enum State {
        STATE_MAIN,
        STATE_EXEC,
        STATE_READ_NAME
    } s;

    std::vector<TMatrix> matrices;
    std::vector<double> constants;

    static const int len = 'z' - 'a' + 1;

    void Process();
    void Get();
    void ReadParam();
    void PrintParam();
    void Execute();
    void PrintHelp();
    void PrintVersion();
    int Index();

public:
    TMenu();
    void Start();
};

#endif // MENU_H_INCLUDED

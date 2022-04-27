#include "menu.h"

#include <cctype>

TMenu::TMenu() {
    this->matrices.resize(TMenu::len);
    this->constants.resize(TMenu::len);
    this->s = STATE_MAIN;
    this->input = "";
}

void TMenu::Start() {
    this->Get();
    while (this->s != STATE_MAIN || this->input[0] != 'q') {
        this->Process();
        this->Get();
    }
}

void TMenu::Process() {
    switch (this->input[0]) {
    case 'r': // read
        this->s = STATE_READ_NAME;
        this->Get();
        this->s = STATE_MAIN;
        this->ReadParam();
        break;
    case 'p': // print
        this->s = STATE_READ_NAME;
        this->Get();
        this->s = STATE_MAIN;
        this->PrintParam();
        break;
    case 'e': // execute
        this->s = STATE_EXEC;
        this->Execute();
        this->s = STATE_MAIN;
        break;
    case 'z': // zero
        this->matrices.clear();
        this->constants.clear();
        this->matrices.resize(TMenu::len);
        this->constants.resize(TMenu::len);
        break;
    case 'h': // help
        this->PrintHelp();
        break;
    case 'v': // version
        this->PrintVersion();
        break;
    }
}

int TMenu::Index() {
    return this->input[0] - (islower(this->input[0]) ? 'a' : 'A');
}

void TMenu::ReadParam() {
    if (islower(this->input[0])) {
        std::cin >> this->constants.at(this->Index());
    }
    else {
        std::cin >> this->matrices.at(this->Index());
    }
}

void TMenu::PrintParam() {
    if (islower(this->input[0])) {
        std::cout << this->constants.at(this->Index());
        std::cout << "\n";
    }
    else {
        std::cout << this->matrices.at(this->Index());
    }
}

void TMenu::Get() {
    switch (this->s) {
    case STATE_MAIN:
        std::cout << "Input command (h for help): ";
        break;
    case STATE_READ_NAME:
        std::cout << "Input parameter name (A-Z,a-z): ";
        break;
    case STATE_EXEC:
        std::cout << "Input operation (+,-,*,/,^,t,d,n): ";
        break;
    default:
        throw std::runtime_error("Bug in Menu");
    }
    std::getline(std::cin, this->input);
}

void TMenu::Execute() {
    this->Get();
    char command = this->input[0];
    this->s = STATE_READ_NAME;
    this->Get();
    auto& lv = this->matrices.at(this->Index());
    this->s = STATE_READ_NAME;
    this->Get();
    auto& rv = this->matrices.at(this->Index());
    this->s = STATE_READ_NAME;
    this->Get();
    auto& to = this->matrices.at(this->Index());
    switch (command) {
    case '+':
        to = lv + rv;
        break;
    case '-':
        to = lv - rv;
        break;
    case '*':
        to = lv * rv;
        break;
    case '/':
        to = lv / rv;
        break;
    case '^':
        to = pow(lv, rv.data[0][0]);
        break;
    case 't':
        to = lv.transposed();
        break;
    case 'd':
        to = lv.det();
        break;
    case 'n':
        to = lv.norm();
        break;
    }
}

void TMenu::PrintHelp() {
    std::cout << "available commands:\n"
                 "(r)ead\n"
                 "(p)rint\n"
                 "(e)xecute\n"
                 "(z)ero\n"
                 "(h)elp\n"
                 "(v)ersion\n";
}
void TMenu::PrintVersion() {
    std::cout << "Made by da-kurlzzzzz\n";
}

#include "matrix.h"

#include <string>
#include <sstream>

TMatrix::TMatrix(int rows, int cols, int diag_elem) {
    if (cols == -1) {
        cols = rows;
    }
    this->data.resize(rows);
    for (unsigned i = 0; i < this->data.size(); ++i) {
        this->data.at(i).resize(cols);
        this->data.at(i).at(i) = diag_elem;
    }
}

int TMatrix::height() const {
    return this->data.size();
}

int TMatrix::width() const {
    return this->data.at(0).size();
}

void TMatrix::check_nonempty() const {
    if (this->data.empty() || this->data.at(0).empty()) {
        throw std::runtime_error("empty matrix");
    }
}

void TMatrix::check_consistency() const {
    for (auto row : this->data) {
        if (row.size() != this->data.at(0).size()) {
            throw std::runtime_error("inconsistent number of elements in matrix");
        }
    }
}

std::ostream& operator<<(std::ostream& out, const TMatrix& rv) {
    for (auto row : rv.data) {
        for (auto elem = row.begin(); elem != row.end(); ++elem) {
            out << *elem;
            if (std::next(elem) != row.end()) {
                out << " ";
            }
        }
        out << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, TMatrix& rv) {
    rv.data.clear();
    std::vector<double> row;
    do {
        std::string str;
        std::getline(in, str);
        std::istringstream iss(str);
        row.clear();
        for (double input; iss >> input; ) {
            row.push_back(input);
        }
        if (!row.empty()) {
            rv.data.push_back(row);
        }
    } while (!row.empty());
    rv.check_nonempty();
    rv.check_consistency();
    return in;
}

#include "matrix.h"

#include <string>
#include <sstream>
#include <cmath>

TMatrix::TMatrix(int rows, int cols, int diag_elem) {
    if (cols == -1) {
        cols = rows;
    }
    this->data.resize(rows);
    for (unsigned i = 0; i < this->data.size(); ++i) {
        this->data.at(i).resize(cols);
        this->data.at(i).at(i) = diag_elem;
    }
    this->check_nonempty();
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

void TMatrix::check_consistent() const {
    for (auto row : this->data) {
        if (row.size() != this->data.at(0).size()) {
            throw std::runtime_error("inconsistent number of elements in matrix");
        }
    }
}

void TMatrix::check_additive(const TMatrix& rv) const {
    if (this->height() != rv.height() || this->width() != rv.width()) {
        throw std::runtime_error("incompatible sizes for addition");
    }
}

void TMatrix::check_multiplicative(const TMatrix& rv) const {
    if (this->width() != rv.height()) {
        throw std::runtime_error("incompatible sizes for multiplication");
    }
}

TMatrix& TMatrix::operator+=(const TMatrix& rv) {
    this->check_additive(rv);
    for (int i = 0; i < this->height(); ++i) {
        for (int j = 0; j < this->width(); ++j) {
            this->data.at(i).at(j) += rv.data.at(i).at(j);
        }
    }
    return *this;
}

TMatrix& TMatrix::operator*=(double rv) {
    for (auto& row : this->data) {
        for (auto& elem : row) {
            elem *= rv;
        }
    }
    return *this;
}

TMatrix TMatrix::operator*(double rv) const {
    TMatrix result = *this;
    return result *= rv;
}

TMatrix& TMatrix::operator-=(const TMatrix& rv) {
    return *this += (rv * -1);
}

TMatrix TMatrix::operator+(const TMatrix& rv) const {
    TMatrix result = *this;
    return result += rv;
}

TMatrix TMatrix::operator-(const TMatrix& rv) const {
    TMatrix result = *this;
    return result -= rv;
}

TMatrix TMatrix::operator/(double rv) const {
    return *this * (1 / rv);
}

TMatrix& TMatrix::operator/=(double rv) {
    return *this *= (1 / rv);
}

TMatrix TMatrix::operator*(const TMatrix& rv) const {
    this->check_multiplicative(rv);
    TMatrix result(this->height(), rv.width(), 0);
    for (int i = 0; i < result.height(); ++i) {
        for (int j = 0; j < result.width(); ++j) {
            for (int k = 0; k < this->width(); ++k) {
                result.data.at(i).at(j) += this->data.at(i).at(k) * rv.data.at(k).at(j);
            }
        }
    }
    return result;
}

TMatrix& TMatrix::operator*=(const TMatrix& rv) {
    return *this = *this * rv;
}

bool TMatrix::operator==(const TMatrix& rv) const {
    try {
        this->check_additive(rv);
    }
    catch (const std::runtime_error& e) {
        return false;
    }
    for (int i = 0; i < this->height(); ++i) {
        for (int j = 0; j < this->width(); ++j) {
            if (this->data.at(i).at(j) != rv.data.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

bool TMatrix::operator!=(const TMatrix& rv) const {
    return !(*this == rv);
}

TMatrix TMatrix::transposed() const {
    TMatrix result(this->width(), this->height());
    for (int i = 0; i < result.height(); ++i) {
        for (int j = 0; j < result.width(); ++j) {
            result.data.at(i).at(j) = this->data.at(j).at(i);
        }
    }
    return result;
}

TMatrix TMatrix::inverted() const {
    TMatrix result(this->height(), this->width());
    for (int i = 0; i < result.height(); ++i) {
        for (int j = 0; j < result.width(); ++j) {
            result.data.at(i).at(j) = this->cofactor(i, j);
        }
    }
    result = result.transposed() / this->det();
    return result;
}

TMatrix TMatrix::sub(int i_sub, int j_sub) const {
    TMatrix result(this->height() - 1, this->width() - 1);
    for (int i = 0; i < result.height(); ++i) {
        for (int j = 0; j < result.width(); ++j) {
            int i_delta = (i < i_sub ? 0 : 1),
                j_delta = (j < j_sub ? 0 : 1);
            result.data.at(i).at(j) = this->data.at(i + i_delta).at(j + j_delta);
        }
    }
    return result;
}

double TMatrix::minor(int i_sub, int j_sub) const {
    return this->sub(i_sub, j_sub).det();
}

double TMatrix::cofactor(int i_sub, int j_sub) const {
    return this->minor(i_sub, j_sub) * std::pow(-1, i_sub + j_sub);
}

double TMatrix::det() const {
    if (!this->is_square()) {
        throw std::runtime_error("determinant is defined for square matrix only");
    }
    if (this->height() == 1) {
        return this->data.at(0).at(0);
    }
    double result = 0;
    for (int i = 0; i < this->height(); ++i) {
        result += this->data.at(0).at(i) * this->cofactor(0, i);
    }
    return result;
}

double TMatrix::norm() const {
    double result = 0;
    for (auto row : this->data) {
        for (auto elem : row) {
            if (result < std::abs(elem)) {
                result = std::abs(elem);
            }
        }
    }
    return result;
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
    rv.check_consistent();
    return in;
}

bool TMatrix::is_square() const {
    return this->height() == this->width();
}

bool TMatrix::is_diagonal() const {
    return this->is_triangular_upper() && this->is_triangular_lower();
}

bool TMatrix::is_zero() const {
    return *this == TMatrix(this->height(), this->width(), 0);
}

bool TMatrix::is_identity() const {
    return this->is_square() && *this == TMatrix(this->height(), this->width(), 1);
}

bool TMatrix::is_symmetric() const {
    return *this == this->transposed();
}

bool TMatrix::is_triangular_upper() const {
    if (!this->is_square()) {
        return false;
    }
    for (int i = 0; i < this->height(); ++i) {
        for (int j = 0; j < this->width(); ++j) {
            if (i > j && this->data.at(i).at(j) != 0) {
                return false;
            }
        }
    }
    return true;
}

bool TMatrix::is_triangular_lower() const {
    return this->transposed().is_triangular_upper();
}

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>

class TMatrix {
private:
    std::vector<std::vector<double> > data;

    void check_nonempty() const;
    void check_consistent() const;
    void check_additive(const TMatrix& rv) const;
    void check_multiplicative(const TMatrix& rv) const;

    TMatrix sub(int i_sub, int j_sub) const;
    double minor(int i_sub, int j_sub) const;

    friend std::ostream& operator<<(std::ostream& out, const TMatrix& rv);
    friend std::istream& operator>>(std::istream& in, TMatrix& rv);

    friend TMatrix pow(const TMatrix& base, int exponent);

public:
    TMatrix(int rows = 1, int cols = -1, int diag_elem = 1);

    int height() const;
    int width() const;

    TMatrix operator+(const TMatrix& rv) const;
    TMatrix operator-(const TMatrix& rv) const;
    TMatrix operator*(const TMatrix& rv) const;
    TMatrix operator*(double rv) const;
    TMatrix operator/(const TMatrix& rv) const;
    TMatrix operator/(double rv) const;

    TMatrix& operator+=(const TMatrix& rv);
    TMatrix& operator-=(const TMatrix& rv);
    TMatrix& operator*=(const TMatrix& rv);
    TMatrix& operator*=(double rv);
    TMatrix& operator/=(const TMatrix& rv);
    TMatrix& operator/=(double rv);

    bool operator==(const TMatrix& rv) const;
    bool operator!=(const TMatrix& rv) const;

    TMatrix inverted() const;
    TMatrix transposed() const;

    double det() const;
    double norm() const;

    bool is_square() const;
    bool is_diagonal() const;
    bool is_zero() const;
    bool is_identity() const;
    bool is_symmetric() const;
    bool is_triangular_upper() const;
    bool is_triangular_lower() const;
};

#endif // MATRIX_H_INCLUDED

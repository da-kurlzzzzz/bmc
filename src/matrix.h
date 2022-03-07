#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>

class TMatrix {
private:
    std::vector<std::vector<double> > data;
    void check_nonempty() const;
    void check_consistency() const;
    friend std::ostream& operator<<(std::ostream& out, const TMatrix& rv);
    friend std::istream& operator>>(std::istream& in, TMatrix& rv);
public:
    TMatrix(int rows = 1, int cols = -1, int diag_elem = 1);
    int height() const;
    int width() const;
};

#endif // MATRIX_H_INCLUDED

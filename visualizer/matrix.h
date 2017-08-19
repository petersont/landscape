#ifndef _MATRIX_
#define _MATRIX_

#include <stdio.h>
#include <assert.h>

class Matrix;




class Matrix {

private:
    int rows,columns;

    void allocate();
    void deallocate();
    void match(const Matrix& M);

public:
    double** entries;

    Matrix();
    Matrix( int inrows, int incolumns );
    Matrix( const class Matrix& M );
    ~Matrix();

    void setSize( int inrows, int incolumns );

    Matrix& set(const double* a);

    void print() const;
    void display() const;

    Matrix& zero();
    Matrix& identity();

    Matrix transpose() const;
    Matrix inverse() const;
    Matrix solve(const Matrix& b) const;

    Matrix& gaussianElimination(Matrix& M);
    Matrix& rowOpp(int r1, int r2, double a1, double b1, double a2, double b2); //does r1+=k*r2

    double det() const;

    Matrix& operator= (const Matrix& M);
    Matrix operator+ (const Matrix& M) const;
    Matrix& operator+= (const Matrix& M);
    Matrix operator- (const Matrix& M) const;
    Matrix& operator-= (const Matrix& M);
    Matrix operator* (const Matrix& M) const;

    Matrix operator* (double k);
    friend Matrix operator* (double k, Matrix M) {return M*k;}
    Matrix operator/ (double k);
    Matrix& operator*= (double k);
    Matrix& operator/= (double k);
};


#endif

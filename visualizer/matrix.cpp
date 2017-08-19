
#include <stdio.h>
#include <math.h>
#include "matrix.h"


void Matrix::allocate()
{
    entries = new double*[columns];
    for( int i=0; i<columns; i++ )
        entries[i] = new double[rows];
}

void Matrix::deallocate()
{
    for( int i=0; i<columns; i++ )
        delete[] entries[i];
    delete[] entries;
}

void Matrix::match(const Matrix& M)
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        entries[i][j] = M.entries[i][j];
}




/****************/
/*public methods*/
/****************/

Matrix::Matrix()
{
    rows = columns = 1;
    allocate();
}

Matrix::Matrix( int inrows, int incolumns )
{
    rows = inrows;
    columns = incolumns;
    allocate();
}

Matrix::Matrix( const class Matrix& M )
{
    rows = M.rows;
    columns = M.columns;
    allocate();
    match(M);
}

void Matrix::setSize( int inrows, int incolumns )
{
    if( rows != inrows || columns != incolumns )
    {
        deallocate();
        rows = inrows;
        columns = incolumns;
        allocate();
    }
}

Matrix::~Matrix()
{
    deallocate();
}

Matrix& Matrix::set(const double* a)
{
    int counter = 0;
    for(int j=0; j<rows; j++)
    for(int i=0; i<columns; i++)
        entries[i][j] = a[counter++];

    return *this;
}


void Matrix::print() const
{
    for( int j=0; j<rows; j++ )
    {
        for( int i=0; i<columns; i++ )
            printf( "%f\t", entries[i][j] );

        printf( "\n" );
    }
}

void Matrix::display() const
{
    print();
    printf( "\n" );
}

Matrix& Matrix::zero()
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        entries[i][j] = 0.0;
    return *this;
}

Matrix& Matrix::identity()
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        entries[i][j] = (i==j)?1.0:0.0;
    return *this;
}

Matrix Matrix::transpose() const
{
    Matrix M(columns,rows);
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        M.entries[j][i] = entries[i][j];

    return M;
}


Matrix& Matrix::operator= (const Matrix& M)
{
    setSize(M.rows,M.columns);
    match(M);
    return *this;
}

Matrix Matrix::operator+ (const Matrix& M) const
{
    assert( rows == M.rows && columns == M.columns );
    Matrix R(*this);
    R+=M;
    return R;
}

Matrix& Matrix::operator+= (const Matrix& M)
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        entries[i][j] += M.entries[i][j];

    return *this;
}

Matrix Matrix::operator- (const Matrix& M) const
{
    assert( rows == M.rows && columns == M.columns );
    Matrix R(*this);
    R-=M;
    return R;
}

Matrix& Matrix::operator-= (const Matrix& M)
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
        entries[i][j] -= M.entries[i][j];

    return *this;
}


Matrix Matrix::operator* (const Matrix& M) const
{
    int middle;
    assert(M.rows == columns);
    middle = columns;

    Matrix R(rows,M.columns);

    for( int j=0; j<rows; j++ )
    for( int i=0; i<M.columns; i++ )
    {
        double t=0.0;
        for( int k=0; k<middle; k++ )
            t += entries[k][j] * M.entries[i][k];
        R.entries[i][j] = t;
    }

    return R;
}

Matrix Matrix::inverse() const
{
    assert(rows==columns);

    Matrix I(rows,columns);
    I.identity();
    Matrix M(*this);
    M.gaussianElimination(I);
    return I;
}

Matrix Matrix::solve(const Matrix& b) const
{
    Matrix x(b);
    Matrix M(*this);
    M.gaussianElimination(x);
    return x;
}

double Matrix::det() const
{
    double R = 1.0;

    assert( rows==columns );

    Matrix M(*this);

    for( int i=0; i<columns; i++ )
    {
        double maxsofar=M.entries[i][i];
        int index=i;
        for( int j=i+1; j<rows; j++ )
        {
            if(fabs(M.entries[i][j])>maxsofar)
            {
                index=j;
                maxsofar = fabs(M.entries[i][j]);
            }
        }

        if(i!=index) M.rowOpp(i, index, 0.0,1.0, -1.0,0.0);
        double aii = M.entries[i][i];
        R*=aii;
        M.rowOpp(i,i, 1.0/aii,0, 1.0/aii,0); //what the hay

        for( int j=i+1; j<rows; j++ )
        {
            double t = M.entries[i][j];
            M.rowOpp(i,j, 1,0, -t,1);
        }
    }

    return R;
}


Matrix Matrix::operator* (double k)
{
    Matrix M(*this);

    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
    {
        M.entries[i][j]*=k;
    }

    return M;
}

Matrix Matrix::operator/ (double k)
{
    Matrix M(*this);

    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
    {
        M.entries[i][j]/=k;
    }

    return M;
}

Matrix& Matrix::operator*= (double k)
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
    {
        entries[i][j]*=k;
    }
    return *this;
}

Matrix& Matrix::operator/= (double k)
{
    for( int j=0; j<rows; j++ )
    for( int i=0; i<columns; i++ )
    {
        entries[i][j]/=k;
    }
    return *this;
}



Matrix& Matrix::gaussianElimination(Matrix& M)
{
    for( int i=0; i<columns; i++ )
    {
        double maxsofar=fabs(entries[i][i]);
        int index=i;
        for( int j=i+1; j<rows; j++ )
        {
            if(fabs(entries[i][j])>maxsofar)
            {
                index=j;
                maxsofar = fabs(entries[i][j]);
            }
        }

        rowOpp(i, index, 0.0,1.0, -1.0,0.0);
        M.rowOpp(i, index, 0.0,1.0, -1.0,0.0);

        double aii = entries[i][i];
        rowOpp(i,i, 1.0/aii,0,1.0/aii,0);
        M.rowOpp(i,i, 1.0/aii,0,1.0/aii,0);

        for( int j=i+1; j<rows; j++ )
        {
            double t = entries[i][j];
            rowOpp(i,j, 1,0, -t,1);
            M.rowOpp(i,j, 1,0, -t,1);
        }
    }


    for( int i=0; i<columns; i++ )
    {
        for( int j=i-1; j>=0; j-- )
        {
            double t = entries[i][j];
            rowOpp(i,j, 1,0, -t,1);
            M.rowOpp(i,j, 1,0, -t,1);
        }
    }

    return *this;
}


Matrix& Matrix::rowOpp(int r1, int r2, double a1, double b1, double a2, double b2)
{
    for( int i=0; i<columns; i++ )
    {
        double t = entries[i][r1];
        double u = entries[i][r2];

        entries[i][r1] = a1*t + b1*u;
        entries[i][r2] = a2*t + b2*u;
    }

    return *this;
}






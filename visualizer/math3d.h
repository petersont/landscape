
#ifndef _MATH3D_
#define _MATH3D_

#include <stdio.h>
#include <math.h>

#include <vector>
#include <list>
#include <map>
#include <set>


using namespace std;

namespace lib3d {


#define sgn(X) ((X)<0?(-1):1)
#define abs(X) ((X)<0?(-(X)):(X))
int mymod( int n, int m );
double squareOf(double t);
double min( double n, double m );
double max( double n, double m );

#define PI (3.1415926535897931)
#define ONE_OVER_PI (0.31830988618379069)

struct trig_pair {double cos,sin;};
trig_pair sin_and_cos(double);

vector<double> quad_form(double a, double b, double c);

#define QUAD_FORM(A,B,C,r1,r2) { double a=A,b=B,c=C; double q = -0.5*( b + sgn(b)*sqrt(b*b - 4.0*a*c) ); r1 = q/a; r2 = c/q; }


class Vector2d {
public:

    double x,y;

    Vector2d() { x=y=0; }
    Vector2d( double inx, double iny ) { x = inx; y = iny; }
    Vector2d( const class Vector2d& V ) { x = V.x; y = V.y; }
    ~Vector2d() {}

    inline double mag() const { return (sqrt(x*x+y*y)); }
    inline double magSquared() const { return (x*x+y*y); }
    inline double dot( const class Vector2d& V ) const { return ( x*V.x + y*V.y ); }
    inline void set( double inx, double iny ) {x = inx; y = iny;}

    class Vector2d projectOnto( const class Vector2d& V ) const;
    class Vector2d reflectAbout( const class Vector2d& V ) const;

    Vector2d perp() const;
    Vector2d right() const;
    Vector2d left() const;
    double angle() const;

    double theta( const Vector2d V ) const;
    double angleTo( const Vector2d V ) const;

    bool between(const Vector2d U, const Vector2d V) const;
    bool betweenInclusive(const Vector2d U, const Vector2d V) const;


    inline class Vector2d& operator = (const class Vector2d& V) {
        x = V.x;
        y = V.y;
        return *this;
    }

    inline class Vector2d operator - () const {
        Vector2d V( -x,-y );
        return V;
    }

    inline friend class Vector2d operator * (Vector2d V, double r) {
        Vector2d U;
        U.x = V.x*r;
        U.y = V.y*r;
        return U;
    }

    inline friend class Vector2d operator * (double r, Vector2d V) {
        return V*r;
    }

    inline class Vector2d operator / (double r) const {
        Vector2d V;
        V.x = x/r;
        V.y = y/r;
        return V;
    }

    inline class Vector2d operator + (const class Vector2d& V) const {
        Vector2d U;
        U.x = x+V.x;
        U.y = y+V.y;
        return U;
    }

    inline class Vector2d operator - (const class Vector2d& V) const {
        Vector2d U;
        U.x = x-V.x;
        U.y = y-V.y;
        return U;
    }

    inline class Vector2d& operator += (const class Vector2d& V) {
        x+=V.x; y+=V.y;
        return *this;
    }

    inline class Vector2d& operator -= (const class Vector2d& V) {
        x-=V.x; y-=V.y;
        return *this;
    }

    inline class Vector2d& operator *= (double r) {
        x*=r; y*=r;
        return *this;
    }

    inline class Vector2d& operator /= (double r) {
        x/=r; y/=r;
        return *this;
    }

    inline bool operator == (const Vector2d& V) const {
        return (x==V.x && y==V.y);
    }

    inline bool operator != (const Vector2d& V) const {
        return !(x==V.x && y==V.y);
    }

    class Vector2d& rotate(double theta);
    class Vector2d& rotate(const trig_pair p);

    void display() const;
    void print() const;
};

Vector2d normalize( const Vector2d& V );


class Vector3d {
public:
    double x,y,z;

    Vector3d() {x=y=z=0.0;}
    Vector3d( double inx, double iny, double inz ) { x = inx; y = iny; z = inz; }
    Vector3d( const Vector2d& V ) { x = V.x; y = V.y; z = 0.0; }
    ~Vector3d() {}


    inline void set( double inx, double iny, double inz ) {
        x = inx; y = iny; z = inz;
    }

    inline double mag() const {
        return (sqrt(x*x+y*y+z*z));
    }

    inline double magSquared() const {
        return (x*x + y*y + z*z);
    }

    inline double dot( const class Vector3d& V ) const {
        return ( x*V.x + y*V.y + z*V.z );
    }

    inline class Vector3d cross( const class Vector3d& V ) const {
        Vector3d retval(    y*V.z - z*V.y,
                            z*V.x - x*V.z,
                            x*V.y - y*V.x );
        return retval;
    }


    class Vector3d projectOnto( const class Vector3d& V ) const;
    class Vector3d reflectAbout( const class Vector3d& V ) const;
    double theta( const Vector3d V ) const;


    Vector2d& operator = (Vector2d& V) {
        x = V.x; y = V.y; z = 0.0;
        return V;
    }

    inline class Vector3d operator - () const{
        Vector3d V( -x,-y,-z );
        return V;
    }

    inline friend class Vector3d operator * (Vector3d V, double r) {
        Vector3d U;
        U.x = V.x*r;
        U.y = V.y*r;
        U.z = V.z*r;
        return U;
    }

    inline friend class Vector3d operator * (double r, Vector3d V) {
        return V*r;
    }

    inline class Vector3d operator / (double r) const {
        Vector3d V(x/r, y/r, z/r);
        return V;
    }

    inline class Vector3d operator + (const class Vector3d& V) const {
        Vector3d U;
        U.x = x+V.x;
        U.y = y+V.y;
        U.z = z+V.z;
        return U;
    }

    inline class Vector3d operator - (const class Vector3d& V) const {
        Vector3d U;
        U.x = x-V.x;
        U.y = y-V.y;
        U.z = z-V.z;
        return U;
    }

    inline class Vector3d& operator += (const class Vector3d& V) {
        x+=V.x; y+=V.y; z+=V.z;
        return *this;
    }

    inline class Vector3d& operator -= (const class Vector3d& V) {
        x-=V.x; y-=V.y; z-=V.z;
        return *this;
    }

    inline class Vector3d& operator *= (double r) {
        x*=r; y*=r; z*=r;
        return *this;
    }

    inline class Vector3d& operator /= (double r) {
        x/=r; y/=r; z/=r;
        return *this;
    }

    inline bool operator == (const Vector3d& V) const {
        return (x==V.x && y==V.y && z==V.z);
    }

    inline bool operator != (const Vector3d& V) const {
        return !(x==V.x && y==V.y && z==V.z);
    }

    void display() const;
    void print() const;
};


Vector3d normalize( const Vector3d& V );



/*An ad hoc matrix class*/

class Matrix3d
{
public:
    double E[3][3];

    Matrix3d()
    {
        E[0][0]=1; E[1][0]=0; E[2][0]=0;
        E[0][1]=0; E[1][1]=1; E[2][1]=0;
        E[0][2]=0; E[1][2]=0; E[2][2]=1;
    }

    Matrix3d(double a, double b, double c,
             double d, double e, double f,
             double g, double h, double i )
    {
        E[0][0]=a; E[1][0]=b; E[2][0]=c;
        E[0][1]=d; E[1][1]=e; E[2][1]=f;
        E[0][2]=g; E[1][2]=h; E[2][2]=i;
    }

    Matrix3d(const Vector3d& u, const Vector3d& v, const Vector3d& w)
    {
        E[0][0]=u.x; E[1][0]=v.x; E[2][0]=w.x;
        E[0][1]=u.y; E[1][1]=v.y; E[2][1]=w.y;
        E[0][2]=u.z; E[1][2]=v.z; E[2][2]=w.z;
    }

    Matrix3d& set(const Vector3d& u, const Vector3d& v, const Vector3d& w)
    {
        E[0][0]=u.x; E[1][0]=v.x; E[2][0]=w.x;
        E[0][1]=u.y; E[1][1]=v.y; E[2][1]=w.y;
        E[0][2]=u.z; E[1][2]=v.z; E[2][2]=w.z;
        return *this;
    }

    Matrix3d& set(  double a, double b, double c,
                    double d, double e, double f,
                    double g, double h, double i  )
    {
        E[0][0]=a; E[1][0]=b; E[2][0]=c;
        E[0][1]=d; E[1][1]=e; E[2][1]=f;
        E[0][2]=g; E[1][2]=h; E[2][2]=i;
        return *this;
    }

    ~Matrix3d(){};


    const bool operator == (const Matrix3d& M) const
    {
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            if( M.E[x][y]!=E[x][y] )
                return false;
        }
        return true;
    }


    class Matrix3d& operator +=(const Matrix3d& M)
    {
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            E[x][y] += M.E[x][y];
        }
        return *this;
    }

    class Matrix3d& operator -=(const Matrix3d& M)
    {
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            E[x][y] -= M.E[x][y];
        }
        return *this;
    }

    class Matrix3d operator -()
    {
        Matrix3d M;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            M.E[x][y] = -E[x][y];
        }
        return M;
    }


    class Matrix3d operator +(const Matrix3d& M) const
    {
        Matrix3d R;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            R.E[x][y] = E[x][y] + M.E[x][y];

        return R;
    }

    class Matrix3d operator -(const Matrix3d& M) const
    {
        Matrix3d R;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            R.E[x][y] = E[x][y] - M.E[x][y];

        return R;
    }

    class Matrix3d operator *=(double k)
    {
        Matrix3d R;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            E[x][y] *= k;

        return R;
    }

    Matrix3d& operator /=(double k)
    {
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            E[x][y] /= k;

        return *this;
    }


    friend class Matrix3d operator * (Matrix3d T, double k)
    {
        Matrix3d R;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            R.E[x][y] = T.E[x][y]*k;

        return R;
    }

    friend class Matrix3d operator * (double k, Matrix3d V)
    {
        return V*k;
    }

    class Matrix3d operator /(double k) const
    {
        Matrix3d R;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            R.E[x][y] = E[x][y]/k;

        return R;
    }


    Vector3d row(int i) const
    {
        return Vector3d( E[0][i], E[1][i], E[2][i] );
    }

    Vector3d column(int i) const
    {
        return Vector3d( E[i][0], E[i][1], E[i][2] );
    }

    Vector3d operator *(const Vector3d& V) const
    {
        return Vector3d(   E[0][0]*V.x + E[1][0]*V.y + E[2][0]*V.z,
                           E[0][1]*V.x + E[1][1]*V.y + E[2][1]*V.z,
                           E[0][2]*V.x + E[1][2]*V.y + E[2][2]*V.z );
    }

    Matrix3d& operator *=( Matrix3d& M )
    {
        Matrix3d B;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            B.E[x][y] = ( row(y) ).dot( M.column(x) );
        }
        (*this) = B;
        return *this;
    }

    class Matrix3d operator *( const Matrix3d& M ) const
    {
        Matrix3d B;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            B.E[x][y] = ( row(y) ).dot( M.column(x) );
        }
        return B;
    }


    double det() const
    {
        return(  E[0][0]*E[1][1]*E[2][2]
                -E[0][0]*E[1][2]*E[2][1]
                +E[0][1]*E[1][2]*E[2][0]
                -E[0][1]*E[1][0]*E[2][2]
                +E[0][2]*E[1][0]*E[2][1]
                -E[0][2]*E[1][1]*E[2][0] );
    }

    class Matrix3d transpose() const
    {
        Matrix3d B;
        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
        {
            B.E[x][y] = E[y][x];
        }
        return B;
    }


    double codet( long x,long y ) const
    {
        static Matrix3d B;
        B = (*this);

        B.E[x][0] = B.E[x][1] = B.E[x][2] = 0;
        B.E[0][y] = B.E[1][y] = B.E[2][y] = 0;
        B.E[x][y] = 1;

        return B.det();
    }


    class Matrix3d inverse() const
    {
        Matrix3d B;

        for(long x=0; x<3; x++)
        for(long y=0; y<3; y++)
            B.E[x][y] = codet(y,x);

        B/=det();

        return B;
    }

    void axisRotation(double theta, const Vector3d& axis)
    {
        Vector3d V(normalize(axis));
        double x=V.x, y=V.y, z=V.z;
        double cost = cos(theta);
        double sint = sin(theta);

        set(cost+(1.0-cost)*x*x,        (1.0-cost)*x*y - sint*z,    (1.0-cost)*x*z + sint*y,
            (1.0-cost)*y*x + sint*z,    cost + (1.0-cost)*y*y,        (1.0-cost)*y*z - sint*x,
            (1.0-cost)*z*x - sint*y,    (1.0-cost)*z*y + sint*x,    cost + (1.0-cost)*z*z);
    }

    void print() const
    {
        printf( "%f, %f, %f\n",E[0][0],E[1][0],E[2][0] );
        printf( "%f, %f, %f\n",E[0][1],E[1][1],E[2][1] );
        printf( "%f, %f, %f\n",E[0][2],E[1][2],E[2][2] );
    }

    void display() const
    {
        print();
        printf( "\n" );
    }
};


} //end namespace

#endif





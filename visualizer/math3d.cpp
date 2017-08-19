#include "math3d.h"
#include <algorithm>

namespace lib3d {

int mymod( int n, int m ) { return ((n%m)+m)%m; }
double squareOf(double t){ return t*t; }
double min( double n, double m ) { return n<m?n:m; }
double max( double n, double m ) { return n<m?m:n; }

Vector2d normalize( const Vector2d& V ) {return V/V.mag();}
Vector3d normalize( const Vector3d& V ) {return V/V.mag();}

trig_pair sin_and_cos(double theta)
{
    trig_pair p;
    p.sin = sin(theta);
    p.cos = cos(theta);
    return p;
}

vector<double> quad_form(double a, double b, double c)
{
    vector<double> R(2);

    double q = -0.5*( b + sgn(b)*sqrt(b*b - 4.0*a*c) );
    R[0] = q/a;
    R[1] = c/q;

    return R;
}


class Vector2d Vector2d::projectOnto( const class Vector2d& V ) const {
    return ( V*dot(V)/V.magSquared() );
}

class Vector2d Vector2d::reflectAbout( const class Vector2d& V ) const {
    return 2*projectOnto(V) - (*this);
}


Vector2d Vector2d::perp() const {
    Vector2d V;
    V.x = y;
    V.y = -x;
    return V;
}

Vector2d Vector2d::right() const {
    return perp();
}

Vector2d Vector2d::left() const {
    Vector2d V;
    return V-perp();
}

double Vector2d::angle() const {
    return atan2(y,x);
}

double Vector2d::theta( const Vector2d V ) const {
    return acos(dot(V)/(mag()*V.mag()));
}

double Vector2d::angleTo( const Vector2d V ) const {
    return theta(V)*sgn( V.y*x-V.x*y );
}

bool Vector2d::between(const Vector2d U, const Vector2d V) const{
    return V.y*x -V.x*y >0 &&  U.x*y -U.y*x>0;
}

bool Vector2d::betweenInclusive(const Vector2d U, const Vector2d V) const{
    return V.y*x -V.x*y >=0 &&  U.x*y -U.y*x>=0;
}

class Vector2d& Vector2d::rotate(double theta) {
    trig_pair p = sin_and_cos(theta);
    return rotate(p);
}

class Vector2d& Vector2d::rotate(const trig_pair p) {
    double new_x, new_y;
    new_x = p.cos*x - p.sin*y;
    new_y = p.sin*x + p.cos*y;
    x = new_x;
    y = new_y;
    return (*this);
}


void Vector2d::display() const {
    printf( "<%f, %f>\n", x, y );
}

void Vector2d::print() const {
    printf( "<%f, %f>", x, y );
}

class Vector3d Vector3d::projectOnto( const class Vector3d& V ) const {
    return ( V*dot(V)/V.magSquared() );
}

class Vector3d Vector3d::reflectAbout( const class Vector3d& V ) const {
    return 2.0*projectOnto(V) - (*this);
}

double Vector3d::theta( const Vector3d V ) const {
    return acos(dot(V)/(mag()*V.mag()));
}

void Vector3d::display() const {
    printf( "<%f, %f, %f>\n", x, y, z );
}

void Vector3d::print() const {
    printf( "<%f, %f, %f>", x, y, z );
}


} //end namespace


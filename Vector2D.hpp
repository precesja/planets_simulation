#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <cmath>

class Vector_2D{
    public:
        double x;
        double y;
    
    Vector_2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector_2D operator+(const Vector_2D &obj) const{
        return Vector_2D(x + obj.x, y + obj.y);
    }

    Vector_2D operator-(const Vector_2D &obj) const{
        return Vector_2D(x - obj.x, y - obj.y);
    }

    Vector_2D operator*(double scalar) const{
        return Vector_2D(x*scalar, y*scalar);
    }
    
    Vector_2D operator/(double scalar) const{
        return Vector_2D(x/scalar, y/scalar);
    }

    double LengthSquared(){
        return x*x + y*y;
    }

    double VectorLength(){
        return std::sqrt(LengthSquared());
    }

    Vector_2D VectorNormalized(){
        return *this / VectorLength();
    }
};
#endif
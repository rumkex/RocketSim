#pragma once

struct Vector3
{
    Vector3(): X(0), Y(0), Z(0)
    {}

    Vector3(const Vector3& other): X(other.X), Y(other.Y), Z(other.Z)
    {}

    Vector3(double x, double y, double z): X(x), Y(y), Z(z)
    {}

    double X, Y, Z;

    Vector3 operator* (double other) const
    {
        return Vector3(X*other, Y*other, Z*other);
    }

    Vector3 operator+ (const Vector3& other) const
    {
        return Vector3(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3 operator- (const Vector3& other) const
    {
        return Vector3(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3 operator- () const
    {
        return Vector3(-X, -Y, -Z);
    }

    double dot(const Vector3& other) const
    {
        return X*other.X + Y*other.Y + Z*other.Z;
    }

    Vector3 cross(const Vector3& other) const
    {
        return Vector3(Y * other.Z - Z * other.Y,
                       Z * other.X - X * other.Z,
                       X * other.Y - Y * other.X);
    }

    double length() const
    {
        return sqrt(lengthSquared());
    }

    double lengthSquared() const
    {
        return X*X + Y*Y + Z*Z;
    }
};

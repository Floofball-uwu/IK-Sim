#include "Vector3.hpp"
#include "Wrappers.hpp"

namespace IkLib {
    Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {
    }

    Vector3::Vector3(const Vector3 &other): x(other.x), y(other.y), z(other.z) {
    }

    float Vector3::length() const {
        return sqrt(x * x + y * y + z * z);
    }

    float Vector3::lengthSquared() const {
        return x * x + y * y + z * z;
    }

    void Vector3::normalize() {
        *this = normalized();
    }

    Vector3 Vector3::normalized() const {
        return *this / length();
    }

    float Vector3::dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }


    Vector3 Vector3::operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator*(float const scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator/(float const scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
}

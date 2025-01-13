#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace IkLib {
    struct Vector3 {
        float x = 0;
        float y = 0;
        float z = 0;

        Vector3() = default;

        Vector3(float x, float y, float z);

        Vector3(const Vector3 &other);

        [[nodiscard]] float length() const;

        [[nodiscard]] float lengthSquared() const;

        void normalize();

        [[nodiscard]] Vector3 normalized() const;

        [[nodiscard]] float dot(const Vector3& other) const;

        [[nodiscard]] Vector3 cross(const Vector3& other) const;

        Vector3 operator+(const Vector3 &other) const;

        Vector3 operator-(const Vector3 &other) const;

        Vector3 operator*(float scalar) const;

        Vector3 operator/(float scalar) const;
    };
}
#endif //VECTOR3_HPP

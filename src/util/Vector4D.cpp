/*
 * Vec4.cpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#include <Vector4D.hpp>

Vector4D::Vector4D() : x(0), y(0), z(0), w(0) {}
Vector4D::Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4D Vector4D::operator+(const Vector4D& other) const {
    return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4D Vector4D::operator-(const Vector4D& other) const {
    return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4D Vector4D::operator*(float scalar) const {
    return Vector4D(x * scalar, y * scalar, z * scalar, w * scalar);
}

float Vector4D::dot(const Vector4D& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4D::norm() const {
    return std::sqrt(dot(*this));
}

Vector4D Vector4D::normalized() const {
    float n = norm();
    return (n > 0.0f) ? (*this * (1.0f / n)) : Vector4D();
}



/*
 * Quaternion.cpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

/*
 * Quaternion.cpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#include "Quaternion.hpp"
#include <cmath>

Quaternion::Quaternion() : vec(0.0f, 0.0f, 0.0f, 1.0f) {}

Quaternion::Quaternion(float w, float x, float y, float z) : vec(x, y, z, w) {}

Quaternion::~Quaternion() {}

Quaternion Quaternion::fromAxisAngle(float ax, float ay, float az, float angle) {
    float s = sin(angle * 0.5f);
    float c = cos(angle * 0.5f);
    return Quaternion(c, ax * s, ay * s, az * s);
}

float Quaternion::normSquared() const {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(vec.w, -vec.x, -vec.y, -vec.z);
}

Quaternion Quaternion::inverse() const {
    return conjugate() * (1.0f / normSquared());
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    float w1 = vec.w, x1 = vec.x, y1 = vec.y, z1 = vec.z;
    float w2 = q.vec.w, x2 = q.vec.x, y2 = q.vec.y, z2 = q.vec.z;

    return Quaternion(
        w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2,
        w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
        w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2,
        w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2
    );
}

Quaternion Quaternion::operator*(float s) const {
    return Quaternion(vec.w * s, vec.x * s, vec.y * s, vec.z * s);
}

float Quaternion::x() const { return vec.x; }
float Quaternion::y() const { return vec.y; }
float Quaternion::z() const { return vec.z; }
float Quaternion::w() const { return vec.w; }

void Quaternion::set(float w, float x, float y, float z) {
    vec = Vector4D(x, y, z, w);
}

Vector4D Quaternion::asVector() const {
    return vec;
}

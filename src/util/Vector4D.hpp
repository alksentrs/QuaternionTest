/*
 * Vec4.hpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#ifndef SRC_BUSINESS_VECTOR4D_HPP_
#define SRC_BUSINESS_VECTOR4D_HPP_

#pragma once
#include <cmath>

class Vector4D {
public:
    float x, y, z, w;

    Vector4D();
    Vector4D(float x, float y, float z, float w);

    Vector4D operator+(const Vector4D& other) const;
    Vector4D operator-(const Vector4D& other) const;
    Vector4D operator*(float scalar) const;

    float dot(const Vector4D& other) const;
    float norm() const;
    Vector4D normalized() const;
};


#endif /* SRC_BUSINESS_VECTOR4D_HPP_ */

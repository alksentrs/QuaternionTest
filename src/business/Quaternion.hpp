/*
 * Quaternion.hpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#ifndef SRC_BUSINESS_QUATERNION_HPP_
#define SRC_BUSINESS_QUATERNION_HPP_

/*
 * Quaternion.hpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#include "Vector4D.hpp"

class Quaternion {
private:
    Vector4D vec;

public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    virtual ~Quaternion();

    static Quaternion fromAxisAngle(float ax, float ay, float az, float angle);

    float normSquared() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;
    void set(float w, float x, float y, float z);
    Vector4D asVector() const;

    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float s) const;

    float w() const;
    float x() const;
    float y() const;
    float z() const;
};

#endif /* SRC_BUSINESS_QUATERNION_HPP_ */

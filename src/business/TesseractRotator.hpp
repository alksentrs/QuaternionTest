/*
 * TesseractRotator.hpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#ifndef SRC_BUSINESS_TESSERACTROTATOR_HPP_
#define SRC_BUSINESS_TESSERACTROTATOR_HPP_

#pragma once

#include "Vector4D.hpp"
#include "Quaternion.hpp"
#include <vector>
#include <utility>
#include <SFML/System/Vector3.hpp>

enum class ProjectionMode {
    PERSPECTIVE,
    SLICE
};

class TesseractRotator {
public:
    std::vector<Vector4D> vertices;
    std::vector<std::pair<int, int>> edges;

    Quaternion q1, q2;

    ProjectionMode mode = ProjectionMode::PERSPECTIVE;
    float sliceW = .0f;

    TesseractRotator();

    void updateRotation(float time);
    Vector4D rotate(const Vector4D& v) const;
    sf::Vector3f projectTo3D(const Vector4D& v, float distance = 5.0f) const;

    void setProjectionMode(ProjectionMode m);
    void setSliceW(float w);

    std::vector<std::pair<sf::Vector3f, sf::Vector3f>> getVisibleSegments3D() const;
    std::vector<sf::Vector3f> getVisiblePoints3D() const;

private:
    bool sliceTo3D(const Vector4D& a, const Vector4D& b, float sliceW, sf::Vector3f& out) const;

};

#endif /* SRC_BUSINESS_TESSERACTROTATOR_HPP_ */

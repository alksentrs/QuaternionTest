/*
 * TesseractRotator.cpp
 *
 *  Created on: 7 de abr. de 2025
 *      Author: aleksander
 */

#include "TesseractRotator.hpp"
#include <iostream>

TesseractRotator::TesseractRotator() {
    vertices = {
        {-1, -1, -1, -1}, {1, -1, -1, -1}, {1, 1, -1, -1}, {-1, 1, -1, -1},
        {-1, -1,  1, -1}, {1, -1,  1, -1}, {1, 1,  1, -1}, {-1, 1,  1, -1},
        {-1, -1, -1,  1}, {1, -1, -1,  1}, {1, 1, -1,  1}, {-1, 1, -1,  1},
        {-1, -1,  1,  1}, {1, -1,  1,  1}, {1, 1,  1,  1}, {-1, 1,  1,  1}
    };

    edges = {
        {0,1},{1,2},{2,3},{3,0}, {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}, {8,9},{9,10},{10,11},{11,8},
        {12,13},{13,14},{14,15},{15,12}, {8,12},{9,13},{10,14},{11,15},
        {0,8},{1,9},{2,10},{3,11}, {4,12},{5,13},{6,14},{7,15}
    };

    q1 = Quaternion(1, 0, 0, 0);
    q2 = Quaternion(1, 0, 0, 0);
}

void TesseractRotator::updateRotation(float time) {
    q1 = Quaternion::fromAxisAngle(1, 0, 0, time * 0.5f);
    q2 = Quaternion::fromAxisAngle(0, 1, 0, time * 0.7f);
}

Vector4D TesseractRotator::rotate(const Vector4D& v) const {
    Quaternion p(v.w, v.x, v.y, v.z);
    Quaternion r = q1 * p * q2.conjugate();
    return Vector4D(r.x(), r.y(), r.z(), r.w());
}

sf::Vector3f TesseractRotator::projectTo3D(const Vector4D& v, float distance) const {
    float w = 1.0f / (distance - v.w);
    return sf::Vector3f(v.x * w, v.y * w, v.z * w);
}

bool TesseractRotator::sliceTo3D(const Vector4D& a, const Vector4D& b, float sliceW, sf::Vector3f& outPoint) const {
    float w1 = a.w;
    float w2 = b.w;

    // Verifica se há interseção com o plano w = sliceW
    if ((w1 - sliceW) * (w2 - sliceW) >= 0.0f) {
        return false; // ambos do mesmo lado ou em cima do plano
    }

    // Interpolação linear do ponto de corte
    float t = (sliceW - w1) / (w2 - w1);
    Vector4D point = a + (b - a) * t;

    // Projeta para 3D (desconsidera w, já está cortado)
    outPoint = sf::Vector3f(point.x, point.y, point.z);
    return true;
}

void TesseractRotator::setProjectionMode(ProjectionMode m) {
    mode = m;
}

void TesseractRotator::setSliceW(float w) {
    sliceW = w;
}

std::vector<std::pair<sf::Vector3f, sf::Vector3f>> TesseractRotator::getVisibleSegments3D() const {
    std::vector<std::pair<sf::Vector3f, sf::Vector3f>> result;

    for (const auto& edge : edges) {
        Vector4D v1 = rotate(vertices[edge.first]);
        Vector4D v2 = rotate(vertices[edge.second]);

        //std::cout << "w1 = " << v1.w << ", w2 = " << v2.w << std::endl;

        if (mode == ProjectionMode::PERSPECTIVE) {
            sf::Vector3f p1 = projectTo3D(v1);
            sf::Vector3f p2 = projectTo3D(v2);
            result.emplace_back(p1, p2);
        } else if (mode == ProjectionMode::SLICE) {
            float d1 = v1.w - sliceW;
            float d2 = v2.w - sliceW;

            float thickness = .05f; // ajustável

            if (std::abs(d1) < thickness && std::abs(d2) < thickness) {
                sf::Vector3f p1(v1.x, v1.y, v1.z);
                sf::Vector3f p2(v2.x, v2.y, v2.z);
                result.emplace_back(p1, p2);
            }

            if (d1*d2 < 0.0f) {
                float t = (sliceW - v1.w) / (v2.w - v1.w);
                Vector4D p = v1 + (v2 - v1) * t;
                sf::Vector3f p3D(p.x, p.y, p.z);
                // guarde os pontos cortados
            }

        }
    }

    return result;
}

std::vector<sf::Vector3f> TesseractRotator::getVisiblePoints3D() const {
    std::vector<sf::Vector3f> result;
    if (mode == ProjectionMode::SLICE) {

    	for (const auto& edge : edges) {
    		Vector4D v1 = rotate(vertices[edge.first]);
    		Vector4D v2 = rotate(vertices[edge.second]);

            float d1 = sliceW - v1.w;
            float d2 = sliceW - v2.w;

            if ( d1 * d2 < 0.0f ) {
                float t = d1 / (v2.w - v1.w);
                Vector4D p = v1 + (v2 - v1) * t;
                sf::Vector3f p3D(p.x, p.y, p.z);
                result.emplace_back(p3D);
            }
        }
    }
    return result;
}





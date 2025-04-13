/*
 * ConvexHullBuilder.cpp
 *
 *  Created on: 11 de abr. de 2025
 *      Author: aleksander
 */

#include "ConvexHullBuilder.hpp"
#include "quickhull/QuickHull.hpp"  // Ajuste para seu path do QuickHull
#include <unordered_set>
#include <functional>
#include <cmath>

using namespace std;

namespace {

std::pair<sf::Vector3f, sf::Vector3f> make_sorted_edge(const sf::Vector3f& a, const sf::Vector3f& b) {
    if (a.x != b.x) return (a.x < b.x) ? std::make_pair(a, b) : std::make_pair(b, a);
    if (a.y != b.y) return (a.y < b.y) ? std::make_pair(a, b) : std::make_pair(b, a);
    return (a.z < b.z) ? std::make_pair(a, b) : std::make_pair(b, a);
}

bool equalVec3f(const sf::Vector3f& a, const sf::Vector3f& b, float eps = 1e-5f) {
    return std::abs(a.x - b.x) < eps && std::abs(a.y - b.y) < eps && std::abs(a.z - b.z) < eps;
}

struct EdgeHash {
    size_t operator()(const std::pair<sf::Vector3f, sf::Vector3f>& edge) const {
        auto h1 = std::hash<float>()(edge.first.x) ^ std::hash<float>()(edge.first.y) ^ std::hash<float>()(edge.first.z);
        auto h2 = std::hash<float>()(edge.second.x) ^ std::hash<float>()(edge.second.y) ^ std::hash<float>()(edge.second.z);
        return h1 ^ h2;
    }
};

struct EdgeEqual {
    bool operator()(const std::pair<sf::Vector3f, sf::Vector3f>& e1, const std::pair<sf::Vector3f, sf::Vector3f>& e2) const {
        return (equalVec3f(e1.first, e2.first) && equalVec3f(e1.second, e2.second)) ||
               (equalVec3f(e1.first, e2.second) && equalVec3f(e1.second, e2.first));
    }
};

} // namespace

std::vector<ConvexHullBuilder::Triangle> ConvexHullBuilder::compute(const std::vector<sf::Vector3f>& points) const {
    std::vector<quickhull::Vector3<float>> qhPoints;
    qhPoints.reserve(points.size());

    for (const auto& p : points)
        qhPoints.emplace_back(p.x, p.y, p.z);

    quickhull::QuickHull<float> qh;
    const auto hull = qh.getConvexHull(qhPoints, true, true, 1e-6f);

    const auto& vertices = hull.getVertexBuffer();
    const auto& indexBuffer = hull.getIndexBuffer();

    std::vector<Triangle> triangles;
    for (size_t i = 0; i + 2 < indexBuffer.size(); i += 3) {
        Triangle tri;
        for (int j = 0; j < 3; ++j) {
            const auto& v = vertices[indexBuffer[i + j]];
            tri[j] = sf::Vector3f(v.x, v.y, v.z);
        }
        triangles.push_back(tri);
    }

    return triangles;
}

std::vector<ConvexHullBuilder::Edge> ConvexHullBuilder::extractEdges(const std::vector<Triangle>& triangles) const {
    std::unordered_set<Edge, EdgeHash, EdgeEqual> uniqueEdges;

    for (const auto& tri : triangles) {
        uniqueEdges.insert(make_sorted_edge(tri[0], tri[1]));
        uniqueEdges.insert(make_sorted_edge(tri[1], tri[2]));
        uniqueEdges.insert(make_sorted_edge(tri[2], tri[0]));
    }

    return std::vector<Edge>(uniqueEdges.begin(), uniqueEdges.end());
}


/*
 * ConvexHullBuilder.h
 *
 *  Created on: 11 de abr. de 2025
 *      Author: aleksander
 */

#ifndef SRC_BUSINESS_CONVEXHULLBUILDER_HPP_
#define SRC_BUSINESS_CONVEXHULLBUILDER_HPP_

#pragma once

#include <SFML/System/Vector3.hpp>
#include <vector>
#include <array>
#include <utility>

class ConvexHullBuilder {
public:
    using Triangle = std::array<sf::Vector3f, 3>;
    using Edge = std::pair<sf::Vector3f, sf::Vector3f>;

    std::vector<Triangle> compute(const std::vector<sf::Vector3f>& points) const;
    std::vector<Edge> extractEdges(const std::vector<Triangle>& triangles) const;
};


#endif /* SRC_BUSINESS_CONVEXHULLBUILDER_HPP_ */

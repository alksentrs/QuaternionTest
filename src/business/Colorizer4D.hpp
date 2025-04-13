/*
 * Colorizer4D.hpp
 *
 *  Created on: 8 de abr. de 2025
 *      Author: aleksander
 */

#ifndef SRC_BUSINESS_COLORIZER4D_HPP_
#define SRC_BUSINESS_COLORIZER4D_HPP_

#pragma once

#include <SFML/Graphics/Color.hpp>

enum class ColorMode {
    W_DEPTH,
    Z_DEPTH
};

class Colorizer4D {
public:
    ColorMode mode = ColorMode::W_DEPTH;

    // Define os limites para normalização
    float minW = -1.0f;
    float maxW =  1.0f;
    float minZ = -1.5f;
    float maxZ =  1.5f;

    void setMode(ColorMode newMode) {
        mode = newMode;
    }

    void setWRange(float minVal, float maxVal) {
        minW = minVal;
        maxW = maxVal;
    }

    void setZRange(float minVal, float maxVal) {
        minZ = minVal;
        maxZ = maxVal;
    }

    // Retorna cor RGB entre 0 e 1 (OpenGL friendly)
    void getColor(float w, float z, float& r, float& g, float& b) const {
        if (mode == ColorMode::W_DEPTH) {
            float t = (w - minW) / (maxW - minW);
            t = std::clamp(t, 0.0f, 1.0f);
            r = 1.0f - t;
            g = 0.0f;
            b = t;
        } else { // Z_DEPTH
            float t = (z - minZ) / (maxZ - minZ);
            t = std::clamp(t, 0.0f, 1.0f);
            r = t;
            g = t;
            b = 1.0f - t;
        }
    }
};


#endif /* SRC_BUSINESS_COLORIZER4D_HPP_ */

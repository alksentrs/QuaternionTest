/*
 * Sketch.hpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Sketch.hpp
#ifndef BUSINESS_SKETCH_HPP_
#define BUSINESS_SKETCH_HPP_

#include <vector>
#include <utility>
#include <unordered_set>
#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/ILogic.hpp"
#include "util/Vector2D.hpp"
#include "TesseractRotator.hpp"
#include "Colorizer4D.hpp"

class Sketch : public ILogic {
public:
	Sketch();
	virtual ~Sketch();
	void init(sf::RenderWindow& window) override;
	void input(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
	const char* getWindowName() const override;
	int getWidth() const override;
	int getHeight() const override;

private:
	const char* windowName = "Quaternion Test";
	int windowWidth = 800;
	int windowHeight = 600;

	float timeAccumulator = 0.0f;
	TesseractRotator tesseract;
	Colorizer4D colorizer;

	float normalizeZ(float z, float minZ = -1.5f, float maxZ = 1.5f);
	float normalizeW(float w, float minW = -1.0f, float maxW = 1.0f);
};

#endif /* BUSINESS_SKETCH_HPP_ */

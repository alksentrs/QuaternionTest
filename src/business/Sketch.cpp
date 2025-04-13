/*
 * Sketch.cpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Sketch.cpp
#include "Sketch.hpp"
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include "ConvexHullBuilder.hpp"

Sketch::Sketch() {

}

void Sketch::init(sf::RenderWindow& window) {
	window.setActive(true);

    glEnable(GL_DEPTH_TEST);

    // Set viewport to match window size
    glViewport(0, 0, windowWidth, windowHeight);

    // Set background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);

    // Set projection ONCE
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, (float)windowWidth / windowHeight, 0.1f, 100.f);

    // Leave modelview selected
    glMatrixMode(GL_MODELVIEW);

    GLfloat matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, matrix);
    std::cout << "Projection matrix: ";
    for (int i = 0; i < 16; ++i) std::cout << matrix[i] << ' ';
    std::cout << std::endl;
}


void Sketch::input(const sf::Event& event, sf::RenderWindow& window) {
	(void)event;
	(void)window;

    if (event.type == sf::Event::KeyPressed) {
    	if (event.key.code == sf::Keyboard::W) {
    		colorizer.setMode(ColorMode::W_DEPTH);
	    } else if (event.key.code == sf::Keyboard::Z) {
	        colorizer.setMode(ColorMode::Z_DEPTH);
	    } else if (event.key.code == sf::Keyboard::P) {
            tesseract.setProjectionMode(ProjectionMode::PERSPECTIVE);
        } else if (event.key.code == sf::Keyboard::S) {
            tesseract.setProjectionMode(ProjectionMode::SLICE);
        } else if (event.key.code == sf::Keyboard::Up) {
            tesseract.setSliceW(tesseract.sliceW + 0.05f);
            std::cout << "sliceW = " << tesseract.sliceW << std::endl;
        } else if (event.key.code == sf::Keyboard::Down) {
            tesseract.setSliceW(tesseract.sliceW - 0.05f);
            std::cout << "sliceW = " << tesseract.sliceW << std::endl;
        }
    }
}

void Sketch::update(float dt) {
	timeAccumulator += dt;                // acumula o tempo
	    tesseract.updateRotation(timeAccumulator);  // passa tempo total
}

float Sketch::normalizeZ(float z, float minZ, float maxZ) {
    return (z - minZ) / (maxZ - minZ);
}

float Sketch::normalizeW(float w, float minW, float maxW) {
    return (w - minW) / (maxW - minW); // normaliza para 0~1
}

void Sketch::draw(sf::RenderWindow& window) {
	(void)window;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();                      // ModelView reset
    glTranslatef(0.f, 0.f, -5.f);          // Pull cube back

    glBegin(GL_LINES);
    for (const auto& segment : tesseract.getVisibleSegments3D()) {
        const auto& [p1, p2] = segment;
        glColor3f(1.0f, 1.0f, 1.0f); // cor padrão (pode usar Colorizer4D também)
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();

    const auto& points = tesseract.getVisiblePoints3D();

    ConvexHullBuilder convexHullBuilder;
    auto triangles = convexHullBuilder.compute(points);
    auto edges = convexHullBuilder.extractEdges(triangles);

    glColor3f(1.0f, 1.0f, 0.0f); // amarelo
    glBegin(GL_LINES);
    for (auto& [a, b] : edges) {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
    }
    glEnd();

    /*glBegin(GL_LINES);
    glColor3f(0, 0, 1); //azul
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            glVertex3f(points[i].x, points[i].y, points[i].z);
            glVertex3f(points[j].x, points[j].y, points[j].z);
        }
    }
    glEnd();*/
}



const char* Sketch::getWindowName() const {
	return windowName;
}

int Sketch::getWidth() const {
	return windowWidth;
}

int Sketch::getHeight() const {
	return windowHeight;
}

Sketch::~Sketch() {
}

/*
 * Engine.cpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Engine.cpp
#include "Engine.hpp"
#include <chrono>
#include <thread>

Engine::Engine(ILogic* logic, int fps, int ups, bool sync)
    : logic(logic), targetFPS(fps), targetUPS(ups), syncEnabled(sync), running(true) {}

void Engine::run() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // ✅ Critical for 3D rendering
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 2;
	settings.minorVersion = 1;

	sf::RenderWindow window(
			sf::VideoMode(logic->getWidth(), logic->getHeight()),
			logic->getWindowName(),
			sf::Style::Default,
			settings
	);
	logic->init(window);
	loop(window);
}

void Engine::stop() {
    running = false;
}

void Engine::loop(sf::RenderWindow& window) {
    sf::Clock clock;
    float interval = 1.0f / targetUPS;
    float accumulator = 0.0f;

    while (running && window.isOpen()) {
        float frameStartTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
                window.close();
            }
            logic->input(event, window);
        }

        accumulator += frameStartTime;

        while (accumulator >= interval) {
            logic->update(interval);
            accumulator -= interval;
        }

        //window.clear();
        logic->draw(window);
        window.display();

        if (syncEnabled) sync(frameStartTime);
    }
}

void Engine::sync(float frameStartTime) {
    float frameDuration = 1.0f / targetFPS;
    float sleepTime = frameDuration - frameStartTime;
    if (sleepTime > 0) {
        std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
    }
}



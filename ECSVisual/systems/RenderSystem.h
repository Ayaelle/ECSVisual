#pragma once

#include "../ecs/ECS.h"
#include "../components/Position.h"
#include "../components/Color.h"
#include <SFML/Graphics.hpp>

class RenderSystem {
public:
	void update(ECS& ecs, sf::RenderWindow& window) {
		for (Entity entity = 0; entity < 5000; entity++) {
			if (!ecs.isAlive(entity)) continue;

			try {
				Position& pos = ecs.getComponent<Position>(entity);
				Color& col = ecs.getComponent<Color>(entity);

				sf::RectangleShape rect({ 10.f, 10.f });
				rect.setFillColor(col.value);
				rect.setPosition(sf::Vector2f{ pos.x, pos.y });
				window.draw(rect);

			}
			catch (...) {
				// Entité non conernée : ignore
			}
		}
	}
};
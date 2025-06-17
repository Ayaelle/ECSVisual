#pragma once

#include "../ecs/ECS.h"
#include "../components/Position.h"
#include "../components/Size.h"
#include "../components/PlayerControlled.h"
#include <SFML/Graphics/Rect.hpp>

class CollisionSystem {
public:
	void update(ECS& ecs) {
		Entity player = findPlayer(ecs);
		if (player == INVALID_ENTITY) return;

		Position& playerPos = ecs.getComponent<Position>(player);
		Size& playerSize = ecs.getComponent<Size>(player);

		sf::FloatRect playerRect({ playerPos.x, playerPos.y }, { playerSize.width, playerSize.height });

		for (Entity other = 0; other < 5000; other++) {
			if (!ecs.isAlive(other) || other == player) continue;

			try {
				Position& pos = ecs.getComponent<Position>(other);
				Size& size = ecs.getComponent<Size>(other);

				sf::FloatRect otherRect({ pos.x, pos.y }, { size.width, size.height });
				sf::FloatRect intersection;


				//Test de corection du if (playerRect.findIntersection(otherRect))
				if (playerRect.findIntersection(otherRect)) {
					playerPos.x -= playerLastVel.vx;
					playerPos.y -= playerLastVel.vy;
				}

			}
			catch (...) {
				continue;
			}
		}
	}

	void setPlayerVelocity(float vx, float vy) {
		playerLastVel.vx = vx;
		playerLastVel.vy = vy;
	}

private:
	struct VelocitySnapshot { float vx = 0.f, vy = 0.f; } playerLastVel;

	Entity findPlayer(ECS& ecs) {
		for (Entity e = 0; e < 5000; e++) {
			if (!ecs.isAlive(e)) continue;
			try {
				ecs.getComponent<PlayerControlled>(e);
				return e;
			}
			catch (...) {}
		}
		return INVALID_ENTITY;
	}

	static constexpr Entity INVALID_ENTITY = 5001;
};
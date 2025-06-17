#pragma once

#include "../ecs/ECS.h"
#include "../components/Position.h"
#include "../components/Velocity.h"

class MovementSystem {
public:
	void update(ECS& ecs, float screenWidth, float screenHeight) {
		for (Entity entity = 0; entity < 5000; entity++) {
			if (!ecs.isAlive(entity)) continue;

			try {
				Position& pos = ecs.getComponent<Position>(entity);
				Velocity& vel = ecs.getComponent<Velocity>(entity);

				pos.x += vel.vx;
				pos.y += vel.vy;

				//rebond sur les bords
				if (pos.x < 0.f || pos.x > screenWidth - 10.f) {
					vel.vx = -vel.vx;
					pos.x = std::max(0.f, std::min(pos.x, screenWidth - 10.f));
				}
				if (pos.y < 0.f || pos.y > screenHeight - 10.f) {
					vel.vy = -vel.vy;
					pos.y = std::max(0.f, std::min(pos.y, screenHeight - 10.f));
				}
			}
			catch (...) {
				// Si l'entité n'a pas de Position ou Velocity, on ignore
			}
		}
	}
};
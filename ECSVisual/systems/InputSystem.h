#pragma once

#include "../ecs/ECS.h"
#include "../components/PlayerControlled.h"
#include "../components/Velocity.h"
#include <SFML/Window/Keyboard.hpp>
#include <string>

struct KeyMapping {
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
};

class InputSystem {
public:
	InputSystem(const KeyMapping& keys) : mapping(keys) {}

	void update(ECS& ecs) {
		for (Entity entity = 0; entity < 5000; entity++) {
			if (!ecs.isAlive(entity)) continue;

			try {
				ecs.getComponent<PlayerControlled>(entity);	//Test de la présence de l'entité controllée par le jouer
				Velocity& vel = ecs.getComponent<Velocity>(entity);

				vel.vx = 0.f;
				vel.vy = 0.f;

				if (sf::Keyboard::isKeyPressed(mapping.left)) vel.vx = -2.f;					
				if (sf::Keyboard::isKeyPressed(mapping.right)) vel.vx = 2.f;					
				if (sf::Keyboard::isKeyPressed(mapping.up)) vel.vy = -2.f;					
				if (sf::Keyboard::isKeyPressed(mapping.down)) vel.vy = 2.f;
					

			} catch (...) {
				//Non joueur ou sans velocity > ignore
			}
		}
	}

private:
	KeyMapping mapping;
};
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ecs/ECS.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Color.h"
#include "components/PlayerControlled.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"
#include "systems/InputSystem.h"
#include "systems/CollisionSystem.h"
#include "utils/KeyboardConfig.h"
#include <random>
#include <iostream>
#include <string>

int main()
{
	constexpr unsigned int screenWidth = 800;
	constexpr unsigned int screenHeight = 600;

	sf::RenderWindow window(sf::VideoMode({ screenWidth, screenHeight }), "Mini ECS - SFML 3.0");
	window.setFramerateLimit(60);

	ECS ecs;
	MovementSystem movementSystem;
	RenderSystem renderSystem;

	std::string layout = getKeyboardLayout();
	KeyMapping mapping;

	if (layout == "AZERTY") {
		mapping = { sf::Keyboard::Key::Z, sf::Keyboard::Key::S, sf::Keyboard::Key::Q, sf::Keyboard::Key::D };
	}
	else {
		mapping = { sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D };
	}

	InputSystem inputSystem(mapping);
	CollisionSystem collisionSystem;

	//Création de l'entité joueur
	Entity player = ecs.createEntity();
	ecs.addComponent<Position>(player, {400.f, 300.f});
	ecs.addComponent<Velocity>(player, {0.f, 0.f});
	ecs.addComponent<Color>(player, { sf::Color::White });
	ecs.addComponent<Size>(player, { 10.f, 10.f });
	ecs.addComponent<PlayerControlled>(player, {});


	//Générateur aléatoire pour positions, vitesses, couleurs
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> posX(0.f, screenWidth - 10.f);
	std::uniform_real_distribution<float> posY(0.f, screenHeight - 10.f);
	std::uniform_real_distribution<float> speed(-1.f, -1.f);
	std::uniform_int_distribution<int> color(0, 255);

	//Création d'entités
	for (int i = 0; i < 50; i++) {
		Entity e = ecs.createEntity();
		ecs.addComponent<Position>(e, { posX(rng), posY(rng) });
		ecs.addComponent<Velocity>(e, { speed(rng), speed(rng) });
		ecs.addComponent<Color>(e, { sf::Color(color(rng), color(rng), color(rng)) });
		ecs.addComponent<Size>(e, { 10.f, 10.f });
	}

	//Boucle principale	
	while (window.isOpen()) {	
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>() || (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
				window.close();
			}
		}

		inputSystem.update(ecs);
		collisionSystem.setPlayerVelocity(ecs.getComponent<Velocity>(player).vx, ecs.getComponent<Velocity>(player).vy);
		movementSystem.update(ecs, screenWidth, screenHeight);
		collisionSystem.update(ecs);

		window.clear(sf::Color::Black);
		renderSystem.update(ecs, window);
		window.display();
	}

	return 0;
}
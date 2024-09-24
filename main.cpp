#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "UI.h"
int main() {
	Board board;
	sf::Vector2i posMouse;
	bool pressed = false;
	UI ui;

	// Jaque States
	bool jW, jB, jMW, jMB;

	// Window
	sf::RenderWindow window(sf::VideoMode(504, 524), "Chess Game - Canavesi Games", sf::Style::Titlebar | sf::Style::Close);

	// Set the window's size to a fixed value (504, 524) 
    window.setSize(sf::Vector2u(504, 524));
    
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			posMouse = sf::Mouse::getPosition(window);

			// Mouse events handling
			if (event.type == sf::Event::MouseButtonPressed) pressed = true;
			if (event.type == sf::Event::MouseButtonReleased) pressed = false;
		}

		// Update board
		board.Update(posMouse.x, posMouse.y, pressed);

		// Consult Jaque
		board.ConsultJaque(jW, jB, jMW, jMB);

		// Update information about the turn
		ui.Update(board.ConsultTurn());

		// Update information about the Jaque
		if (jW) ui.Jaque(true);
		if (jB) ui.Jaque(false);
		if (jMW) ui.JaqueMate(true);
		if (jMB) ui.JaqueMate(false);

		// Clear window to redisplaying the drawable objects
		window.clear();

		// Draw drawables
		window.draw(board);
		window.draw(ui);

		// Display
		window.display();
	}
	return 0;
}
#include "UI.h"

UI::UI() {

	// Load fonts
	if (!font.loadFromFile("resources/antology/Antology.ttf")) {
		std::cout << "Error loading font\n";
	}
	text.setFont(font);
	text.setCharacterSize(40);
	text.setPosition(252, 490);
	text.setString("");
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setFillColor(sf::Color(0, 0, 0));
}

// Update turn
void UI::Update(bool color) {
	if (jaqueTime == 0) {
		text.setString((std::string)"Turno de " + (std::string)(color ? "Blancas" : "Negras"));
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
	else if (jaqueTime > 0) {
		jaqueTime--;
	}
}

// Update Jaque
void UI::Jaque(bool color) {
	jaqueTime = 100;
	if (!color) {
		text.setString("Jaque para Negras");
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
	else {
		text.setString("Jaque para Blancas");
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
}

// Update Jaque Mate
void UI::JaqueMate(bool color) {
	jaqueTime = -100;
	if (!color) {
		text.setString("Jaque Mate para Negras");
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
	else {
		text.setString("Jaque Mate para Blancas");
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
}

// Drawing
void UI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(text, rs);
}
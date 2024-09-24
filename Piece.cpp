#include "Piece.h"

Piece::Piece(sf::Texture& texture, int x, int y, int val) {

	// Texture
	sprite.setTexture(texture);

	// Value
	// 0 - Empty, Positive - White, Negative - Black
	// 1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen, 5 - King, 6 - Pawn
	value = val;

	// Assing the appropiate section of the tuxture, depending of the type of the piece
	if (value < 0) sprite.setTextureRect(sf::IntRect(56 * (abs(value) - 1), 0, 56, 56));
	else sprite.setTextureRect(sf::IntRect(56 * (abs(value) - 1), 56, 56, 56));

	// Locate piece in board
	sprite.setPosition(x, y);
	sprite.setOrigin(56 / 2, 56 / 2);
}

sf::Vector2f Piece::GetPosition() {
	return sprite.getPosition();
}

void Piece::SetPosition(int x, int y) {
	sprite.setPosition(x, y);
}

int Piece::GetValue() {
	return value;
}

// The position of the mouse, contain the current piece?
bool Piece::ContainPosition(int x, int y) {
	int szX = sprite.getPosition().x;
	int szY = sprite.getPosition().y;
	sf::IntRect rect = sf::IntRect(szX - 28 + 3, szY - 28 + 3, 50, 50);
	return rect.contains(x, y);
}

// Draw piece with SFML library
void Piece::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(sprite, rs);
}
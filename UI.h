#include <iostream>
#include <SFML/Graphics.hpp>

class UI : public sf::Drawable {
private:
	sf::Font font;
	sf::Text text;
	int jaqueTime = 0;
public:
	UI();
	void Update(bool);
	void Jaque(bool);
	void JaqueMate(bool);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};
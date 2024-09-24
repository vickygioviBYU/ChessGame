#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Piece.h"

class Board : public sf::Drawable {
private:
	sf::Texture texture, pTexture;
	std::vector<std::vector<int>> desc;
	std::vector<Piece> piece;
	sf::Sprite board;
	int pInd = -1, pI, pJ;
	bool color = true, jaqW = false, jaqMW = false, jaqB = false, jaqMB = false;
	void TakePiece(int, int);
	void DropPiece(int, int);
	bool CheckPeon(int, int);
	bool CheckRey(int, int);
	bool CheckCaballo(int, int);
	bool CheckTorre(int, int);
	bool CheckAlfil(int, int);
	bool CheckReina(int, int);
	bool CheckMove(int, int);
	void CheckJaque();
public:
	Board();
	void Update(int, int, bool);
	void ConsultJaque(bool&, bool&, bool&, bool&);
	bool ConsultTurn();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};
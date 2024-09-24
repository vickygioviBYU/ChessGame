#include "Board.h"

Board::Board() {

	// Load texture board
	if (!texture.loadFromFile("resources/board1.png"))	std::cout << "Error loading Texture\n";

	board.setTexture(texture);
	board.setPosition(0, 0);

	// Load texture piece
	if (!pTexture.loadFromFile("resources/pieces.png")) std::cout << "Error loading Texture\n";

	// 0 - Empty, Positive - White, Negative - Black
	// 1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen, 5 - King, 6 - Pawn
	desc = { {-1,-2,-3,-4,-5,-3,-2,-1},
					{-6,-6,-6,-6,-6,-6,-6,-6},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{6, 6, 6, 6, 6, 6, 6, 6},
					{1, 2, 3, 4, 5, 3, 2, 1} };

	// Iterate in the board, and push back the pieces into the pieces array
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (desc[i][j] != 0) {
				Piece p(pTexture, 56 + j * 56, 56 + i * 56, desc[i][j]);
				piece.push_back(p);
			}
		}
	}
}

// Event to take the piece (if the piece is clicked)
void Board::TakePiece(int x, int y) {
	for (int h = 0; h < (int)piece.size(); h++) {
		if (piece[h].ContainPosition(x, y)) {
			pInd = h;
			break;
		}
	}

	// Verify the turn (if the piece selected don't correspond to the turn)
	if (color && piece[pInd].GetValue() < 0) pInd = -1;
	else if (!color && piece[pInd].GetValue() > 0) pInd = -1;

	// What position in the matrix correspond to the mouse position
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sf::IntRect rect = sf::IntRect(28 + 3 + j * 56, 28 + 3 + i * 56, 50, 50);
			if (rect.contains(x, y))	pI = i, pJ = j;
		}
	}
}

// Method to drop the piece
void Board::DropPiece(int x, int y) {
	bool flag = 1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			// What position in the matrix correspond to the mouse position
			sf::IntRect rect = sf::IntRect(28 + j * 56 + 3, 28 + i * 56 + 3, 50, 50);

			// Target position have to be an empty position (0), or contain a piece of the contrary color
			// Check if the move is valid
			if (rect.contains(x, y) && ((color && desc[i][j] <= 0) || (!color && desc[i][j] >= 0)) && CheckMove(i, j)) {

				// Asign position to the piece
				piece[pInd].SetPosition(56 + j * 56, 56 + i * 56);

				// Move piece
				desc[i][j] = desc[pI][pJ];
				desc[pI][pJ] = 0;
				flag = 0;

				// Part to check eating pieces
				for (int h = 0; h < (int)piece.size(); h++) {
					int val = piece[h].GetValue();
					if (piece[h].ContainPosition(x, y) && ((color && val < 0) || (!color && val > 0)))
						piece.erase(piece.begin() + h);
				}

				// Part to check Jaque and Jaque Mate
				CheckJaque();

				// Swap turn
				if (color) color = false;
				else color = true;
			}
		}
	}

	// Part executed if the target of the piece is invalid
	if (flag) piece[pInd].SetPosition(56 + pJ * 56, 56 + pI * 56);
	pInd = -1;
}

// Handling mouse events corresponding to pieces
void Board::Update(int x, int y, bool pressed) {
	CheckJaque();
	if (pInd != -1 && pressed) {
		piece[pInd].SetPosition(x, y);
	}
	else if (pInd != -1 && !pressed) {
		DropPiece(x, y);
	}
	else if (pInd == -1 && pressed) {
		TakePiece(x, y);
	}
}

// Pawn:
// Pawn black or white
// Two squares up or down, one square up or down, or 1 up or down, and 1 left, or 1 right
bool Board::CheckPeon(int i, int j) {
	if (color) {
		if (desc[i][j] == 0 && pI - i == 1 && j == pJ) return true;
		else if (desc[i][j] == 0 && pI - i == 2 && j == pJ && pI == 6 && desc[i + 1][j] == 0) return true;
		else if (desc[i][j] < 0 && pI - i == 1 && abs(j - pJ) == 1) return true;
	}
	else {
		if (desc[i][j] == 0 && pI - i == -1 && j == pJ) return true;
		else if (desc[i][j] == 0 && pI - i == -2 && j == pJ && pI == 1 && desc[i - 1][j] == 0) return true;
		else if (desc[i][j] > 0 && pI - i == -1 && abs(j - pJ) == 1) return true;
	}

	return false;
}

// King
// Around squares, up, down, left, right, up and left, up and right, down and left, down and right
bool Board::CheckRey(int i, int j) {
	if (color) {
		if (abs(pI - i) <= 1 && abs(pJ - j) <= 1 && desc[i][j] <= 0) return true;
	}
	else {
		if (abs(pI - i) <= 1 && abs(pJ - j) <= 1 && desc[i][j] >= 0) return true;
	}

	return false;
}

// Knight
// Two squares in an axis, and one square in the other axis
bool Board::CheckCaballo(int i, int j) {
	if (color) {
		if (((abs(pI - i) == 2 && abs(pJ - j) == 1) || (abs(pI - i) == 1 && abs(pJ - j) == 2)) && desc[i][j] <= 0) return true;
	}
	else {
		if (((abs(pI - i) == 2 && abs(pJ - j) == 1) || (abs(pI - i) == 1 && abs(pJ - j) == 2)) && desc[i][j] >= 0) return true;
	}

	return false;
}

// Rook
// Scrolling in a single axis
bool Board::CheckTorre(int i, int j) {
	if (pJ == j) {
		for (int I = std::min(pI, i) + 1; I < std::max(pI, i); I++) {
			if (desc[I][pJ] != 0) return false;
		}

		if (color && desc[i][j] <= 0) return true;
		else if (!color && desc[i][j] >= 0) return true;

	}
	else if (pI == i) {
		for (int J = std::min(pJ, j) + 1; J < std::max(pJ, j); J++) {
			if (desc[pI][J] != 0) return false;
		}

		if (color && desc[i][j] <= 0) return true;
		else if (!color && desc[i][j] >= 0) return true;

	}

	return false;
}

// Bishop
// Scrolling x quantity of squares in an axis, and x quantity in another axis
bool Board::CheckAlfil(int i, int j) {
	if (abs(pJ - j) == abs(pI - i)) {

		int difI = (pI - i < 0 ? 1 : -1);
		int difJ = (pJ - j < 0 ? 1 : -1);

		int I = pI;
		int J = pJ;

		while (I != i - difI && J != j - difJ) {
			I += difI;
			J += difJ;
			if (desc[I][J] != 0) return false;
		}

		if (color && desc[i][j] <= 0) return true;
		else if (!color && desc[i][j] >= 0) return true;
	}

	return false;
}

// Queen
// Combination of Rook and Bishop
bool Board::CheckReina(int i, int j) {
	if (CheckTorre(i, j) || CheckAlfil(i, j)) return true;
	return false;
}

bool Board::CheckMove(int i, int j) {

	// Check type of piece
	switch (abs(desc[pI][pJ])) {
	case 6: return CheckPeon(i, j); break;
	case 5: return CheckRey(i, j); break;
	case 2: return CheckCaballo(i, j); break;
	case 1: return CheckTorre(i, j); break;
	case 3: return CheckAlfil(i, j); break;
	case 4: return CheckReina(i, j); break;
	}
	return false;
}

// 
void Board::CheckJaque() {
	int iR = -1, jR = -1;

	// Position in which is located the contrary king
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) { if ((color && desc[i][j] == -5) || (!color && desc[i][j] == 5)) { iR = i; jR = j; } }
	}

	int npI = pI; int npJ = pJ;
	bool jaq = false;

	// Verify if it is a piece of the corresponding color
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((color && desc[i][j] < 0) || (!color && desc[i][j] > 0)) continue;
			pI = i; pJ = j;

			// Check if I can access those piece
			if (CheckMove(iR, jR)) {
				jaq = true;
				if (color) {

					// If it is already Jaque, then is Jaque Mate
					if (jaqB) jaqMB = true;
					jaqB = true;
				}
				else {

					// If it is already Jaque, then is Jaque Mate
					if (jaqW) jaqMW = true;
					jaqW = true;
				}
			}
		}
	}

	// Handling errors in mapping Jaque and Jaque Mate
	pI = npI; pJ = npJ;
	if (color && !jaq) jaqW = false;
	else if (!jaq) jaqB = false;
}

// Consult if there are a Jaque
void Board::ConsultJaque(bool& jW, bool& jB, bool& jMW, bool& jMB) {
	jW = jaqW;
	jB = jaqB;
	jMW = jaqMW;
	jMB = jaqMB;
}

// Consult turn
bool Board::ConsultTurn() {
	return color;
}

// Draw board with SFML library
void Board::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(board, rs);

	// Drawing pieces in the board, and when those are being dropped
	for (int i = 0; i < (int)piece.size(); i++) {
		if (i != pInd)	rt.draw(piece[i], rs);
	}
	if (pInd != -1) rt.draw(piece[pInd], rs);
}
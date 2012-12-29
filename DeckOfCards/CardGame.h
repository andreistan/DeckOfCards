#pragma once

#include "consts.h"
#include "types.h"
#include "consts.h"
#include "CardDeck.h"

#include <fstream>

namespace nsDeckOfCards {

class CCardGame {

public:
	CCardGame( size_t n = delaultDeckSize );
	~CCardGame();

	void deal( void );
	void hand( void );
	void play( void );
	
	friend ostream& operator<<( ostream& os, CCardGame& cg );

private:
	size_t mCardsNo;

	CCardDeck mPlayer1Cards;
	CCardDeck mPlayer2Cards;

	// game log file
	ofstream gameLogFile;

	// statistical info
	size_t mHands;
	size_t mWars;

	// helpers
	void updateDecks( CCardDeck& player, CCardDeck& cd1, CCardDeck& cd2 );
	void updateDecks( CCardDeck& player, CCard& c1, CCard& c2 );
	void war( CCard& c1, CCard& c2 );
};

}


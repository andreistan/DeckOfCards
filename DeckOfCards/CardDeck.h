#pragma once

#include "types.h"
#include "consts.h"
#include "Card.h"

#include <iostream>
#include <list>

namespace nsDeckOfCards {

class CCardDeck {

public:

	CCardDeck( size_t crtSize = 0, size_t maxSize = maxDeckSize );
	bool isDeckValid( void );
	bool isDeckEmpty( void );
	size_t getDeckSize( void );
	void shuffle( size_t s );
	CCardDeck extract( size_t n );
	void paste( CCardDeck& cd );
	void reverse( void );
	void pasteTop( CCardDeck& cd );
	CCard& peek();
	CCard getCard( void );
	void putCard( CCard& c );
	void putCardTop( CCard& c );

	friend ostream& operator<<( ostream& os, CCardDeck& cd );

private:
	size_t			mMaxNoOfCards;
	size_t			mCrtNoOfCards;
	bool			mDeckIsValid; 
	list<CCard>	mDeck;

};

}

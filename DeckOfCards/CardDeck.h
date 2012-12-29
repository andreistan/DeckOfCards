#pragma once

#include "types.h"
#include "consts.h"
#include "conf.h"
#include "Card.h"

#include <iostream>

#ifdef USE_LIST
	#include <list>
#endif

#ifdef USE_VECT
	#include <vector>
#endif

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

#ifdef USE_LIST
	list<CCard>	mDeck;
#endif

#ifdef USE_VECT
	vector<CCard>	mDeck;
#endif

};

}

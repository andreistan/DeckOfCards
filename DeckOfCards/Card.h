#pragma once

#include "types.h"
#include "consts.h"

#include <iostream>

using namespace std;

namespace nsDeckOfCards {

class CCard {

public:
	CCard( rank_t r = R_UDEF, suit_t s = S_UDEF );
	void setCard( rank_t r, suit_t s );
	rank_t getRank( void ); 
	bool isCardValid( void );

	friend ostream& operator<<( ostream& os, const CCard& c );

	bool operator>( const CCard& rhs );
	bool operator==( const CCard& rhs );

private:
	rank_t mRank;
	suit_t mSuit;
};

}

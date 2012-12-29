#include "Card.h"

namespace nsDeckOfCards {

CCard::CCard( rank_t r, suit_t s ) : 
	mRank( r ), 
	mSuit( s ) {
}

void CCard::setCard( rank_t r, suit_t s ) {
	mRank = r;
	mSuit = s;
}

rank_t CCard::getRank( void ) {
	return mRank;
}

bool CCard::isCardValid( void ) {
	if( ( R_UDEF == mRank ) || ( S_UDEF == mSuit ) ) {
		return false;
	} else {
		return true;
	}
}

ostream& operator<<( ostream& os, const CCard& c ) {
	os << rankNames[ static_cast<int>(c.mRank) ] << suitNames[ static_cast<int>(c.mSuit) ];
	return os;
}

bool CCard::operator>( const CCard& rhs ) {
	if( this->mRank > rhs.mRank ) {
		return true;
	} else {
		return false;
	}
}

bool CCard::operator==( const CCard& rhs ) {
	return( this->mRank == rhs.mRank );
}

}

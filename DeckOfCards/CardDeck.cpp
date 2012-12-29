
#include <cstdint>

#include "CardDeck.h"

namespace nsDeckOfCards {

CCardDeck::CCardDeck( size_t crtSize, size_t maxSize ) :
	mMaxNoOfCards( maxSize ),
	mCrtNoOfCards( crtSize ),
	mDeck(
#ifdef USE_VECT
	crtSize
#endif
	) {
	if ( ( crtSize!=0 ) && ( crtSize <= maxDeckSize ) && ( crtSize % 4  == 0 ) ) {
		uint32_t offset = ( maxDeckSize - crtSize ) >> 2 ;

		// TODO may use lazy evaluation (here is lazy initialization)
		for( uint32_t i = 0; i < crtSize>>2; i++ ) {
			for( uint32_t j = 0; j < 4; j++ ) {

#ifdef USE_VECT
				mDeck[ i * 4 + j ].setCard( static_cast<rank_t>(i+offset), static_cast<suit_t>(j) ); 
#endif

#ifdef USE_LIST
				CCard c;
				c.setCard( static_cast<rank_t>(i+offset), static_cast<suit_t>(j) ); 
				mDeck.push_back( c );
#endif

			}
		}
		mDeckIsValid = true;
	} else {
		mDeckIsValid = false;
	}
}
	
bool CCardDeck::isDeckValid( void ) {
	return mDeckIsValid;
}

bool CCardDeck::isDeckEmpty( void ) {
	return ( mCrtNoOfCards == 0 ) ;
}

size_t CCardDeck::getDeckSize( void ) {
	return mCrtNoOfCards;
}

void CCardDeck::shuffle( size_t s ) {
	if( mCrtNoOfCards ) {
		CCard c;

#ifdef USE_LIST
		list<CCard>::iterator itA;
		list<CCard>::iterator itB;
#endif

		while( s ){
			uint32_t i = rand() % mCrtNoOfCards;
			uint32_t j = rand() % mCrtNoOfCards;
			if( i != j ) {
				s--;

#ifdef USE_VECT
				c = mDeck[ i ];
				mDeck[ i ] = mDeck[ j ];
				mDeck[ j ] = c;
#endif

#ifdef USE_LIST
				itA = mDeck.begin();
				itB = mDeck.begin();

				while( i-- ) itA++;
				while( j-- ) itB++;

				c = *itA;
				*itA = *itB;
				*itB = c;
#endif
			}
		}
	}
}

CCardDeck CCardDeck::extract( size_t n ){
	CCardDeck cd;
	if( n <= mCrtNoOfCards ){
#ifdef USE_VECT
		while( n-- ){
			cd.putCard( getCard() );
		}
#endif

#ifdef USE_LIST
		list<CCard>::iterator it = mDeck.begin();
		cd.mCrtNoOfCards = n;
		mCrtNoOfCards -= n;
		while( n-- ) it++;
		cd.mDeck.splice( cd.mDeck.end(), mDeck, mDeck.begin(), it );
#endif
	}
	return cd;
}

void CCardDeck::paste( CCardDeck& cd ){

#ifdef USE_VECT 
	while( false == cd.isDeckEmpty() ){
		putCard( cd.getCard() );
	}
#endif

#ifdef USE_LIST
	mCrtNoOfCards+=cd.mDeck.size();
	mDeck.splice( mDeck.end(), cd.mDeck );
	cd.mCrtNoOfCards = 0;
#endif
}

void CCardDeck::reverse( void ){
#ifdef USE_VECT
	size_t n = mCrtNoOfCards / 2;
	size_t i = 0;
	CCard c;
	while( n-- ){
		c = mDeck[ i ];
		mDeck[ i ] = mDeck[ mCrtNoOfCards - i - 1 ];
		mDeck[ mCrtNoOfCards - i - 1 ] = c;
		i++;
	}
#endif

#ifdef USE_LIST
	mDeck.reverse();
#endif
}
	
void CCardDeck::pasteTop( CCardDeck& cd ){
#ifdef USE_VECT
	while( false == cd.isDeckEmpty() ){
		putCardTop( cd.getCard() );
	}
#endif

#ifdef USE_LIST
	mCrtNoOfCards += cd.mDeck.size();

	cd.mDeck.reverse();
	cd.mDeck.splice( cd.mDeck.end(), mDeck );
	mDeck.swap( cd.mDeck );

	cd.mCrtNoOfCards = 0;
#endif
}

CCard& CCardDeck::peek(){
	return mDeck.front();
}

CCard CCardDeck::getCard( void ){
	CCard c;
	if( mCrtNoOfCards ) {
		c = mDeck.front();
		mDeck.erase(mDeck.begin());
		mCrtNoOfCards--;
	}
	return c;
}

ostream& operator<<( ostream& os, CCardDeck& cd ) {
	if( cd.mCrtNoOfCards == 0 ){
		os<<"EMPTY";
	} else {

#ifdef USE_VECT
		for( uint32_t i = 0; i < cd.mCrtNoOfCards; i++ ) {
			os << cd.mDeck[ i ];
			os << " ";
		}
#endif

#ifdef USE_LIST
		for( list<CCard>::iterator it = cd.mDeck.begin(); it != cd.mDeck.end(); ++it ) {
			os << *it;
			os << " ";
		}
#endif
	
	}
	os<<endl;
	return os;
}

void CCardDeck::putCard( CCard& c ){
	mDeck.insert( mDeck.end(), c );
	mCrtNoOfCards++;
}

void CCardDeck::putCardTop( CCard& c ){
	mDeck.insert( mDeck.begin(), c );
	mCrtNoOfCards++;
}

}

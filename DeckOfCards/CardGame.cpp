#include <cstdint>

#include "CardGame.h"

namespace nsDeckOfCards {

CCardGame::CCardGame( size_t n ) :
	mCardsNo( n ),
	mPlayer1Cards(),
	mPlayer2Cards(),
	mHands( 0 ),
	mWars( 0 ),
	gameLogFile( gameLogFileName ){
}

CCardGame::~CCardGame( void ){
	gameLogFile.close();
}

void CCardGame::deal( void ) {
	CCard c;
	CCardDeck cd( mCardsNo );
	uint32_t turn = 0;
	cd.shuffle( 6546 );
	// TODO tricky stuff!!!
	while( (c = cd.getCard(), c.isCardValid() ) ) {
		if( turn ) {
			mPlayer1Cards.putCard( c );
		} else {
			mPlayer2Cards.putCard( c );
		}
		turn ^= 1;
	}
}

void CCardGame::hand( void ) {
	CCard c1 = mPlayer1Cards.getCard();
	CCard c2 = mPlayer2Cards.getCard();

	mHands++;

	if( c1 > c2 ){
		updateDecks( mPlayer1Cards, c1, c2 );
	} else if( c1 == c2 ) {
		war( c1, c2 );
	} else {
		updateDecks( mPlayer2Cards, c2, c1 );	
	}
}

void CCardGame::play( void ) {
	while( mPlayer1Cards.isDeckEmpty() == false && mPlayer2Cards.isDeckEmpty() == false ){
		// cout<<"BEFORE "<<"("<<mPlayer1Cards.getDeckSize()<<","<<mPlayer2Cards.getDeckSize()<<") "<<endl<<*this;
		hand();
		gameLogFile<<"AFTER "<<"("<<mPlayer1Cards.getDeckSize()<<","<<mPlayer2Cards.getDeckSize()<<") "<<endl<<*this;
	}
	if( mPlayer1Cards.isDeckEmpty() == true ) {
		gameLogFile<<endl<<"Player 2 is the winner!"<<endl;
	} else if( mPlayer2Cards.isDeckEmpty() == true ) {
		gameLogFile<<endl<<"Player 1 is the winner!"<<endl;
	}
	gameLogFile<<"Total hands: "<<mHands<<endl;
	gameLogFile<<"Total wars: "<<mWars<<endl;
}
	
ostream& operator<<( ostream& os, CCardGame& cg ) {
	os<<cg.mPlayer1Cards;
	os<<cg.mPlayer2Cards;
	return os;
}

void CCardGame::updateDecks( CCardDeck& player, CCardDeck& cd1, CCardDeck& cd2 ){
	cd1.reverse();
	cd2.reverse();
	player.paste( cd1 );
	player.paste( cd2 );
}

void CCardGame::updateDecks( CCardDeck& player, CCard& c1, CCard& c2 ){
	player.putCard( c1 );
	player.putCard( c2 );
}

void CCardGame::war( CCard& c1, CCard& c2 ) {
	size_t n;
	bool war = true;

	CCardDeck cd1, cd2;

	cd1.putCard( c1 );
	cd2.putCard( c2 );

	do{

		mWars++;

		n = ( ACE == cd1.peek().getRank() ) ? 1 : ( cd1.peek().getRank() + 2 );

		if( mPlayer1Cards.getDeckSize() < n ) {
			n = mPlayer1Cards.getDeckSize();
		}
		if( mPlayer2Cards.getDeckSize() < n ) {
			n = mPlayer2Cards.getDeckSize();
		}

		gameLogFile<<endl<<"WAR ( "<<n<<" )"<<endl;

		cd1.pasteTop( mPlayer1Cards.extract( n ) );
		cd2.pasteTop( mPlayer2Cards.extract( n ) );

		if( cd1.peek() > cd2.peek() ){
			war = false;
			updateDecks( mPlayer1Cards, cd1, cd2 );
		} else if( cd1.peek() == cd2.peek() ){
			if( mPlayer1Cards.isDeckEmpty() == true ){ 
				war = false;
				updateDecks( mPlayer2Cards, cd2, cd1 );
			} else if ( mPlayer2Cards.isDeckEmpty() == true ){
				war = false;
				updateDecks( mPlayer1Cards, cd1, cd2 );
			}
		} else {
			war = false;
			updateDecks( mPlayer2Cards, cd2, cd1 );
		}
	} while( war );
}

}

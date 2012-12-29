
// uncomment this include in order to enable the Visual Leak Detector
// #include <vld.h>


#include "CardGame.h"

using namespace std;
using namespace nsDeckOfCards; 

void doIt( void ) {
	CCardGame game( 52 );
	game.deal();
	game.play();
}

void main( void ){
	
#if 0
	CCardDeck cd( 16 );
	cout<<cd;
	cd.reverse();
	cout<<cd;
#endif

#if 0
	CCardDeck cd( 16 );
	CCardDeck cd1;
	
	cout<<cd<<cd1;

	cd.paste( cd.extract( 2 ) );

	cout<<cd<<cd1;
#endif
	
	doIt();

#if 0
	const size_t cardsNo = 4;

	CCardDeck DeckOfCards( cardsNo );
	CCardDeck Player1Cards;
	CCardDeck Player2Cards;

	CCard c;

	cout<<DeckOfCards;

	DeckOfCards.shuffle(145);
	cout<<DeckOfCards;
	
	c=DeckOfCards.getCard();
	cout<<c;
	cout<<endl;

	cout<<DeckOfCards;

	Player1Cards.putCard(c);
	cout<<Player1Cards;

	DeckOfCards.shuffle(145);
	cout<<DeckOfCards;
#endif

}

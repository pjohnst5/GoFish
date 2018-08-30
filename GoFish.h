#pragma once
#include "DoubleLinkedList.h"
class GoFish
{
public:
	GoFish();
	~GoFish();
	void clearDeck();
	void clearPlayerHand();
	void clearComputerHand();
	void createDeck(string fileName);
	void displayDeck();
	void displayPlayerHand();
	void displayComputerHand();
	void play(int numOfCards);
	void drawCard(int humanOrComputer);
	void dealCards(int cardsPerHand);
	void shuffleDeck();
	int getSizeOfDeck() const;
	int getSizeOfPlayerHand() const;
	int getSizeOfComputerHand() const;
	bool isEmpty();
private:
	DoubleLinkedList deckOfCards;
	DoubleLinkedList playerHand;
	DoubleLinkedList computerHand;
	int humanScore;
	int computerScore;
};

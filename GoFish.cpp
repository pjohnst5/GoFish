#include "GoFish.h"


GoFish::GoFish()
{
	humanScore = 0;
	computerScore = 0;
}

GoFish::~GoFish()
{
	clearDeck();
}

int GoFish::getSizeOfDeck() const {
	return deckOfCards.getSize();
}

int GoFish::getSizeOfPlayerHand() const{
	return playerHand.getSize();
}

int GoFish::getSizeOfComputerHand() const {
	return computerHand.getSize();
}

bool GoFish::isEmpty() {
	if (getSizeOfDeck() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void GoFish::clearDeck() {
	deckOfCards.clear();
}

void GoFish::clearPlayerHand(){
	playerHand.clear();
}

void GoFish::clearComputerHand(){
	computerHand.clear();
}

void GoFish::createDeck(string fileName) {
	string name;
	string line;
	int number;
	ifstream myFile;
	myFile.open(fileName.c_str());
	while (myFile >> name) {
		myFile >> number;
		deckOfCards.insertHead(name, number);
		deckOfCards.insertHead(name, number);
	}
	return;
}

void GoFish::displayDeck() {

	if (deckOfCards.getSize() == 0) {
		cout << "Empty" << endl;
		return;
	}
	else {
		string deck = deckOfCards.toStringNoCommas();
		string name;
		string num;
		istringstream ss(deck);
		cout << "Deck: ";
		while (ss >> deck) {
			name = deck;
			ss >> num;
			cout << "\t" << name << " " << num << endl;
		}
		cout << endl;
		return;
	}
}

void GoFish::displayPlayerHand() {
	cout << "Player hand: " << playerHand.toString();
	return;
}

void GoFish::displayComputerHand() {
	cout << "Computer hand: " << computerHand.toString();
	cout << endl;
	return;
}

void GoFish::drawCard(int humanOrComputer) {
	const int HUMAN = 1;
	const int COMPUTER = 2;
	srand(42);
	int indexOfCard = 0;
	string name;
	int num = 0;
	if (deckOfCards.getSize() == 0) {
		cout << "Deck is empty, nothing done." << endl << endl;
		return;
	}
	else {
		indexOfCard = (rand() % deckOfCards.getSize()); //getSizeOfDeck()
		if (humanOrComputer == HUMAN) {
			name = deckOfCards.nameAt(indexOfCard);
			num = deckOfCards.numAt(indexOfCard);
			deckOfCards.removeAt(indexOfCard);
			if (playerHand.findIfDuplicateExists(name, num)) {
				playerHand.remove(name, num);
			}
			else {
				playerHand.insertTail(name, num);
			}
		}
		else {
			name = deckOfCards.nameAtReverse(indexOfCard);
			num = deckOfCards.numAtReverse(indexOfCard);
			deckOfCards.removeAtReverse(indexOfCard);
			if (computerHand.findIfDuplicateExists(name, num)) {
				computerHand.remove(name, num);
			}
			else {
				computerHand.insertTail(name, num);
			}
		}
	}
}

void GoFish::dealCards(int cardsPerHand) {
	const int HUMAN = 1;
	const int COPMUTER = 2;
	int humanOrComputer = HUMAN;

	for (int i = 0; i < cardsPerHand * 2; ++i) {
		if (humanOrComputer == HUMAN) {
			drawCard(humanOrComputer);
			++humanOrComputer;
		}
		else {
			drawCard(humanOrComputer);
			--humanOrComputer;
		}
	}
}

void GoFish::play(int numOfCards) {
	srand(42);
	const int GUESS_OPTION = 1;
	const int SHUFFLE_DECK_OPTION = 2;
	const int DISPLAY_DECK_OPTION = 3;
	const int DISPLAY_COMPUTER_HAND = 4;
	const int GIVE_UP_OPTION = 5;
	const int HUMAN = 1;
	const int COMPUTER = 2;
	const int BONUS = 3;
	int userOption = 0;
	string cardName;
	int cardNum = 0;
	int sizeOfDeck = 0;
	int newSizeOfDeck = 0;
	int computersGuess = 0;
	bool gameIsOver = false;
	bool playerQuitted = false;
	int humanOrComputerTurn = HUMAN;

	shuffleDeck();
	dealCards(numOfCards);

	if (playerHand.getSize() == 0 && computerHand.getSize() == 0) {
		humanScore = BONUS;
		computerScore = BONUS;
		gameIsOver = true;

	}
	else if (playerHand.getSize() == 0) {
		humanScore = BONUS;
		gameIsOver = true;

	}
	else if (computerHand.getSize() == 0) {
		computerScore = BONUS;
		gameIsOver = true;
	}
	while (gameIsOver == false) {
		if (humanOrComputerTurn == HUMAN) {
			do {
				displayPlayerHand();
				cout << "Player score: " << humanScore << endl;
				cout << "Computer score: " << computerScore << endl << endl;

				cout << "PLAY MENU" << endl;
				cout << "1. Make Guess" << endl;
				cout << "2. Shuffle Deck" << endl;
				cout << "3. Display Deck" << endl;
				cout << "4. Display Computer Hand" << endl;
				cout << "5. Give up" << endl;
				cout << "Enter selection: ";
				cin >> userOption;
				cout << endl;

				if (cin.fail() || userOption < GUESS_OPTION || userOption > GIVE_UP_OPTION) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "INVALID SELECTION.  Please try again." << endl << endl;
					userOption = -1;
				}
				else if (userOption == GUESS_OPTION) {
					cout << "What is the name of the card? (Just the name): ";
					cin.ignore(1000, '\n');
					getline(cin, cardName);
					cout << endl;
					cout << "What is the number of the card? (Just the number): ";
					cin >> cardNum;
					cout << endl;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Please enter card number in digit form." << endl << endl;
						cardNum = -1;
					}
					else {
						if (playerHand.findIfDuplicateExists(cardName, cardNum)) {
							if (computerHand.findIfDuplicateExists(cardName, cardNum)) {
								cout << "You guessed correctly!" << endl;
								cout << "Adding a point to your score..." << endl << endl;
								++humanScore;
								playerHand.remove(cardName, cardNum);
								computerHand.remove(cardName, cardNum);
								if (playerHand.getSize() == 0 && computerHand.getSize() == 0) {
									cout << "You both emptied your hands at the same time!" << endl;
									cout << "Adding bonuses to both players' scores.." << endl << endl;
									humanScore = humanScore + BONUS;
									computerScore = computerScore + BONUS;
									gameIsOver = true;
								}
								else if (playerHand.getSize() == 0) {
									cout << "You emptied your hand! Good job." << endl;
									cout << "Adding a bonus to your score..." << endl;
									humanScore = humanScore + BONUS;
									gameIsOver = true;
								}
								else if (computerHand.getSize() == 0) {
									cout << "The computer emptied its hand!" << endl;
									cout << "Adding a bonus to the computer's score..." << endl << endl;
									computerScore = computerScore + BONUS;
									gameIsOver = true;
								}
							}
							else {
								cout << "GO FISH!" << endl << endl;
								sizeOfDeck = playerHand.getSize();
								drawCard(humanOrComputerTurn);
								newSizeOfDeck = playerHand.getSize();
								if (newSizeOfDeck < sizeOfDeck) {
									cout << "You drew a card to complete a pair!" << endl;
									cout << "Adding a point to your score... " << endl << endl;
									++humanScore;
								}
								if (newSizeOfDeck == 0) {
									cout << "You emptied your hand! Good job." << endl;
									cout << "Adding a bonus to your score..." << endl << endl;
									humanScore = humanScore + BONUS;
									gameIsOver = true;
								}
							}
							++humanOrComputerTurn;
						}
						else {
							cout << "That card isn't in your hand. Please pick again.";
							cout << "(Don't add extra spaces)" << endl << endl;
						}
					}
				}
				else if (userOption == SHUFFLE_DECK_OPTION) {
					if (deckOfCards.getSize() == 0) {
						cout << "Deck is empty, therefore it was not shuffled." << endl << endl;
					}
					else {
						shuffleDeck();
						cout << "The deck was shuffled." << endl << endl;
					}
				}
				else if (userOption == DISPLAY_DECK_OPTION) {
					displayDeck();
					cout << endl;
				}
				else if (userOption == DISPLAY_COMPUTER_HAND) {
					displayComputerHand();
				}
				else if (userOption == GIVE_UP_OPTION) {
					playerQuitted = true;
					gameIsOver = true;
				}
			} while (humanOrComputerTurn == HUMAN && gameIsOver == false);
		}
		else {
			computersGuess = 0;
			computersGuess = (rand() % getSizeOfComputerHand());

			cardName = computerHand.nameAt(computersGuess);
			cardNum = computerHand.numAt(computersGuess);
			cout << "The computer guessed \"" << cardName << " " << cardNum << "\"" << endl << endl;

				if (playerHand.findIfDuplicateExists(cardName, cardNum)) {
					cout << "It guessed correctly!" << endl;
					cout << "Adding a point to the computer's score..." << endl << endl;
					++computerScore;
					computerHand.remove(cardName, cardNum);
					playerHand.remove(cardName, cardNum);
					if (playerHand.getSize() == 0 && computerHand.getSize() == 0) {
						cout << "You both emptied your hands at the same time!" << endl;
						cout << "Adding bonuses to both players' scores.." << endl << endl;
						humanScore = humanScore + BONUS;
						computerScore = computerScore + BONUS;
						gameIsOver = true;
					}
					else if (playerHand.getSize() == 0) {
						cout << "You emptied your hand! Good job." << endl;
						cout << "Adding a bonus to your score..." << endl << endl;
						humanScore = humanScore + BONUS;
						gameIsOver = true;
					}
					else if (computerHand.getSize() == 0) {
						cout << "The computer emptied its hand!" << endl;
						cout << "Adding bonus to computer's score..." << endl;
						computerScore = computerScore + BONUS;
						gameIsOver = true;
					}
				}
				else {
					cout << "GO FISH!" << endl << endl;
					sizeOfDeck = computerHand.getSize();
					drawCard(humanOrComputerTurn);
					newSizeOfDeck = computerHand.getSize();
					if (newSizeOfDeck < sizeOfDeck) {
						cout << "The computer drew a card to complete a pair!" << endl;
						cout << "Adding a point to the computer's score..." << endl << endl;
						++computerScore;
					}
					if (newSizeOfDeck == 0) {
						cout << "The computer emptied its hand!" << endl;
						cout << "Adding a bonus to the computer's score..." << endl << endl;
						computerScore = computerScore + BONUS;
						gameIsOver = true;
					}
				}
			--humanOrComputerTurn;
		}
	}

	deckOfCards.clear();
	playerHand.clear();
	computerHand.clear();

	if (playerQuitted) {
		cout << "The computer won, as usual." << endl;
		return;
	}

	else {
		cout << "FINAL SCORE" << endl;
		cout << "Player score: " << humanScore << endl;
		cout << "Computer score: " << computerScore << endl;
		if (humanScore > computerScore) {
			cout << "You win!" << endl;
		}
		else if (humanScore < computerScore) {
			cout << "The computer wins!" << endl;
		}
		else if (humanScore == computerScore) {
			cout << "Its a tie, everybody wins!" << endl;
		}
		return;
	}
}

void GoFish::shuffleDeck() {
	string name;
	int num;
	int sizeOfDeck = getSizeOfDeck();
	if (sizeOfDeck == 1) {
		return;
	}
	else {
		const int NUM_OF_SHUFFLES = 3;
		DoubleLinkedList tempList;
		int sizeOfList = deckOfCards.getSize();
		string name;
		int num;

		for (int k = 0; k < NUM_OF_SHUFFLES; ++k) {
			int j = 0;
			for (int i = 0; i < sizeOfList / 2; ++i) {
				name = deckOfCards.nameAt(0);
				num = deckOfCards.numAt(0);
				tempList.insertTail(name, num);
				deckOfCards.remove(name, num);
			}
			for (int i = 0; i < sizeOfList / 2; ++i) {
				name = tempList.nameAt(0);
				num = tempList.numAt(0);
				tempList.remove(name, num);
				deckOfCards.insertAfter(name, num, j);
				++j;
				++j;
			}
		}

	}

}

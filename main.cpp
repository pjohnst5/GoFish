#include "GoFish.h"

using namespace std;


int main() {
	const int CREATE_DECK_OPTION = 1;
	const int DISPLAY_DECK_OPTION = 2;
	const int PLAY_OPTION = 3;
	const int QUIT_OPTION = 4;
	int userOption = 0;
	int cardsPerHand = 0;
	string fileName;
	GoFish myGame;
	myGame.clearDeck();
	
	cout << "Welcome to the go fish simulator!" << endl;
	do {
		cout << endl;
		cout << "MAIN MENU" << endl;
		cout << "1. Create Deck" << endl;
		cout << "2. Display Deck" << endl;
		cout << "3. Play" << endl;
		cout << "4. Quit" << endl;
		cout << "Enter selection: ";
		cin >> userOption;
		cout << endl;

		if (cin.fail() || userOption < CREATE_DECK_OPTION || userOption > QUIT_OPTION) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "INVALID SELECTION.  Please try again." << endl << endl;
			userOption = -1;
		}
		else if (userOption == CREATE_DECK_OPTION) {
			myGame.clearDeck();

			cout << "What is the name of the deck you want to use? (Don't forget the .txt at the end): ";
			cin.ignore(1000, '\n');
			getline(cin, fileName);
			cout << endl;
			myGame.createDeck(fileName);
			myGame.displayDeck();
		}
		else if (userOption == DISPLAY_DECK_OPTION) {
			myGame.displayDeck();
		}
		else if (userOption == PLAY_OPTION) {
			if (myGame.isEmpty()){
				cout << "No deck" << endl;
			}
			else {
				cout << "How many cards should each player start with? " << endl;
				cout << "Enter selection: ";
				cin >> cardsPerHand;
				cout << endl;
				if (cin.fail() || cardsPerHand <= 0 || cardsPerHand > (myGame.getSizeOfDeck() / 2)) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "INVALID SELECTION.  Please try again." << endl << endl;
					cardsPerHand = -1;
				}
				else {
					myGame.clearPlayerHand();
					myGame.clearComputerHand();
					myGame.play(cardsPerHand);
				}
			}
		}
	} while (userOption != QUIT_OPTION);

	cout << "Goodbye" << endl;

system("pause");
return 0;
}

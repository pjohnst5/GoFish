#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList() {
	head = NULL;
	tail = NULL;
	int numItems = 0;
}

DoubleLinkedList::~DoubleLinkedList() {
	clear();
}

bool DoubleLinkedList::findIfDuplicateExists(string name, int numValue) {
		DNode* DNodePtr = head;
		if (DNodePtr == NULL) {
			return false;
		}
		else {
			while (DNodePtr != NULL) {
				if ((DNodePtr->name) == name && DNodePtr->num == numValue) {
					return true;
				}
				DNodePtr = DNodePtr->next;
			}
			return false;
		}
}

void DoubleLinkedList::insertHead(string cardName, int numValue) {
	DNode* DNodePtr = new DNode(cardName, numValue, NULL, head);
		head = DNodePtr;
		if (head->next != NULL) {
			head->next->prev = head;
		}
		if (tail == NULL) {
			tail = head;
		}
		++numItems;
		return;
}

string DoubleLinkedList::toString() {
	string stringOfNodesData;
	ostringstream out;

	DNode* DNodePtr = head;
	if (DNodePtr == NULL) {
		stringOfNodesData = out.str();
		return stringOfNodesData;
	}
	else {
		while (DNodePtr != NULL) {
			if (DNodePtr->next != NULL) {
				out << (DNodePtr->name) << " " << DNodePtr->num << ", ";
				DNodePtr = DNodePtr->next;
			}
			else {
				out << (DNodePtr->name) << " " << DNodePtr->num << endl;
				DNodePtr = DNodePtr->next;
			}
		}
		stringOfNodesData = out.str();
		return stringOfNodesData;
	}
}

string DoubleLinkedList::toStringNoCommas() {
	string stringOfNodesData;
	ostringstream out;

	DNode* dNodePtr = head;
	if (dNodePtr == NULL) {
		stringOfNodesData = out.str();
		return stringOfNodesData;
	}
	else {
		while (dNodePtr != NULL) {
			if (dNodePtr->next != NULL) {
				out << (dNodePtr->name) << " " << dNodePtr->num << " ";
				dNodePtr = dNodePtr->next;
			}
			else {
				out << (dNodePtr->name) << " " << dNodePtr->num << endl;
				dNodePtr = dNodePtr->next;
			}
		}
		stringOfNodesData = out.str();
		return stringOfNodesData;
	}
}

void DoubleLinkedList::clear() {
		DNode* DnodePtr = head;
		while (head != NULL) {
			DnodePtr = head;
			head = DnodePtr->next;
			delete DnodePtr;
		}
		tail = NULL;
		numItems = 0;
		return;
}

int DoubleLinkedList::getSize() const{
	return numItems;
}

void DoubleLinkedList::remove(string cardName, int cardNum) {
	DNode* DNodePtr = head;
	if (DNodePtr->name == cardName && DNodePtr->num == cardNum && DNodePtr == tail) {
		head = NULL;
		tail = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else if (DNodePtr->name == cardName && DNodePtr->num == cardNum) {
		head = head->next;
		head->prev = NULL;
		DNodePtr->next = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else {
		while (DNodePtr != NULL) {
			if (DNodePtr->name == cardName && DNodePtr->num == cardNum && DNodePtr == tail) {
				tail = DNodePtr->prev;
				tail->next = NULL;
				DNodePtr->prev = NULL;
				delete DNodePtr;
				--numItems;
				return;
			}
			else if (DNodePtr->name == cardName && DNodePtr->num == cardNum) {
				DNodePtr->next->prev = DNodePtr->prev;
				DNodePtr->prev->next = DNodePtr->next;
				DNodePtr->prev = NULL;
				DNodePtr->next = NULL;
				delete DNodePtr;
				--numItems;
				return;
			}
			DNodePtr = DNodePtr->next;
		}
		return;
	}
}

void DoubleLinkedList::removeAt(int index) {
	DNode* DNodePtr = head;
	for (int i = 0; i < index; ++i) {
		DNodePtr = DNodePtr->next;
	}
	if (DNodePtr == head && DNodePtr == tail) {
		head = NULL;
		tail = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else if (DNodePtr == head) {
		head = head->next;
		head->prev = NULL;
		DNodePtr->next = NULL;
		delete DNodePtr;
		--numItems;
		return;
}
	else if (DNodePtr == tail) {
		tail = tail->prev;
		tail->next = NULL;
		DNodePtr->prev = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else {
		DNodePtr->next->prev = DNodePtr->prev;
		DNodePtr->prev->next = DNodePtr->next;
		DNodePtr->prev = NULL;
		DNodePtr->next = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
}

void DoubleLinkedList::removeAtReverse(int index) {
	DNode* DNodePtr = tail;
	for (int i = 0; i < index; ++i) {
		DNodePtr = DNodePtr->prev;
	}
	if (DNodePtr == head && DNodePtr == tail) {
		head = NULL;
		tail = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else if (DNodePtr == tail) {
		tail = tail->prev;
		tail->next = NULL;
		DNodePtr->prev = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else if (DNodePtr == head) {
		head = head->next;
		head->prev = NULL;
		DNodePtr->next = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
	else {
		DNodePtr->next->prev = DNodePtr->prev;
		DNodePtr->prev->next = DNodePtr->next;
		DNodePtr->prev = NULL;
		DNodePtr->next = NULL;
		delete DNodePtr;
		--numItems;
		return;
	}
}

string DoubleLinkedList::nameAt(int index) {
	DNode* DNodePtr = head;
	for (int i = 0; i <= index; ++i) {
		if (i == index) {
			return (DNodePtr->name);
		}
		DNodePtr = DNodePtr->next;
	}
}

int DoubleLinkedList::numAt(int index) {
	DNode* DNodePtr = head;
	for (int i = 0; i <= index; ++i) {
		if (i == index) {
			return (DNodePtr->num);
		}
		DNodePtr = DNodePtr->next;
	}
}

string DoubleLinkedList::nameAtReverse(int index) {
	DNode* DNodePtr = tail;
	for (int i = 0; i <= index; ++i) {
		if (i == index) {
			return (DNodePtr->name);
		}
		DNodePtr = DNodePtr->prev;
	}
}

int DoubleLinkedList::numAtReverse(int index) {
	DNode* DNodePtr = tail;
	for (int i = 0; i <= index; ++i) {
		if (i == index) {
			return (DNodePtr->num);
		}
		DNodePtr = DNodePtr->prev;
	}
}

void DoubleLinkedList::insertAfter(string nameOfCard, int numOfCard, int positionAfter) {
	DNode* DNodePtr = new DNode(nameOfCard, numOfCard, NULL, NULL);
	DNode* afterMe = head;

	for (int i = 0; i < positionAfter; ++i) {
		afterMe = afterMe->next;
	}

	if (tail == afterMe) {
		afterMe->next = DNodePtr;
		DNodePtr->prev = tail;
		DNodePtr->next = NULL;
		tail = DNodePtr;
		++numItems;
		return;
	}
	else {
		DNodePtr->prev = afterMe;
		DNodePtr->next = afterMe->next;
		DNodePtr->next->prev = DNodePtr;
		DNodePtr->prev->next = DNodePtr;
		++numItems;
	}
	return;
}

void DoubleLinkedList::insertBefore(string nameOfCard, int numOfCard, int positionBefore) {
	DNode* DNodePtr = new DNode(nameOfCard, numOfCard, NULL, NULL);
	DNode* beforeMe = head;

	for (int i = 0; i < positionBefore; ++i) {
		beforeMe = beforeMe->next;
	}

	if (head == beforeMe) {
		DNodePtr->prev = NULL;
		DNodePtr->next = head;
		head->prev = DNodePtr;
		head = DNodePtr;
		++numItems;
		return;
	}
	else {
		DNodePtr->next = beforeMe;
		DNodePtr->prev = beforeMe->prev;
		beforeMe->prev = DNodePtr;
		DNodePtr->prev->next = DNodePtr;
		++numItems;
		return;
	}

}

void DoubleLinkedList::insertTail(string nameOfCard, int numOfCard) {
	if (tail != NULL) {
		DNode* DNodePtr = new DNode(nameOfCard, numOfCard, NULL, NULL);
		tail->next = DNodePtr;
		DNodePtr->prev = tail;
		DNodePtr->next = NULL;
		tail = DNodePtr;

		numItems++;
		return;
	}
	else {
		insertHead(nameOfCard, numOfCard);
		return;
	}
}

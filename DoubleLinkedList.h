#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <fstream>


using namespace std;
#pragma once
class DoubleLinkedList
{
public:

	DoubleLinkedList();
	~DoubleLinkedList();

	bool findIfDuplicateExists(string name, int num);

	void insertHead(string name, int numValue);

	string toString();

	string toStringNoCommas();

	void clear();

	int getSize() const;

	void remove(string name, int num);

	void removeAt(int index);

	void removeAtReverse(int index);

	string nameAt(int index);

	int numAt(int index);

	string nameAtReverse(int index);

	int numAtReverse(int index);

	void insertAfter(string name, int num, int positionAfter);

	void insertBefore(string name, int num, int positionBefore);

	void insertTail(string name, int num);


private:
#ifndef DNODE_H_
#define DNODE_H_
		struct DNode {
		string name;
		int num;
		DNode* next;
		DNode* prev;
		DNode(const string& data_item, const int& num_item, DNode* prev_val = NULL, DNode* next_ptr = NULL) :
			name(data_item), num(num_item), prev(prev_val), next(next_ptr) {}
	};
#endif
	DNode* head;
	DNode* tail;
	int numItems;
};

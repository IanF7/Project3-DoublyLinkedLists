//Lydia K Fritz
//2/14/2019
//Provided C++ DLinkedList

#pragma once

#ifndef DLINKLIST_H
#define DLINKLIST_H

#include <iostream>

using namespace std;

template <class T>
class DLinkedList {

	//PROVIDED
	friend ostream& operator<<(ostream& out, const DLinkedList<T>& rhs) {
		DNode* curr = rhs.header->next;
		while (curr != rhs.header) {
			out << curr->data << " ";
			curr = curr->next;
		}
		return out;
	}

public:

	//inner class DNode PROVIDED
	class DNode {
	public:
		DNode* next;
		DNode* prev;
		T data;

		DNode(T val = T()) {
			data = val;
			next = prev = this;
		}


	};

	//create an empty list:  PROVIDED
	DLinkedList() {
		//create the header
		header = new DNode();
	}

	//add method  PROVIDED
	DNode* add(T item) {
		//add a new node and return a 
		//pointer to this node
		DNode* newNode = new DNode(item);
		newNode->prev = header;
		newNode->next = header->next;
		header->next->prev = newNode;
		header->next = newNode;
		return newNode;
	}

	/**
	* ASSIGNED
	* remove val from the list
	*
	* @param val
	* @return true if successful, false otherwise
	*/
	//remove method that takes in a T object called val and returns a bool (O[n])
	bool remove(T val) 
	{
		// creates a bool found and sets it equal to false
		bool found = false;
		//creates a new DNode pointer temp and sets it equal to the address of the value next
		//to header
		DNode* temp = header->next;
		//runs while temp isn't equal to header
		while (temp != header)
		{
			//if the value of temp equals the value, runs the following
			if (temp->data == val)
			{
				//checks if head is NULL and if so, sets header equal to temp->next
				//and the header's prev pointer to NULL
				if (temp->prev == NULL)
				{
					header = temp->next;
					header->prev = NULL;
				}
				//check is the tail is NULL and if so sets the value of temp's next prev
				//pointer to null
				else if (temp->next == NULL)
				{
					temp->prev->next = NULL;
				}
				//runs if the value is in the middle, sets the value of temp's next prev pointer
				//to the next temp and temp's previous next pointer to the previous temp
				else
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				//deletes temp
				delete(temp);
				//sets found to true
				found = true;
				//breaks loop
				break;
			}
			//updates temp
			temp = temp->next;
		}
		//if found is false, prints out that the value was not found
		if (!found)
		{
			cout << "Your value was not found" << endl;
		}
		//returns found
		return found;
	}


	/**
	* ASSIGNED
	*
	* @param item
	*/
	//insertOrder function that takes in a T object called item (O[n])
	void insertOrder(T item)
	{
		//creates a new DNode pointer and sets it equal to item
		DNode* newNode = new DNode(item);
		//creates DNode pointer temp and sets it equal to the addess of the value after header
		DNode* temp = header->next;
		//iterates through loop whil temp isn't equal to header and the value of temp is less 
		//than or equal to the value of newNode
		while (temp->data <= newNode->data && temp != header)
		{
			temp = temp->next;
		}
		//checks if the next value of temp is header and temp is less than or equal to newNode
		if (temp->next == header && temp->data <= newNode->data)
		{
			//sets newNode's next and prev pointers to temp->next and temp
			newNode->next = temp->next;
			newNode->prev = temp;
			//inserts newNode in between temp->next->prev and temp->next
			temp->next->prev = newNode;
			temp->next = newNode;
		}
		//checks if temp equals the header and temp is greater than or equal to newNode
		else if (temp == header && temp->data >= newNode->data)
		{
			//sets newNode's next and prev pointers to temp and temp->prev
			newNode->next = temp;
			newNode->prev = temp->prev;
			//inserts newNode in between temp->prev->next and temp->prev
			temp->prev->next = newNode;
			temp->prev = newNode;
			//sets header equal to newNode
			header = newNode;
		}
		//runs in any other case
		else
		{
			//sets newNode's next and prev pointers to temp and temp->prev
			newNode->next = temp;
			newNode->prev = temp->prev;
			//inserts newNode in between temp->prev->next and temp->prev
			temp->prev->next = newNode;
			temp->prev = newNode;
		}

	}

	/**
	* ASSIGNED
	*
	* @param item
	*/
	//insertOrderUnique function that takes in a T object called item and returns a bool (O[1])
	bool insertOrderUnique(T item)
	{
		//checks if uniqueItem returns false and if so runs insertOrder with the item
		if (!uniqueItem(item))
		{
			insertOrder(item);
		}
		//returns true
		return true;
	}

	/**
	* ASSIGNED
	* PRE:  this and rhs are sorted lists
	* @param rhs
	* @return list that contains this and rhs merged into a sorted list
	* POST:  returned list will not contain duplicates, both rhs and this
	* will have no elements
	*/
	//merge function that takes in a DLinkedList called rhs and returns a DLinkedList (O[n + m])
	DLinkedList merge(DLinkedList rhs) {
		//creates DLinkedList result
		DLinkedList result;
		//creates DNode pointer temp and sets it equal to the address of the value after header
		DNode* temp = header->next;
		//creates an int counter and sets it equal to 1
		int counter = 1;
		//runs while temp doesn't equal header
		while (temp != header)
		{
			//runs insertOrderUnique with the item at the place of counter
			result.insertOrderUnique(findItem(counter));
			//updates counter
			counter++;
			//sets temp equal to the next value
			temp = temp->next;
		}
		//runs a for loop while i is less than counter that removes every item in the list
		for (int i = 1; i < counter; i++)
		{
			remove(findItem(1));
		}
		//sets temp equal to the address of the value after header from the inputted list
		temp = rhs.header->next;
		//resets counter to 1
		counter = 1;
		//runs while temp doesn't equal header of the inputted list
		while (temp != rhs.header)
		{
			//runs insertOrderUnique with the item at the place of counter
			result.insertOrderUnique(rhs.findItem(counter));
			//updates counter
			counter++;
			//sets temp equal to the next value
			temp = temp->next;
		}
		//runs a for loop while i is less than counter that removes every item in the list
		for (int i = 1; i < counter; i++)
		{
			rhs.remove(rhs.findItem(1));
		}
		//returns result
		return result;
	}

	//uniqueItem function that takes in a T object called item and returns a bool (O[n])
	bool uniqueItem(T item)
	{
		//creates a bool unique and sets it equal to false
		bool unique = false;
		//creates a new DNode pointer and sets it equal to item
		DNode* newNode = new DNode(item);
		//creates DNode pointer temp and sets it equal to the address of the value after header
		DNode* temp = header->next;
		//runs while temp isn't equal to header
		while (temp != header)
		{
			//check if newNode equals temp and if so, sets unique to true and ends loop
			if (newNode->data == temp->data)
			{
				unique = true;
				break;
			}
			//sets temp equal to temp->next
			temp = temp->next;
		}
		//returns unique
		return unique;
	}

	//findItem function that takes in an int called find and returns a T (O[n])
	T findItem(int find)
	{
		//creates a new DNode pointer and sets it equal to item
		DNode* temp = header->next;
		//runs a for loop while i is less than find to iterate through list
		for (int i = 1; i < find; i++)
		{
			temp = temp->next;
		}
		//returns the value of temp 
		return temp->data;
	}



private:
	//DLinkedList fields:  PROVIDED
	DNode* header;

};


#endif

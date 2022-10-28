//Lydia K Fritz
//2/14/2019
//driver program for DLinkedList C++
//provided

//Ian Fletcher
//CST-201
//10/2/2022
//This is my own code combined with the template code, some code from the slides in class, 
//and some help from tutorialspoint.com

#include "DLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//initializes cleanUp function
string cleanUp(string str);

//main method
int main() {
	//creates 2 DLinkedList objects 
	DLinkedList<string> lst1;
	DLinkedList<string> lst2;

	//opens the file for Text1
	ifstream fin("Text1.in");

	//creates a string called str
	string str;

	//runs while there is a word to input into str
	while (fin >> str) {
		//sets str equal to the cleaned up version
		str = cleanUp(str);
		//lst1.add(str);
		//inserts str into lst1 using insertOrderUnique
		lst1.insertOrderUnique(str);
	}
	//closes Text1
	fin.close();

	//opens the file for Text1
	fin.open("Text2.in");
	//runs while there is a word to input into str
	while (fin >> str) {
		//sets str equal to the cleaned up version
		str = cleanUp(str);
		//lst2.add(str);
		//inserts str into lst2 using insertOrderUnique
		lst2.insertOrderUnique(str);
	}

	//prints out the lists
	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;

	//creates a DLinkedList object equal to the merged lists
	DLinkedList<string> combined = lst1.merge(lst2);


	//prints out the results after merging
	cout << "\nAFTER MERGE" << endl;
	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;
	cout << "\nCombined: " << combined << endl;


	return 0;
}

/**
* ASSIGNED
* @param str
* @return str in all lower case with LEADING and TRAILING non-alpha
* chars removed
*/

//cleanUp function that takes in a string called str and returns a string (O[n])
string cleanUp(string str) 
{
	//runs a for loop while i is less than the length of the string
	for (int i = 0; i < str.length(); i++)
	{
		//checks if the character at i is uppercase and if so changes it to lowercase
		if (str[i] >= 65 && str[i] <= 90)
		{
			str[i] = str[i] + 32;
		}
		//checks if the character at i isn't a letter and if so removes it
		else if (!(str[i] >= 97 && str[i] <= 122))
		{
			str.erase(str.begin() + i);
		}
	}
	//retuns str
	return str;
}
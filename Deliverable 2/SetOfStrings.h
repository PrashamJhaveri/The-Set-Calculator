//
//  SetOfStrings.h
//  SetOfStrings
//
//  Created by Partha Roop on 26/08/13.
//  Copyright (c) 2013 Partha Roop. All rights reserved.
//

#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h
#include <iostream>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

class SetOfStrings{
protected:
	vector<string> setv;
	vector<string>::iterator p;

public:

	// Set calculation (Students need to complete this section)
	SetOfStrings *setUnion(SetOfStrings *set1);
	SetOfStrings *setIntersection(SetOfStrings *set1);
	SetOfStrings *product(SetOfStrings *set1);
	
    //getters for the private members
    vector<string>::iterator getvitrbegin();
    vector<string>::iterator getvitrend();

	// Utility methods
	bool isEmpty();
	bool isEqual(SetOfStrings *s);
	bool isMember(string s);
	bool subset(SetOfStrings *s);
	int size();
	
	// Insert and remove
	void insertElement(string s);
	void removeElement(string s); 
	
	// Getter
	string returnElement(int index);

};

#endif



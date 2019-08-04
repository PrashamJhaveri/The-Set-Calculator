//
//  SetOfStrings.cpp
//  SetOfStrings
//
//  Created by Partha Roop on 25/09/15.
//  Copyright (c) 2015 Partha Roop. All rights reserved.
//

#include "SetOfStrings.h"

using namespace std;

//Getter for private members
//Returns an iterator pointing to the begining of the private vector
vector<string>::iterator SetOfStrings::getvitrbegin(){

	p=setv.begin();
	return p;
}

//Getter for private members
//Returns an iterator pointing to the end of the private vector
vector<string>::iterator SetOfStrings::getvitrend(){
	p=setv.end();
	return p;
}

bool SetOfStrings::isEmpty()
{
	if(setv.empty()) return true;
	else return false;
}

int SetOfStrings::size(){
	return (int) setv.size();
}

bool SetOfStrings::isMember(string s)
{
	p=setv.begin();
	while(p!=setv.end()){
		if(*p==s)return true;
		++p;
	}
	return false;
}

void SetOfStrings::insertElement(string s)
{
	if(!isMember(s)){
		setv.push_back(s);
	}
}

void SetOfStrings::removeElement(string s)
{
	for(p = setv.begin(); p !=setv.end(); ++p){
		if(*p == s){
			setv.erase(p);
		}
	}


}

// Creates a new set of strings which contains the union
SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
	vector<string>::iterator i;
	SetOfStrings *out = new SetOfStrings();

	//Inserting all the elements from setv to out
	for(p = setv.begin(); p != setv.end(); ++p){
		out->insertElement(*p);
	}
	// Checking if each element is SetofStrings s. if the element of s is not a member of
	// setv then we insert that element into out.
	for(i = s->getvitrbegin(); i != s->getvitrend(); ++i){
		if(!isMember(*i)){
			out->insertElement(*i);
		}
	}
	return out;
}


// Checks if setv is equal to set of Strings s.
bool SetOfStrings::isEqual(SetOfStrings *s)
{
	vector<string>::iterator i;
	// If the sizes don'match then they are not equal and hence return false
	if(setv.size() != s->size())return false;
	int count =0;

	// Checks each element of s with setv if there is a match then incriment count
	for(p = setv.begin(); p != setv.end(); ++p){
		for(i = s->getvitrbegin(); i != s->getvitrend(); ++i){
			if(*i == *p){
				count++;
			}
			//If both sets are equal then return true
			if(count == s->size()) return true;
		}
	}

	return false;
}

string SetOfStrings::returnElement(int index)
{
	if (index < (int)setv.size() && index >= 0)
		return setv.at(index);
	else
		return "\n";
}


//All possible combinations of of setv and s.
SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
	vector<string>::iterator i;
	vector<string>::iterator x;

	//appending each element of setv with s. I.e finding all the combinations and then push back
	//into out.
	SetOfStrings *out = new SetOfStrings();
	for(x = setv.begin(); x != setv.end(); ++x){
		for(i = s->getvitrbegin(); i != s->getvitrend(); ++i){
			out->insertElement(*x + "," + *i );
		}
	}
	return out;
}


//Checking if elements in string s are a part ogf(subset) of setv.
bool SetOfStrings::subset(SetOfStrings *s)
{
	vector<string>::iterator x;
	//Checking if elements in string s are a part ogf(subset) of setv. if there is one element which isn't
	// return false else true
	for(x = s->getvitrbegin(); x != s->getvitrend(); ++x){
		if(!isMember(*x)) return false;
	}
	return true;
}

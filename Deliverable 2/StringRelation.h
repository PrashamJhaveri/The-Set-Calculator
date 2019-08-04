/*
 * StringRelation.h
 *
 *  Created on: 3/09/2015
 *	  Author: Partha Roop
 */

#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_
#include "SetOfStrings.h"
#include <limits>

//A class for binary relation over a single set set1
//A relation uses both "composition" and "inheritance"
//A relation "has a" set using which the binary relation is created
//A relation "is a" set and hence it extends a set
//It can perform all set operations i.e., we can create the union, intersection etc. of two relations
//It has additional behaviour not present in a set: we can test for properties such as:
//Reflexive, Symmetric, and Transitive etc.

class StringRelation : public SetOfStrings{
	private:
		// the set over which the relation is created
		SetOfStrings *set1;
	    vector<int> weight; // weight vector
		string path; // string for dijkstra's path
    
		// String splitter, which is a helper function
		vector<string> makeTokens(string input);
		//given string "a,b" return string "b,a"
		string computeDual(string);
		//given "a", returns "a,a"
		string createReflexiveElement(string s);
		//return true if s is of the form "a,a"
		bool isReflexiveElement(string s);
		//return true if s1 is the first component of s2
		//e.g. s1=a and s2=a,b
		bool isFirstComponent(string s1, string s2);
		//Return the second component of the string "a,b" as b
		string returnSecondComponent(string s);
		//This function converts the product of set1 with itself passed as "s" into
		//A relation called "n". This is so that we can print the elements of the
		
		// Return the weight of an edge
		int getWeight(string s);
		
	public:
		int reachable(string origin, string dest);
		void insertWeight(int weightValue);
		int getWeight(int position);
		void setInput(SetOfStrings *s);
		bool isVisited(vector<string>visited, string s);
		//creates a relation that is identical to the product set of set1
		bool isValid();
		bool isReflexive();
		string returnFirstComponent(string s);
		bool isSymmetric();
		bool isTransitive();
		bool isEquivalence();
		SetOfStrings *computeEquivalenceClass(string element);
		

		// Finding the shortest path
		int computeShortest(string source, string destination);

};
#endif

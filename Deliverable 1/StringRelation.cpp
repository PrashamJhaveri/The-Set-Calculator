/*
 * StringRelation.cpp
 *
 *  Created on: 3/09/2015
 *      Author: Partha Roop
 */

#include "StringRelation.h"
#include <algorithm>


//will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

//This helps by assigning the composition member
//s is the pointer to the input set
//and R \subseteq s \times s
void StringRelation::setInput(SetOfStrings *s)
{
	set1=s;
}

//check if the relation provided as input is a
//valid relation i.e., R \subseteq S \times S
//Return true when valid; false otherwise
bool StringRelation::isValid(){
	//Create the product of set1 with itself
	//out= set1 /times set1
	SetOfStrings *out = new SetOfStrings();
	out = set1->product(set1);
	//Overloaded printRelation method used for printing the relation that is
	//equal to the product set
	printRelation(out);
	//this->printRelation();
	if(out->subset(this)){
		return true;
	}
	else return false;
}






//This is one of the main helper function provided as a
//tokenizer to parse relational elements and separate them into components
//This takes a relation element in the form "a,b" and returns
//a string vector containing "a" and "b"


vector<string> StringRelation::makeTokens(string next){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [next.length()+1];
	strcpy(a,next.c_str());
	char* token = std::strtok(a,",");
	int index=0;
	while (token != NULL) {
		//std::cout << "The next token is: "<< token << '\n';
		out.push_back(token);
		token = std::strtok(NULL, ",");
		index++;
	}
	return out;
}

void StringRelation::printRelation()
{
	cout<<"The elements of the relation are: "<<S->ColourText("{", RED);
	int i=0, j=0;
	j=size();
	while(i<j){
		string next;
		next = returnElement(i);
		if(i!=j-1){
			cout<<S->ColourText("(", RED)<<S->ColourText(next, RED)<<S->ColourText(")", RED)<<S->ColourText(", ", RED);
			//cout<<"("<<next<<")"<<", ";
			++i;
		}
		else{
			cout<<S->ColourText("(",RED)<<S->ColourText(next, RED)<<S->ColourText(")", RED);
			//cout<<"("<<next<<")";
			++i;
		}
	}
	//cout<<"}\n";
	cout<<S->ColourText("}", RED)<<"\n";
}

void StringRelation::printRelation(SetOfStrings *s)
{
	SetOfStrings *out = new SetOfStrings();
	out = set1->product(set1);
	if(!out->isEqual(s)){
		cout<<S->ColourText("Invalid argument -- argument must be a product set of set1", RED)<< "\n";
		return;
	}
	else{
		cout<<"The elements of the relation that is equal to the product set are:"<< S->ColourText("{", BLUE);
		int i=0, j=0;
		j=s->size();
		while(i<j){
			string next;
			next = s->returnElement(i);
			if(i!=j-1){
				cout<<S->ColourText("(", BLUE)<<S->ColourText(next, BLUE)<<S->ColourText(")", BLUE)<<S->ColourText(", ", BLUE);
				++i;
			}
			else{
				cout<<S->ColourText("(",BLUE)<<S->ColourText(next, BLUE)<<S->ColourText(")", BLUE);
				++i;
			}
		}
		cout<<S->ColourText("}", BLUE)<<"\n";
	}
}
void StringRelation::printEquivalenceClasses(){
	if(!isEquivalence()){
		cout<<"Not a equivalence relation"<<endl;
		cout<<"Exiting"<<endl;
		return;
	}
	int i=0;
	int j=set1->size();
	while(i<j){

		string next=set1->returnElement(i);
		cout<<"The next equivalence class for:"<<next<<endl;
		SetOfStrings *out = computeEquivalenceClass(next);
		cout<<"The next equivalence class is"<<endl;
		out->print();
		++i;
	}
}


//helper function that returns the string "a,a" when input is "a"
string StringRelation::createReflexiveElement(string s){
	string next, next1;
	next = s;
	next1=next;
	next.append(",");
	next.append(next1);
	//cout<<"The reflexive element created"<<next<<endl;
	return next;
}


//helper function that creates a dual of "a,b" as "b,a"
string StringRelation::computeDual(string s){

	vector<string> tokens=makeTokens(s);
	vector<string>::iterator p;
	p=tokens.begin();
	string other, other1;
	while(p!=tokens.end()-1){
		other=*p;
		//cout<<"Other: "<< *p << "\n";
		other1=*(p+1);
		//cout<<"Other1: "<<other1<<"\n";
		other1.append(",");
		other1.append(other);
		++p;
	}
	//cout<<"Other1:"<<other1<<endl;
	return other1;
}

//return "b" if s is of the form "a,b"
string StringRelation::returnSecondComponent(string s){
	vector<string> tokens;
	vector<string>::iterator p;
	tokens=makeTokens(s);
	p=tokens.begin();
	return *(p+1);
}

string StringRelation::returnFirstComponent(string s){
	vector<string> tokens;
	vector<string>::iterator p;
	tokens=makeTokens(s);
	p=tokens.begin();
	return *(p);
}

//check if s is of the form "a,a" and return true if so
//return false otherwise
bool StringRelation::isReflexiveElement(string s){
	vector<string> check = makeTokens(s);
	if(check[0] == check[1]) return true;
	else return false;
}


//check if the relation is reflexive
//if for all s \in set1, (s,s) \in r then reflexive
bool StringRelation::isReflexive(){
	//You are required to implement this
	int count =0;
	vector<string>::iterator p;
	vector<string>::iterator x;

	// Converting set1 into reflexive and checking if there is a match.
	// if all the elements in set1 have a relfexive present in setv return true.
	for(x = set1->getvitrbegin(); x!=set1->getvitrend(); ++x){
		for(p =setv.begin(); p!=setv.end(); ++p){
			if(createReflexiveElement(*x) == *p) count++;
			//checking if all the elments are present
			if(count == set1->size()) return true;
		}
	}
	return false;
}


//check if the relation is symmetric
//if for any s1,s2 \in set1, (s1,s2) \in R implies (s2,s1) \in R
bool StringRelation::isSymmetric(){
	int count=0;
	vector<string>::iterator i;
	vector<string>::iterator p;

	// Cheching if there is a semetric version of setv present in setv
	// if so incriment count
	for(p =setv.begin(); p!=setv.end(); ++p){
		for(i =setv.begin(); i!=setv.end(); ++i){
			if(computeDual(*p) == *i){
				count++;
			}
			if(count == setv.size()) return true;
		}

	}
	return false;
}






//check if the relation is transitive
// for all x,y,z \in set1, (x -> y AND y -> z) implies x -> z
bool StringRelation::isTransitive(){
	vector<string>::iterator p;
	vector<string>::iterator i;

	for(p = setv.begin(); p != setv.end(); ++p){
		// asignening elements to a b
		string a = returnFirstComponent(*p);
		string b = returnSecondComponent(*p);
		for(i = setv.begin(); i != setv.end(); ++i){
			//checking if whether there is a relation that starts with
			// if so appent that with a and check where is a member. if member not is present
			// return false
			if(b == returnFirstComponent(*i)) {
				string c = returnSecondComponent(*i);
				string pair = a + "," + c;
				if(!isMember(pair)) return false;
			}
		}
	}
	return true;
}



//return true if the relation is an equivalence relation
//return false otherwise
bool StringRelation::isEquivalence(){

	if(isTransitive() && isSymmetric() && isReflexive()) return true;
	else return false;
}

//s1 is of the form "a" while s2 is of the form "p,q"
//if a==p then return true
bool StringRelation::isFirstComponent(string s1, string s2){
	;
	vector<string> out = makeTokens(s2);
	if(out[1] == s1) return true;
	else return false;
}


//Given a member of set1, this function determine the equivalence class
//for this element s1 i.e. {s| (s,s1) \in R and R is a equivalence relation}
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	//You are required to implement this
	vector<string>::iterator p;
	SetOfStrings *out = new SetOfStrings();

	//first component of the relation is equal to the element string push back second component
	// into out.
	if(isEquivalence()){
		for(p = setv.begin(); p!=setv.end(); ++p ){
			if(element == returnFirstComponent(*p)){
				out->insertElement(returnSecondComponent(*p));

			}
		}
	}
	return out;
}

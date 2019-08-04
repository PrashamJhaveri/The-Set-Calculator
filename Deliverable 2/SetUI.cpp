#include "SetUI.h"
#include <string>

SetUI::SetUI()
{
	TopicScreen();
}

// Greet the user and shows the developer name.
void SetUI::TopicScreen()
{
	system("clear");
	cout <<"----------------------------------------------------------------------"<< endl; // Replace the name with yours
	cout <<"\033[1;31mSet Calculator\033[0m\nDeveloper Name: " << "\033[1;34mPrasham Jhaveri PJHA33 890007029 \033[0m\n";
	cout <<"To know available commands, please type 'help'" << endl;
	cout <<"---------------------------------------------------------------------"<< endl;
}




bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose)
{

	string line;
	ifstream infile (filename.c_str());
	if(verbose) cout<< infile.rdbuf();


	//return false if the file does not exist
	if (!infile.good()) return false;

	getline(infile,line); // Get the first line to extract set members
	line.erase(0,2); // Remove '//' in the line



	int i = 0;
	size_t found;
	while((found = line.find(",",i))!=std::string::npos) {
		ss->insertElement(line.substr(i,found-i));
		i = found+1;	
	}

	//Inserting Element into ss
	ss->insertElement(line.substr(i));

	getline(infile,line); // To bypass the second line
	//read the rest of the file.

	while (getline(infile,line)){
		if(line.find("[") == string::npos) continue;
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		// find } as the finisher for file reading
		if (line.find("}")!=string::npos) break; 
		// fetch set and relation in the line 
		if (!getFromLine(ss, sr, line)) return false;

	}

	infile.close();
	sr->setInput(ss);	

	return true;
}




bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line){
	vector<string> element;
	StringRelation tempRel;
	string relation;
	int i = 0;
	size_t found;


	while((found = line.find("->",i))!=std::string::npos) {
		element.push_back(line.substr(i,found-i));
		i = found+2;
	}
	element.push_back(line.substr(i,line.find("[",i)-i));
	relation = element[0]+ "," + element[1];
	tempRel.insertElement(relation);


	// If the relation is a valid relation insert or else return false
	tempRel.setInput(ss);
	if(tempRel.isValid()){
		sr->insertElement(relation);
	}
	else return false;

	//Removes spaces between each line and extracts the weight
	string noSpace;
	int r=0, j=0;
	while(line[r]){
		if(line[r] != ' '){
			line[j++] =line[r];
			r++;
		}
		line[j] = '\0';
		noSpace = line;
	}
	size_t first =  noSpace.find_first_of("\"");
	size_t last = noSpace.find_last_of("\"");
	string number = noSpace.substr(first+1, (last-first-1));

	// Convert to string to int.
	int weightInt = std::atoi(number.c_str());

	//Insert into relation
	sr->insertWeight(weightInt);


	return true;
}



// Prints the set of strings
void SetUI::ListMembers(SetOfStrings* model){

	// if no sets print following
	if(model->size() == 0)cout<< ColorText(" There are no sets", RED);


	//Print all the members in the set by looping through them and printing each member
	cout<<" The member of the ";
	cout<< ColorText("sets", BLUE);
	cout<<" are: \n";
	cout<<" =>";
	cout<<" {";
	int i =0, j=0;
	j = model->size();
	while(i<j){
		string next;
		next = model->returnElement(i);
		if(i!=j-1){
			cout<<ColorText(next, BLUE)<<", ";
			++i;
		}
		else{
			cout<<ColorText(next, BLUE);
			++i;
		}
	}
	cout<<"} \n";




}




// Prints the weights and relations
void  SetUI::ListMembers(StringRelation* model){

	//If empty return the following
	if(model->size() == 0) cout<< ColorText(" There are no relations", RED);

	//Print all the relations in the set by looping through them and printing each
	cout<<" The member of the ";
	cout<< ColorText("relations", YELLOW);
	cout<<" are: \n";
	cout<<" =>";
	cout<<" {";
	int i =0, j=0;
	j = model->size();
	while(i<j){
		string next;
		next = model->returnElement(i);
		if(i!=j-1){
			cout<<"("<<ColorText(next, YELLOW)<<")"<<", ";
			++i;
		}
		else{
			cout<<"("<<ColorText(next, YELLOW)<<")";
			++i;
		}
	}
	cout<<"} \n";


	//Print all the weights in the set by looping through them and printing each
	cout<<" The associated ";
	cout<< ColorText("weights", PURPLE);
	cout<<" are: "<<endl;
	cout<<" =>";
	cout<<" {";
	int k =0, l=0;
	l = model->size();
	while(k<l){
		int weightVal = model->getWeight(k);

		//Convert weight element to string type as ColorText takes in Strings
		string next = to_string(weightVal);
		if(k!=l-1){
			cout<<ColorText(next, PURPLE)<<", ";
			++k;
		}
		else{
			cout<<ColorText(next, PURPLE);
			++k;
		}
	}
	cout<<"}"<<endl;
}




// Printing is the two nodes are reachable.
// Passes through an int which is given from the reachable function.
// Depending on the int a different message will be output
void SetUI::printReachable(int x){
	//
	if(x == 1) cout<<ColorText(" Reachable!",GREEN)<<endl;
	if(x == 2) {
		cout<<ColorText(" Reachable!",GREEN)<<endl;
		cout<<ColorText(" (Source == Destination)",PURPLE)<<endl;
	}
	if(x == 3) printError("invalidMember");
	if(x == -1) cout<<ColorText(" Unreachable!",RED)<<endl;



}



// Print function for equivalence class search
void SetUI::printEquivalenceClass(string member, SetOfStrings* ss){


	// Prints member and SetofStrings. Loops through set of strings to print each element
	cout<<" => [";
	cout<< ColorText(member, BLUE);
	cout<<"]";
	cout<< " = ";
	cout<< "{";
	int i =0, j=0;
	j = ss->size();
	while(i<j){
		string next;
		next = ss->returnElement(i);
		if(i!=j-1){
			cout<<ColorText(next, YELLOW)<<", ";
			++i;
		}
		else{
			cout<<ColorText(next, YELLOW);
			++i;
		}
	}
	cout<<"} \n";

}



// Prints the relationship of the relations.
void SetUI::printProperties(string property, bool isProperty){

	// Prints different message depending on whether or not it is reflexive
	if(property == "reflexive") {
		if(isProperty){
			cout<< ColorText(" => It is reflexive ",GREEN)<<endl;
		}
		else {
			cout<<ColorText(" => It is not reflexive ",RED)<<endl;
		}
	}

	// Prints different message depending on whether or not it is symmetric
	else if(property == "symmetric") {
		if(isProperty){
			cout<< ColorText(" => It is symmetric ",GREEN)<<endl;
		}
		else {
			cout<<ColorText(" => It is not symmetric ",RED)<<endl;
		}
	}
	// Prints different message depending on whether or not it is transitive
	else if(property == "transitive") {
		if(isProperty){
			cout<< ColorText(" => It is transitive ",GREEN)<<endl;
		}
		else {
			cout<<ColorText(" => It is not transitive ",RED)<<endl;
		}
	}

	//// Prints different message depending on whether or not it is equivalent
	else if(property == "equivalent") {
		if(isProperty){
			cout<< ColorText(" => This is an equivalence relation ",GREEN)<<endl;
		}
		else {
			cout<<ColorText(" => This is not an equivalence relation ",RED)<<endl;
		}
	}

}





void SetUI::printError(string reason)
{

	// error message if the command cannot be understood
	if (reason.compare("command") == 0){
		cout << ColorText(" Command cannot be understood. Please enter help to see the available commands\n", RED);
	}
	// error message if the command argument is incorrect
	else if (reason.compare("argument") == 0){
		cout <<ColorText( "Incorrect command arguments!\n", RED);
		cout <<ColorText( "Please type help to know about the command arguments\n", RED);
	}

	// error message if the command argument is incorrect
	else if (reason.compare("file") == 0){
		cout <<ColorText( " Error occured while reading the input file. Possible reasons: \n", RED);
		cout <<ColorText( " 1. File does not exist\n", RED);
		cout <<ColorText( " 2. Contains and invalid graph\n", RED);
		cout <<ColorText( " 3. Unreadable data\n", RED);
		cout <<ColorText( " Graph could not be loaded successfully\n", RED);
	}

	// error message if the command argument is incorrect
	else if (reason.compare("work") == 0){
		cout<< ColorText(" File reading was successful\n", GREEN);
		cout<<ColorText(" Please type 'list' to view the members and relations defined in the graph\n", GREEN);
		cout<< ColorText(" If a directory is opened instead of a file, program will generate incorrect outputs\n", PURPLE);

	}

	else if (reason.compare("invalidMember") == 0){
		cout<< ColorText(" The requested member does not exist in the set \n", RED);
		cout<<ColorText(" Please type 'list' to know about existing strings \n", RED);

	}

	else if (reason.compare("eqclassInvalid") == 0){
		cout<< ColorText(" Equivalence class request could not be executed \n", RED);
		cout<<ColorText(" Possibly the string does not exist in the set or there is no equivalence relation\n", RED);

	}

	else if (reason.compare("sameParameters") == 0){
		cout<< ColorText(" Dijkstra's algorithm cannot handle (source == destination) \n", WHITE);
		cout<<ColorText(" The shortest path distance: ", WHITE);
		cout<<ColorText("0", GREEN)<<endl;

	}

}




string SetUI::GetCommand()
{
	string commandInput;
	cout << ">> ";

	getline (cin, commandInput);
	return commandInput;
}




//prints the help message (Completed)
void SetUI::Help()
{
	cout << "Currently available commands:\n";
	cout << "Anything inside <> bracket is an optional argument, while [] bracket contains a must argument.\n\n";
	cout << left << setw(45) << ColorText("	help", RED) << left << setw(50) << "Show help." << endl << endl;
	cout << left << setw(45) << ColorText("	ls <path> ", RED) << left << setw(50) << "Identical to the ls shell command. If a path is given, then" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "the program returns all the files in that path." << endl << endl;
	cout << left << setw(45) << ColorText("	clear ", RED) << left << setw(50) << "Identical to the clear shell command. Clear the screen." << endl << endl;
	cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED) << left << setw(50) << "Open a file. If the file does not exist, then program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message. If -v (verbose) option is enabled (e.g., open a.txt -v)," << endl;
	cout << left << setw(41) << "" << left << setw(50) << "then each line in the file is printed on console while reading." << endl << endl;
	cout << left << setw(45) << ColorText("	list", RED) << left << setw(50) << "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left << setw(50) << "Check the relation. The option has to be provided. Options are:" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-t (transtivie)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left << setw(50) << "Show equivalence class of the given [VALUE = Set member]." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If VALUE is not a member of set, then the program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED) << left << setw(50) << "This command checks if two given members are connected to each other" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If any of VALUE1 and VALUE2 is not a member of the set, then it" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "returns an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED) << left << setw(50) << "Apply Dijkstra algorithm to find the shortest path." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting node, and VALUE2 is the destination." << endl << endl;
	cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50) << "Terminate the program." << endl;
	cout << "\n\n";
}




void SetUI::printShortestPath(int distance, string path){
	cout << "  The shortest path distance: " << ColorText(to_string(distance),GREEN) << endl;
	cout << "  The path is: " << ColorText(path, BLUE) << endl;
}




string SetUI::ColorText(string s, COLOR color)
{
	string temp;
	switch (color) {
	case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
	case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
	case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
	case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
	case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
	case PURPLE: temp = "\033[1;35m" + s + "\033[0m"; break;
	default: temp = "\033[0m" + s; break;
	}
	return temp;
}


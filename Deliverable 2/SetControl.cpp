/* This is the controller part for your program.
 * In this file, students are required to complete the "control" logic.
 * Controller accepts keyboard inputs from the user through View, and manipulate data in Model.
 * Then, the result from Model is sent back to user through View.
 * Think about the design before the actual implementation.
 * Various diagrams such as class diagram and sequence diagram can be very helpful.
 *
 * Created on: 3/09/2015
 * Last update: 1/09/2017
 *     Author: Jin Ro
 */
#include "SetControl.h"

SetControl::SetControl()
{
	cout <<"Initializing the calculator, please wait! ... \n" << endl;

	//instansiate all members

	setUI = new SetUI();
	setModel = new SetOfStrings();
	relationModel = new StringRelation();


}

SetControl::~SetControl()
{
	//dispose all members
	delete setUI;
	delete setModel;
	delete relationModel;
}



bool SetControl::Run()
{			
#ifdef _DEBUG
	Testing();
	return false; // exit the program after testing
#endif

	string command;

	//invoke the main user interaction
	while(true)
	{

		//show the menu and get user command
		command = setUI->GetCommand();
		int argc = 0;

		// string tokenizer to split string by using " " as the separator.
		// stores the values in argv array while the number of argument is argc.
		vector<string> argv;
		int i = 0;
		size_t found;
		while((found = command.find(" ",i))!=std::string::npos) {

			argv.push_back(command.substr(i,found-i));

			i = found+1;
		}
		argv.push_back(command.substr(i));

		argc = argv.size();

		// if enter is pressed
		if (argc == 0) continue;





		//help command execution (Completed)
		if (argv.at(0).compare("help")==0){
			setUI->Help();
		}
		//ls command execution (Completed)
		else if (argv.at(0).compare("ls")==0){
			if (!(argc == 1 || argc == 2)){setUI->printError("argument"); continue;}
			if (argc == 2){
				string cmd(argv[1]);
				cmd = "ls " + cmd;
				system(cmd.c_str());		
			}		
			else system("ls");
		}



		//Open command
		else if (argv.at(0).compare("open")==0){

			if (!(argc == 2 || argc == 3)) {setUI->printError("argument"); continue;}
			SetOfStrings *temps = new SetOfStrings();
			StringRelation *tempr = new StringRelation();


			// If verbose is detected then if the file is not read then error messege will be
			//returned else relation and set will be set
			if((argc == 3)&& (argv.at(2) == "-v")){
				if(!(setUI->ReadFromFile(argv.at(1), temps, tempr, true))){
					setUI->printError("file");
					continue;
				}
				else{
					relationModel = tempr;
					setModel = temps;
					setUI->printError("work");
					continue;
				}
			}

			//If Not verbose then file is read. If file cannot be read then error will be shown
			// If file is read then else relation and set will be set.
			else if (argc == 2) {
				if(!(setUI->ReadFromFile(argv.at(1), temps, tempr, false))){
					setUI->printError("file");
					cout<<"3";
					continue;
				}
				else{;
				relationModel = tempr;
				setModel = temps;
				setUI->printError("work");
				continue;
				}
			}

			//If an invalid combination is entered Error will be given
			else{
				setUI->printError("file");
				continue;
			}
		}


		// List command. Return the sets, weights and relation
		else if (argv.at(0).compare("list")==0){
			setUI->ListMembers(setModel);
			setUI->ListMembers(relationModel);
			continue;

		}


		//Checks the type of relation type. I.e. whether its reflexive, transitive, symmetric and equivalent
		else if (argv.at(0).compare("check")==0){

			// Checking if reflexive was entered if so then print is reflexive
			if(argc == 2 && argv.at(1)=="-r"){
				setUI->printProperties("reflexive", relationModel->isReflexive());
				continue;
			}

			// Checking if transitive was entered if so then print is transitive
			else if(argc == 2 && argv.at(1)=="-t"){
				setUI->printProperties("transitive", relationModel->isTransitive());
				continue;
			}

			// Checking if symmetric was entered if so then print is symmetric
			else if(argc == 2 && argv.at(1)=="-s"){
				setUI->printProperties("symmetric",relationModel->isSymmetric());
				continue;
			}

			// Checking if equivalent was entered if so then print is equivalent
			else if(argc == 2 && argv.at(1)=="-e"){
				setUI->printProperties("equivalent",relationModel->isEquivalence());
				continue;
			}

			// If invalid combination print error
			else{
				setUI->printError("argument");
				continue;
			}

		}



		// Equivalence command
		else if (argv.at(0).compare("eqclass") == 0) {

			// if Relation is not equivalent print error message
			if (!(relationModel->isEquivalence())) {
				setUI->printError("eqclassInvalid");
				continue;
			}

			//If value is not member of set then return error
			if (!(setModel->isMember(argv.at(1)))){
				setUI->printError("invalidMember"); /// change error in phone photo
				continue;
			}

			//If Equivalent print class.
			if (argc == 2) {
				setUI->printEquivalenceClass(argv.at(1),
						relationModel->computeEquivalenceClass(argv.at(1)));
				continue;
			}
		}



		//Reachable command
		else if (argv.at(0).compare("reachable") == 0){

			//Prints whether or not the relation is reachable
			if(argc == 3){
				setUI->printReachable(relationModel->reachable(argv.at(1), argv.at(2)));
			}

			//If invalid input then return error
			else{
				setUI->printError("argument");
			}
		}


		//Path command
		else if (argv.at(0).compare("path") == 0){
			if(argc == 3){

				//Returns error if same parameters are enteres
				if(argv.at(1) == argv.at(2)){
					setUI->printError("sameParameters");
				}
				if((!setModel->isMember(argv.at(1))) || (!setModel->isMember(argv.at(2)))){
					setUI->printError("invalidMember");
				}
			}

			//If invalid option is enetered then error.
			else{
				setUI->printError("argument");
			}

		}


		// Clear Screen
		else if (argv.at(0).compare("clear") == 0) {
			system("clear");
			setUI->TopicScreen();
		}



		// exit cmmand execution (Completed)
		else if (argv.at(0).find("exit")!=string::npos){
			exit(0);
		}


		// Command is invalid 
		else{
			setUI->printError("command");
		}


	}

	return true;
}

// This function is compiled only when the debug flag is enabled.
#ifdef _DEBUG
void SetControl::Testing(){
	//the name of each test file is hardcoded here.
	SetOfStrings *setTest = new SetOfStrings();
	StringRelation *relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/a.txt", setTest, relationTest, false)==true, "File successfully opened: a.txt");
	// a.txt file contains a graph that is reflexive but not symmetric and transitive.
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive"); // pass if reflexive
	ASSERT(relationTest->isSymmetric()==false, "Relation is not symmetric"); // pass if NOT symmetric
	ASSERT(relationTest->isTransitive()==false, "Relation is not transitive"); // pass if NOT transitive

	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/b.txt", setTest, relationTest, false)==true, "File successfully opened: b.txt");
	// b.txt file contains a graph that is reflexive and symmetric but not transitive.
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive"); // pass if reflexitve
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric"); // pass if symmetric
	ASSERT(relationTest->isTransitive()==false, "Relation is not transitive"); // pass if NOT transitive

	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/c.txt", setTest, relationTest, false)==true, "File successfully opened: c.txt");
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive");
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric");
	ASSERT(relationTest->isTransitive()==true, "Relation is transitive");

	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/d.txt", setTest, relationTest, false)==true, "File successfully opened: d.txt");
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive");
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric");
	ASSERT(relationTest->isTransitive()==true, "Relation is transitive");

	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/e.txt",setTest,relationTest, false)==true, "File successfully opened: e.txt");
	ASSERT(relationTest->isReflexive()==false, "Relation is not reflexive");
	ASSERT(relationTest->isSymmetric()==false, "Relation is not symmetric");
	ASSERT(relationTest->isTransitive()==true, "Relation is transitive");
}
#endif



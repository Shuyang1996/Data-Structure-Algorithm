#include <iostream>
#include <string>
#include <stdlib.h>
#include "hash.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

hashTable dictionary(100000);

void loadDict(ifstream &dict){
	
	string inputWord;
	
	//insert words in hashtable
	while( getline(dict, inputWord) ) {
		transform( inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);
		dictionary.insert( inputWord );
	}

}

void spellCheck(ifstream &input, ofstream &output){
	
	string inputWord, singleWord;
	int character;
	int line = 1;
	bool isNumber;

	while( getline( input, inputWord) ) {
		transform( inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);

		// need to dig into this
		for(int i = 0; i < inputWord.size(); i++ ) {
			character = (int) inputWord[i];
			if()
		}

		stringstream streamObject(inputWord);
		
		while( streamObject >> singleWord ) { //check each word by using streamstring class object
			isNumber = false;
			for(int i = 0; i < singleWord.size(); i++) {
				character = (int) singleWord[i];
				if( (character > 47) && (character < 58) ) isNumber = true;
			}

			if( singleWord.size() > 20 ){
				output << "Long word at line " <<line <<", starts: " << singleWord.substr(0,20) << endl;
			} else if( dictionary.contains(singleWord) || isNumber){
				; // if dictionary contains this word or this word contains number, then we consider this word as a valid word
			} else{
				output << "Unknown word at line " << line <<": " << singleWord << endl; 
			}

		}

		line++;
	}
}

int main (){
	string name; //name for dictionary
	cout <<"Enter name of dictionary: ";
	cin >> name;

	//create input stream
	ifstream dict (name.c_str());

	if(!dict){
		cerr << "Error: cannot open: " << dict << endl;
		exit(1);
	}

	clock_t t1 = clock();

	loadDict(dict);

	clock_t t2 = clock();

	double time1 = (double) (t2 - t1) / CLOCKS_PER_SEC;

	cout << "Total time (in seconds) to load dictionary: "<< time1 <<endl;

	dict.close(); //close dictionary file after inserting words into hashtable


	// user prompt for entering input file
	cout << "Enter name of input file: ";
	cin >> name;
	ifstream inputFile ( name.c_tr() );
	if( !inputFile ){
		cerr << "Cannot open: " << inputFile << endl;
		exit(1);
	}

	// user prompt for entering output file;
	cout << "Enter name of output file: ";
	cin >> name;
	ofstream outputFile ( name.c_str() );
	if( !outputFile ){
		cerr << "Cannot open: " << outputFile << endl;
		exit(1);
	}

	clock_t t3 = clock();

	spellCheck(inputFile, outputFile);

	clock_t t4 = clock();

	inputFile.close();
	outputFile.close();

	double time2 = (double) (t4 - t3) / CLOCKS_PER_SEC;

	cout <<"Total time (in seconds) to check document: " << time2 << endl;

	return 0;
}















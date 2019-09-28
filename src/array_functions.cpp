/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include <sstream>
#include "utilities.h"
#include "array_functions.h"
#include "constants.h"
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry{
	std::string word;
	int numOccur;
};
//TODO add a global array of entry structs (global to this file)
entry entries[constants::MAX_WORDS];

//TODO add variable to keep track of next available slot in array
int tracker= 0;
//TODO define all functions in header file
void clearArray(){
	for(int i = 0; i < tracker; i++){
		entries[i].word = " ";
		entries[i].numOccur = 0;
	}
	tracker = 0;
}

int getArraySize(){
	return tracker;
}

std::string getArrayWordAt(int i){
	return entries[i].word;
}

int getArrayWord_NumbOccur_At(int i){
	return entries[i].numOccur;
}

bool processFile(std::fstream &myfstream){
	bool fail= false;
	bool success= true;
	if(!myfstream.is_open())
		return fail;
	std::string line;
	while(!myfstream.eof()){
		getline(myfstream, line);
		processLine(line);
	}
	return success;
}

void processLine(std::string &myString){

	std::stringstream ss(myString);
	std::string token;

	while (ss){
		std::string word;
		ss>>word;
		processToken(word);
	}
}

void processToken(std::string &token){
	bool validWord = strip_unwanted_chars(token);
	std::string upperToken = token;
	toUpper(upperToken);
	int startOfArray = 0;
	int firstOccur = 1;

	if(validWord){
		if(tracker == startOfArray){
			entries[startOfArray].word= token;
			entries[startOfArray].numOccur = firstOccur;
			tracker++;
		}
		else{
			bool found = false;
			for(int i = 0; i < tracker; i++){
				std::string upperWord = entries[i].word;
				toUpper(upperWord);
				if(upperToken == upperWord){
					entries[i].numOccur++;
					found = true;
					break;
				}
			}
			if(!found){
				entries[tracker].word = token;
				entries[tracker].numOccur = firstOccur;
				tracker++;
			}
		}
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName, std::ios_base::openmode mode){
	bool fail = false;
	bool success = true;
	myfile.open(myFileName.c_str(), mode);
	if(!myfile.is_open()){
		return fail;
	}
	return success;
}

void closeFile(std::fstream& myfile){
	if (myfile.is_open())
		myfile.close();
}

int writeArraytoFile(const std::string &outputfilename){
	std::ofstream outputFile;
	outputFile.open(outputfilename.c_str());
	if(!outputFile.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	int fileEmpty = 0;
	if(tracker == fileEmpty){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	std::string lineOut;
	for(int i = 0; i < tracker; i++){
		std::string numString = intToString(entries[i].numOccur);
		lineOut = entries[i].word + numString + "\n";
		outputFile << lineOut;
	}
	outputFile.close();
	return constants::SUCCESS;
}

void sortArray(constants::sortOrder so){

	for(int i = 0; i < tracker; i++){
		for(int j = 0; j < tracker; j++){
			std::string str1 = entries[i].word;
			std::string str2 = entries[j].word;
			int num1 = entries[i].numOccur;
			int num2 = entries[j].numOccur;
			if(str2 > str1){
				entries[i].word = str2;
				entries[i].numOccur = num2;
				entries[j].word = str1;
				entries[j].numOccur = num1;
			}
		}
	}
}
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

#pragma once
#include <fstream>
#include <ostream>
#include <string>
#include <iostream>
#include <vector>

#define INTER_COMMAND_SPACE "\n\n"
#define TO_BE_DONE "TO BE DONE"
#define CONTENT_HEADER "\t - "


class File {
private:
	std::string name;
	std::string fileName;
	std::string mainPrompt = "What would you like to do? Only input the number next to the action you'd like to perform:\n1) Add content to the list\n2) Delete all content of list\n3) View list\n4) Delete an entry\n5) Help\n6) Exit";
	std::vector<std::string> listContents;


	void printPrompt() {
		std::cout << this->mainPrompt << std::endl;
	}


	void createFile() {
		std::ofstream writing;
		writing.open(this->fileName, std::ios_base::in);
		if (writing.is_open()) {
			writing << name;
			writing << "" << std::endl;
		}
		writing.close();
		
	}

	void getEntries() {
	
		std::ifstream reading;
		std::string entry;
		reading.open(this->fileName, std::ios_base::in);
		std::vector<std::string> listOfEntries;
		if (reading.is_open()) {
			while (reading.good()) {
				getline(reading, entry);
				listOfEntries.push_back(entry);
			}
		}
		listContents = listOfEntries;
		reading.close();
	}


	
	void presentEntries() {
		std::cout << "Which entry would you like to remove?" << std::endl;
		
		for (int i = 0; i < listContents.size(); i++) {
			if (!(listContents[i].compare("\n") == 0 || listContents[i].compare(this->name) == 0)) {
				std::cout << "Entry " << i << ": " << listContents[i] << std::endl;
			}
		}
	}

	//Assumes that the entries displayed to the user are i + 1
	void deleteEntry(int entry) {
		std::ofstream writing;
		listContents.erase(listContents.begin() + entry);
		writing.open(this->fileName, std::ios_base::trunc | std::ios_base::out);
		if (writing.is_open()) {
			for (int i = 0; i < listContents.size(); i++) {
				writing << listContents[i] << std::endl;
			}
		}


		writing.close();
	}

	
	void viewAllLists() {
		std::ifstream reading;
		std::string placeHolder;
		reading.open(this->fileName, std::ios_base::in);
		if (reading.is_open()) {
			while (reading.good()) {
				getline(reading, placeHolder);
				std::cout << placeHolder << std::endl;
			}
		}

		reading.close();
		std::cout << INTER_COMMAND_SPACE << std::endl;
		printPrompt();

	}

	void deleteContentsOfList() {
		std::ofstream writing;
		writing.open(this->fileName, std::ios_base::trunc);
		std::cout << INTER_COMMAND_SPACE << std::endl;
		std::cout << "Contents deleted..." << std::endl;
		std::cout << INTER_COMMAND_SPACE << std::endl;
		printPrompt();
		writing.close();
	}

	void addContentToList() {
		std::string input;
		std::cout << "What would you like to add? Only add one line at a time: ";
		getline(std::cin, input);
		puts(""); // skips a line
		 
		std::ofstream writing;
		writing.open(this->fileName, std::ios_base::app | std::ios_base::ate);

		if (writing.is_open()) {
			writing << CONTENT_HEADER << input << std::endl;
		}
		writing.close();
	}

	void help() {
		std::cout << "Make sure you enter everything correctly... " << std::endl;
	}

public:

	File(std::string name) {
		this->fileName = name + ".txt";
		this->name = name;
		createFile();
		printPrompt();
	}

	File() {
		this->name = "???";
		this->fileName = "noName.txt";
		createFile();
		printPrompt();
	}

	std::string getUserInput() {
		std::string input;
		getline(std::cin, input);
		return input;
	}

	// Will return false if the user decides to stop, else will return true if the user wants to continue
	bool handleMainCommand(std::string cmd) {
		int userInput = std::stoi(cmd);

		switch(userInput){
		case 1:
			//Add content to the list.
			addContentToList();
			std::cout << INTER_COMMAND_SPACE << std::endl;
			printPrompt();
			return true;
		case 2:
			//Delete All content from list
			deleteContentsOfList();
			return true;
		case 3:
			//View contents of list
			viewAllLists();
			return true;
		case 4:
			//Delete an entry
			std::cout << INTER_COMMAND_SPACE << std::endl;
			
			getEntries();
			presentEntries();
			int userInput;
			std::cin >> userInput;
			deleteEntry(userInput);
			std::cout << INTER_COMMAND_SPACE << std::endl;
			printPrompt();
			return true;
		case 5:
			//Help
			help();
			return true;
		case 6:
			// Exit
			std::cout << "Leaving . . . " << std::endl;
			return false;
		default:
			std::cout << "Unrecognized command; enter '5' for help." << std::endl;
			std::cout << INTER_COMMAND_SPACE << std::endl;
			printPrompt();
			return true;
		}
	}
};

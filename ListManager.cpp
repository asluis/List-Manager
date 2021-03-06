

#include "stdafx.h"
#include <iostream>
#include "File.h"
#include <string>

std::string getFile();
bool checkIfValid(std::string fileName);


int main(){
	std::string userInput;
	std::string fileToOpen = getFile();
	File file(fileToOpen);

	getline(std::cin, userInput);
	
	while (file.handleMainCommand(userInput)) {
		userInput = file.getUserInput();
	}
    return 0;
}

std::string getFile() {
	std::cout << "Enter the name of the file you wish to open/create. \nPlease DO NOT include any filename extensions such as .txt or any dots" << std::endl;
	std::string fileName;
	getline(std::cin, fileName);

	while (checkIfValid(fileName)) {
		std::cout << "Please enter a valid name. Remeber, no dots are allowed: ";
		getline(std::cin, fileName);
		puts("");
	}
	return fileName;
}

bool checkIfValid(std::string fileName) {
	for (int i = 0; i < fileName.length(); i++) {
		if (fileName.at(i) == '.') {
			return true;
		}
	}
	return false;
}
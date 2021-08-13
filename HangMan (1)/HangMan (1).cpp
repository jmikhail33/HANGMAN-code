// HangMan (1).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

// this function draws the game bars. drawTop determines if and drawbottom doeslskdjvbsldkfhb
void drawGame(string title, bool drawTop = true, bool drawBottom = true)
{
	if (drawTop) {
		cout <<"\t"<<" H~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~H" << endl;
		cout <<"\t"<<" |";
	}
	else {
		cout << "\t" << " |";
	}

	bool beforeTitle = true;
	for (int i = title.length(); i < 55; i++) {
		if (beforeTitle) {
			title = " " + title;
		}
		else {
			title = title + " ";
		}
		beforeTitle = !beforeTitle;
	}
	cout << title.c_str();


	if (drawBottom) {
		cout << " |" << endl;
		cout << "\t" << " H~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~H" << endl;
	}
	else {
		cout << " |" << endl;
	}


}

void drawHangMan(int numOfGuesses = 0) {

	if (numOfGuesses >= 1) {
		drawGame("|", false, false);
	}
	else {
		drawGame("", false, false);
	}
	if (numOfGuesses >= 2) {
		drawGame("|", false, false);
	}
	else {
		drawGame("", false, false);
	}
	if (numOfGuesses >= 3) {
		drawGame("0", false, false);
	}
	else {
		drawGame("", false, false);
	}
	if (numOfGuesses == 4) {
		drawGame("|", false, false);
	}
	if (numOfGuesses == 5) {
		drawGame("/| ", false, false);
	}
	if (numOfGuesses > 5) {
		drawGame("/|\\", false, false);
	}
	if (numOfGuesses >= 7) {
		drawGame("|", false, false);
	}
	if (numOfGuesses == 8) {
		drawGame("/  ", false, false);
	}
	if (numOfGuesses > 8) {
		drawGame("/ \\", false, false);
		drawGame("DIED :/", false, false);
	}
}

void displayLetters(string Input, char start, char end) {

	string charFound;
	for (char i = start; i <= end; i++) {
		if (Input.find(i) == string::npos) {
			charFound += i;
			charFound += " ";
		}
		else {
			charFound += "_ ";
		}

	}
	drawGame(charFound, false, false);
}

void displayAvailableLetters(string userChoice) {
	displayLetters(userChoice, 'A', 'M');
	displayLetters(userChoice, 'N', 'Z');
}

bool checkTheWord(string actualWord, string userGuess) {
bool userStatus = true;
string collector;
	for (int i = 0 ; i < actualWord.length(); i++) {
		if (userGuess.find(actualWord[i]) != string::npos) {
			collector += actualWord[i];
			collector += " ";
			userStatus = true;
		}
		else {
			collector += " _ ";
			userStatus = false;
		}
	}
	drawGame(collector, false);
	return userStatus;
}

string Reading (string fileName) {
	vector <string> randomVector;
	string line;
	string choosenString;
	
	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open()) {
		while (getline(myFile, line))
		{
			randomVector.push_back(line);
		}
	srand(time(0));
	int randomNumber = rand() % randomVector.size();
	choosenString = randomVector.at(randomNumber);
	myFile.close();
	}
	return choosenString;
}



int userTrials(string actualWord, string userGuess) {
	int userErrors = 0;
	for (int i = 0; i < userGuess.length(); i++){
		if (actualWord.find(userGuess[i]) == string::npos) {
			userErrors +=1;
		}
	}
	return userErrors;

}




int main()
{
	int trials = 0;
	char xInput;
	string userGuess;
	string secretWord;
	string Hint;
	vector <string> wordAndHint;
	string inputtedGuess;
	bool userBool = false;
	secretWord = Reading("gameWords.txt");
	Hint = Reading("gameHints.txt");

	do {
		system("cls");
		drawGame("HANG MAN");
		drawHangMan(trials);
		drawGame("Letters to choose from:");
		displayAvailableLetters(inputtedGuess);
		drawGame("Guess");
		drawGame("Hint:",false,false);
		drawGame(Hint, false);
		userBool = checkTheWord(secretWord, inputtedGuess);

		if (userBool) {
			break;
		}

		cout << " >> ";
		cin >> xInput;
		xInput = toupper(xInput);

		if (inputtedGuess.find(string (1,xInput)) == string::npos) {
			inputtedGuess += string(1, xInput);
		}
		
		trials = userTrials(secretWord, inputtedGuess);
	} while (trials < 10);

	if (userBool) {
		drawGame("YOU WON!", false);
	}
	else {
		drawGame("GAME OVER!",false);
	}
	system("pause>0");
}


/* Hangman

The main objective is to make a hangman game with a text file for words

Made by Dominykas

*/

#include <iostream>  //Common
#include <fstream>   //File manipulation
#include <time.h>    //Time for random word
#include <stdlib.h>  //For rand

using namespace std;

//Gets a list of words from a text file and stores them in words string array
void getWords(string words[], int &wordCount){
	ifstream in("words.txt");
	for(int i = 0;!in.eof(); i++){
		in >> words[i];
		wordCount += 1;
	}
	wordCount -= 1; //Because it reads '\n'
	in.close();
}

//Uses time to select a random word from the word string array and returns a word
string selectWord(string words[], int wordCount){
	srand(time(NULL));
	int randNum = rand() % wordCount;
	return words[randNum];
}

//Sets the unknown word as 0000 symbols
string setUnknownWord(string word){
	string unkWord = "";
	for(int i = 0; i < word.length(); i++){
		unkWord += "0";
	}
	return unkWord;
}

//Displays a menu after a guess and at the very start
string guessMenu(string word, int lives, string unkWord, string &guess){
	cout << "The word is " << word.length() << " characters long." << endl;
	cout << "You have " << lives << " lives" << endl;
	cout << unkWord << endl;
	cout << endl;
		
	cout << "Guess: ";
	cin >> guess;
	
	return guess;
}

//Checks if the letter or whole word is either correct or incorrect
//If the whole word guess is correct or the final letter is correct, you set the gamestate to win
string checkGuess(string word, string &unkWord, string guess, string &gamestate){
	for(int i = 0; i < word.length(); i++){
		//If the guess is the whole word
		if(guess.length() > 1){
			if(guess == word){
				gamestate = "win";
				unkWord = guess;
			}else{
				gamestate = "incorrect";
			}
			return gamestate;
		}
		//Checks the letter
	    if(guess[0] == word[i]){
			//Sets the unknown's word's character to a letter (example: 0 -> i)
			unkWord[i] = word[i];
			gamestate = "correct";
			//If every letter is guessed allready then win the game
			if(unkWord == word){
				gamestate = "win";
				return gamestate;
			}
		}
		//If the last letter of the word is checked and there was a correct guess, return the gamestate
		if(gamestate == "correct" && i+1 >= word.length()){
			return gamestate;
		}
	}
	//If something unexpected happened or the letter was incorrect, return the gamestate
	gamestate = "incorrect";
	return gamestate;
}

//Prints what happens after the guess
void gamestateResolve(string gamestate, int &lives, string word){
	if(gamestate == "win"){
		cout << "You win!" << endl;
		cout << "The word was: " << word << endl;
		cout << "You had " << lives << " lives left" << endl;
	}else if(gamestate == "correct"){
		cout << "You are correct!" << endl;
		cout << endl;
	}else if(gamestate == "incorrect"){
		lives -= 1;
		cout << "You are incorrect!" << endl;
		cout << endl;
	}else{
		//If something unexpected happens
		cout << "You lose!" << endl;
		cout << "The word was: " << word << endl;
		lives = 0;
	}
	if(lives <= 0){
		cout << "You lose!" << endl;
		cout << "The word was: " << word << endl;		
	}
}

//Main loop of the game
void game(string word, string &unkWord, int lives, string &gamestate){
	string guess = "";
	while(lives > 0){
		guess = guessMenu(word, lives, unkWord, guess);                  //Prints the guess menu
		gamestate = checkGuess(word, unkWord, guess, gamestate);         //Checks if the guess is correct
		gamestateResolve(gamestate, lives, word);                        //Prints the result of the guess
		if(gamestate == "win"){
			break;
		}
		gamestate = "lose";
	}
}

int main(){
	string words[100000];        //All words are stored here
	int wordCount = 0;           //Ammount of words
	string gamestate = "lose";   //Sets the player to lose
	int lives = 10;              //Ammount of guessed allowed
	
	getWords(words, wordCount);
	string word = selectWord(words, wordCount);  //The random word we need to guess
	string unkWord = setUnknownWord(word);       //The random word in 0000 format

	game(word, unkWord, lives, gamestate);       //Main loop of the game

	return 0;
}

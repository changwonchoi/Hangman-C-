////////////////////////////////////////////////////////////////////////////////
// File Name:      C++ Project.cpp
//
// Author:         Chang Won Choi, Matthew Derzay
// CS email:       cchoi25@wisc.edu, Mderzay@wisc.edu
//
// Description:    Basic Hangman game. The user1 chooses word, and user2
//		   guesses the word. User2 gets 5 tries.
//
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>

/**
 * A class for the game
 */
class Game {
        public:
                void printBoard(std::vector<char> badGuesses, std::vector<int> goodGuesses, std::string word);
                bool CheckDoubles(char guess, std::vector<char> allGuesses);
                bool win(std::vector<int> goodGuesses, std::string word);
                bool lose(std::vector<char> badGuesses);
                bool CheckGuess(char guess, std::string word);
		void ValGuess(char& c);
		void ValWord(std::string& word);
                int main();
                Game();
};

Game() {

}

int Game::main() {
        Game game;
        std::vector<char> badGuesses;
        std::vector<char> allGuesses;
        std::vector<int> goodGuesses;
        std::string word;
        int wrongGuesses = 0;
        char guess;

        std::cout << "Welcome to Hangman" << std::endl;
        std::cout << "------------------" << std::endl;
        std::cout << "Please choose a word without space or special characters: ";
        std::cin >> word;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	//Change the word to lower case.

        for(int i = 0; i < word.size(); ++i) {
                goodGuesses.push_back(0);
		//fill goodGuesses with 0;
        }

        game.ValWord(word);
	//check if the word is good.

        while(!game.win(goodGuesses, word) && !game.lose(badGuesses)) {
                game.printBoard(badGuesses, goodGuesses, word);

                std::cout << "Please Enter a One Character Guess: ";
                std::cin >> guess;
		guess = tolower(guess);
                //While not double or valid guess.

		game.ValGuess(guess);
		//check if the guess is valid.

                while(game.CheckDoubles(guess, allGuesses)) {
                        std::cout << "Invalid Guess, Please Try Again: ";
                        std::cin >> guess;
			game.ValGuess(guess);
                }
		//if the user guessed same letter again reprompt the user.

                if(game.CheckGuess(guess, word)) {
                        for(int i = 0; i < word.size(); ++i) {
                                if(guess == word.at(i)) {
                                        goodGuesses.at(i) = 1;
					//if the guess is correct, put 1 in correspinding spot.
                                }
                        }
                        allGuesses.push_back(guess);
			//add it to allGuesses.
                }else{
                        badGuesses.push_back(guess);
                        allGuesses.push_back(guess);
			//add it to allGuesses and badGuesses.
                }
        }
        if(game.win(goodGuesses, word)) {
                std::cout << "\nYOU WIN!" << std::endl;
                game.printBoard(badGuesses, goodGuesses, word);
        }else{
                std::cout << "\nYOU LOSE!" << std::endl;
                game.printBoard(badGuesses, goodGuesses, word);
		std::cout << "The word was: " << word << std::endl;
        }
        return 1;
}


/**
 * @brief A method to print the board.
 *
 * @param badGuess A char vector containing the bad guesses.
 * 
 * @param goodGuess A int vector containing info for good guesses.
 *
 * @param word The actual word that the user2 has to guess. 
 *  
 */
void Game::printBoard(std::vector<char> badGuesses, std::vector<int> goodGuesses, std::string word) {
	//draws different board depending on the number of bad guesses.
        switch(badGuesses.size()) {
                case 0:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
                case 1:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|     O  " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
                case 2:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|     O  " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
                case 3:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|     O  " << std::endl;
                        std::cout << "|    <|> " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
                case 4:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|     O  " << std::endl;
                        std::cout << "|    <|> " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|        " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
		case 5:
                        std::cout << "-------- " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|     O  " << std::endl;
                        std::cout << "|    <|> " << std::endl;
                        std::cout << "|     |  " << std::endl;
                        std::cout << "|    ( ) " << std::endl;
                        std::cout << "|________" << std::endl;
                        break;
        }
	//if a letter of the word is not guessed yet, print "_ "
        std::cout << "" << std::endl;
        for(int i = 0; i < word.size(); ++i) {
                if(goodGuesses.at(i) == 0) {
                        std::cout << "_ ";
                }else{
                        std::cout << word.at(i) << " ";
                }
        }
        std::cout << "\n" << std::endl;
	//show all the wrong guesses
        std::cout << "Wrong Guesses: ";
        for(int i = 0; i < badGuesses.size(); ++i) {
                std::cout << badGuesses.at(i) << ", ";
        }
        std::cout << "\n" << std::endl;
}

/**
 * @brief A method that checks if the user guessed same letter twice.
 *
 * @param guess The user's guess.
 *
 * @param allGuesses A char vector containing all the guesses.
 *
 * @return bool true if the user guessed same letter again false otherwise.
 *
 */
bool Game::CheckDoubles(char guess, std::vector<char> allGuesses) {
	//checks if the guess is in allGuesses
        for(int i = 0; i < allGuesses.size(); ++i) {
                if(guess == allGuesses.at(i)) {
                        return true;
                }
        }
        return false;
}

/**
 * Determines if the user2 won the game.
 *
 * @param goodGuesses A int vector containing info for good guesses.
 * ..
 * @param word The word that user2 has to guess
 * 
 * @return true if all the items in the goodGuesses are not 0, false otherwise
 */
bool Game::win(std::vector<int> goodGuesses, std::string word) {
	//checks all the values in goodGuesses
        for(int i = 0; i < goodGuesses.size(); ++i) {
                if(goodGuesses.at(i) == 0) {
                        return false;
                }
        }
        return true;
}

/**
 * @brief Determines whether or not the user2 lost.
 *
 * @param badGuesses A char vector containing all the bad guesses.
 * 
 * @return true if badGuess's size if over 5.
 */
bool Game::lose(std::vector<char> badGuesses) {
        if(badGuesses.size() >= 5) {
                return true;
        }
        return false;
}

/**
 * @brief Checks whether or not the guess is correct.
 *
 * @param guess User2's guess.
 * ..
 * @param word The word that user2 has to guess.
 * 
 * @return true if the guess matches one of the letters in word. 
 */
bool Game::CheckGuess(char guess, std::string word) {
	//traverse through the word to see if guess is correct.
        for(int i = 0; i < word.size(); ++i) {
                if(guess == word.at(i)) {
                        return true;
                }
        }
        return false;
}

/**
 * @brief Checks if the guess is alphabet. Prompts the user to guess
 *	  again if the guess is not alphabet.
 *
 * @param c calls the reference of c, so that c can change. c is the user's guess.
 */
void Game::ValGuess(char& c) {
	//variable to check if valid of not.
	bool valid = false;
	while (!valid) {
	//checks if c is alplabet of not
		if (!isalpha(c)) {
			std::cout << "Invalid guess. Please type a character: ";
			std::cin >> c;
			tolower(c);
		}
		else {
		valid = true;
		}
	}
}

/**
 * @brief Checks if the word is consist of alphabets. Prompts the user to type again
 * 	  if it is not.
 *
 * @param word calls the reference of word, so that word can change.
 * 	       The word is given by user1.
 */

void Game::ValWord(std::string& word) {
	//variable to check if the word is valid.
	bool valid = false;
	while (!valid) {
		int i = 0;
		//variable to check if the word has non alphabet.
		bool err = false;
		while (i < word.length() && !err) {
			if (!isalpha(word[i])) {
			err = true;
			}
			i++;
		}
		if (err) {
			//if error is found, reprompt the user.
			std::cout << "Invalid word. Words with only alphabets are allowed: ";
			std::cin >> word;
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		}
		else {
			valid = true;
		}
	}
}

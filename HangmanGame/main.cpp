#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <vector>
#include "graphics.h"

using namespace std;

vector<string> words;
int attempts_left = 6;


int main() {

	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	srand(time(0));

	initAsciiVectors();

	ifstream dictionary("dictionary.txt");
	while (!dictionary.eof())
	{
		string word;
		getline(dictionary, word);
		transform(word.begin(), word.end(), word.begin(), ::toupper);
		words.push_back(word);
	}
	dictionary.close();
	
	string selected_word = words[rand() % words.size()];
	string display_word = "";
	for (char letter : selected_word)
	{
		if (letter == ' ' || letter == '-')
		{
			display_word.push_back(letter);
		}
		else {
			display_word.push_back('_');
		}
	}

	while (attempts_left > 0 && display_word != selected_word)
	{
		for (int i = 0; i < display_word.size(); i++)
		{
			cout << display_word[i] << " ";
		}
		cout << "\nВведите букву: ";
		string input;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		bool guessed = false;

		for (int i = 0; i < selected_word.size(); i++) {
			if (selected_word[i] == input[0]) {
				display_word[i] = input[0];
				guessed = true;
			}
		}
		if (!guessed) {
			attempts_left--;
		}
		printLevel(attempts_left);
	}
	
	if (attempts_left == 0) {
		cout << "Вы проиграли!";
		cout << "Загаданное слово: " << selected_word;
	}
	else {
		cout << "Поздравляем! Вы выиграли!";
	}

	
	
}
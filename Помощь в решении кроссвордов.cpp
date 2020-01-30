#include <iostream>
#include <math.h>
#include <fstream>
#include <windows.h>
using namespace std;

//программа работает только с упорядоченными по длине слов словарями

int factorial(int i) {
  if (i == 0) return 1;
  else return i * factorial(i - 1);
}

int variations(int n, int k) {
	return factorial(n) / factorial(n - k);
}

int str_length(int n, char str[]) {
	int amountOfSymbol = 0;
	while (str[amountOfSymbol] != '\0') {
		amountOfSymbol++;
	}
	return amountOfSymbol;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	ifstream fin;
	ofstream fout;
	/*	
	fin.open("input1.txt");
	int vocabular_size = 5000;
*/
/*	fin.open("input2.txt");
	int vocabular_size = 67775;
*/
	fin.open("input4.txt");
	int vocabular_size = 125723;
	
	int words_area[25];
	char tw1[25] = "", tw2[25] = "";
	fin.getline(tw1, 25);
	int j = 0;
	for(int i = 1; i < vocabular_size; i++) {
		fin.getline(tw2, 25);
		if(str_length(25, tw1) != str_length(25, tw2)) {
			words_area[j] = i;
			j++;
		}
		for(int j = 0; j < 25; j++) {
			tw1[j] = tw2[j];
		}
	}

	fout.open("output.txt");

//start_with_new_allowed_letters:
	int n_other_letters;
	cout << "Enter the number of all allowed letters: (if all letters are allowed to use >= 1 times, you should type 66)" << endl;
	cin >> n_other_letters;
	char other_letters[n_other_letters];
/*
а б в г д е ё ж з и й к л м н о п р с т у ф х ц ч ш щ ъ ы ь э ю я
*/
	cout << "Enter all allowed letters: (if all letters are allowed to use >= 1 times, you should type all alphabet 2 times)" << endl;
	for(int i = 0; i < n_other_letters; i++) {
		cin >> other_letters[i];
	}
	
	char repeated_letters[n_other_letters] = "";
	int n_repeated_letters = 0;
	for(int m = 0; m < n_other_letters; m++) {
		for(int mn = m + 1; mn < n_other_letters; mn++) {
			if(other_letters[m] == other_letters[mn]) {
				repeated_letters[n_repeated_letters] = other_letters[m];
				n_repeated_letters++;
			}
		}
	}
	for(int mni = n_repeated_letters; mni < n_other_letters; mni++) {
		repeated_letters[mni] = '\0';
	}
			
//	cout << "repeated letters are " << repeated_letters << endl;
	char answer = 's';
	int temp, n_word, n_known;
	
	do {
		fin.clear();
		fin.seekg(0, ios::beg); // ставим указатель на начало файла, чтобы прочитать еще раз
		
		cout << "Enter the number of letters in a word:" << endl;
		cin >> n_word;
		char word[n_word];
	 
		cout << "Enter the number of known letters in a word:" << endl;
		cin >> n_known;
		int known_places[n_known];

		if(n_known > 0) {
			char known_letters[n_known];
			cout << "Enter known letters and their places in a word:" << endl;
			for(int i = 0; i < n_known; i++) {
				cin >> known_letters[i];
				cin >> known_places[i];
				word[known_places[i] - 1] = known_letters[i];
			}
		}
	
		cout << endl;
		if(n_other_letters <= 15) {
			int poss_words = variations(n_other_letters - n_known, n_word - n_known);
			cout << "There are " << poss_words << " possible words" << endl;
		}

		int sum = 0, temp_sum = 0;
		char temp_word[25];
		for(int i = 0; i < words_area[n_word - 2]; i++) {
			fin >> temp_word;
		}
		
		if(n_repeated_letters > 1) {
			cout << "Choose wisely, some words may be incorrect (-:" << endl;
		}
		
		for(int i = words_area[n_word - 2]; i < words_area[n_word - 1]; i++) {
			fin >> temp_word;
			for(int j = 0; j < n_known; j++) {
				if(word[known_places[j] - 1] == temp_word[known_places[j] - 1] ) {
					temp_sum = temp_sum + 1;
				}		
			}
			if(temp_sum == n_known and
			temp_word[n_word] == '\0' and temp_word[n_word - 1] != '\0') {
				for(int k = 0; k < n_word; k++) {
					for(int l = 0; l < n_other_letters; l++) {
						if(temp_word[k] == other_letters[l]) {
							sum = sum + 1;
							break;
						}
					}	
				}
				if(sum == n_word) {
					char temp_repeated_letters[n_word] = "";
					int temp_repeated = 0;	
					for(int m = 0; m < n_word; m++) {
						for(int mn = m + 1; mn < n_word; mn++) {
							if(temp_word[m] == temp_word[mn]) {
								temp_repeated_letters[temp_repeated] = temp_word[m];
								temp_repeated++;
							}
						}
					}
					for(int mni = temp_repeated; mni < n_word; mni++) {
							temp_repeated_letters[mni] = '\0';
					}
					if(temp_repeated == 0) {
						fout << temp_word << endl;
						cout << temp_word << endl;
					} 
					if(n_repeated_letters == 1 and temp_repeated == 1 and repeated_letters[0] == temp_repeated_letters[0]) {
						fout << temp_word << endl;
						cout << temp_word << endl;
					}
					if(n_repeated_letters > 1) {
						fout << temp_word << endl;
						cout << temp_word << endl;
					}
				}
			}
			temp_sum = 0;
			sum = 0;
		}
	
		cout << endl;
		cout << "Would you like to continue?" << endl;
		cout << "Press Y/Д to start with new word or any other button to end" << endl;
		cin >> answer;
		cout << endl << endl;
	}
	while (answer == 'д' or answer == 'y');
	
	fout.close();
	fin.close();
	
	return 0;
}



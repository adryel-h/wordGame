#include "UserInterface.h"

void UserInterface::printtrans(vector<string> final) {
	/**
	* @param final - a string vector
	* 
	* If there exists a solution it prints on the screen the transformations the computer has made starting from the startword and ending at the targetword
	* otherwise it prints that there is no solution
	**/
	if (final.size() != 0) {
		cout << " Move 0: " << final[final.size() - 1] << "\n";
		for (int i = final.size() - 2; i >= 0; i--) {
			cout << " Move " << final.size() - i - 1 << ": " << final[i] << "\n";
		}
	}
	else cout << " There exists no solution! ";
	cout << "\n\n";
}

void UserInterface::load() {
	/**
	* This function manages the computer-user interaction part of the program
	**/
	cout << " ~ WORD PUZZLE GAME ~ \n"<<" based on Lewis Carroll's puzzle game invented in the 19th century\n\n";
	string menu = " SELECT ACTION:\n 1. Automatic mode\n 2. Playing mode\n 3. User data\n 0. Exit\n";
	string automod = "\n Welcome to Automatic mode. Here you type in two words of the same length and you let the computer\n find the optimmal transformations! \n";
	string playermod = "\n Welcome to Playing mode. Here you select the number of letters for a word and a word of that\n length and the computer will give you a target word that you have to reach by\n doing transformations 1 letter at a time.\n By typing during the game:\n 0 - you will exit the game mode\n 1 - you will recieve a hint \n ";
	int pt, at;
	pt = at = 0;
	Controler control;
	Verify funct{control.getaddressdict()};
	Analytics datasaver;
	int operation = 1;
	while (operation) {
		cout << menu<<"\n";
		cin >> operation;
		if (operation == 1) {
			at++;
			string startword, targetword;
			int* moves = new int;
			if (at == 1)
				cout << automod;
			cout << "\nType the starting word! \n";
			cin >> startword;
			while (!funct.validstart(startword)) {
				cout << "\nPlease introduce a valid word from the english language! \n";
				cin >> startword;
			}
			cout << "\n Type the target word! \n";
			cin >> targetword;
			while (!funct.validtarget(targetword, startword.size())) {
				
				cout << "\nThe target word must be an existent word from the english language and of the same length\n as the starting word. Try again: \n ";
				cin >> targetword;
			}
			vector<string> transformations = control.AutomaticMode(startword, targetword, moves);
			cout << "\n TOTAL MOVES: " << *moves<<"\n";
			printtrans(transformations);
			delete moves;
		}
		else {
			if (operation == 2)
			{
				pt++;
				if (pt == 1)
					cout << playermod;
				string username, startword, targetword;
				vector<string> hintwords, usedwords;
				int size, diff, usermoves = 0, hints = 0;
				int* compmoves = new int;
				cout << "\n Type your first name! \n";
				cin >> username;
				cout << "\n Type the number of letters for the word! \n";
				cin >> size;
				while (!funct.validsize(size)) {
					cout << "\n Type a positive integer! \n";
					cin >> size;
				}
				cout << "\n Select difficulty level (type number) :\n 1. Easy\n 2. Medium\n 3. Hard\n 4. Impossible\n\n ";
				cin >> diff;
				startword = control.getStart(size);
				targetword = control.getTarget(startword,diff);
				cout << "\n Your start word is: " << startword << "\n";
				cout << "\n Your target word is: " << targetword<<"\n";
				hintwords = control.AutomaticMode(startword, targetword, compmoves);
				string prevword = startword, curword = startword;
				bool play = true;
				auto start = std::chrono::system_clock::now();
				std::time_t game_time = std::chrono::system_clock::to_time_t(start);
				string time_at_b =  std::ctime(&game_time);
				while (curword != targetword and play) {
					cout << "\n type the next word! (target word: "<<targetword<<")\n\n";
					cin >> curword;
					while (!funct.validmove(prevword, curword)) {
						cout << "\n Invalid move! Try again or type 1 for a hint (current word: "<<prevword<<") \n\n";
						cin >> curword;
					}
					if (curword == "0") {
						play = false;
					}
					else {
						if (curword == "1") {
							hints++;
							int pos = control.getHint(prevword, targetword, hintwords);
							curword = prevword;
							cout << "\n You should try: ";
							for (int i = 0; i <= curword.length(); i++) {
								if (i == pos)
									cout << "\033[32m" << curword[i] << "\033[39m";
								else
									cout << curword[i];
							} cout << "\n";
						}
						else {
							usermoves++;
							usedwords.push_back(curword);
							prevword = curword;
						}
					}
				}
				auto end = std::chrono::system_clock::now();
				std::time_t gme_time = std::chrono::system_clock::to_time_t(end);
				string time_at_e = std::ctime(&gme_time);
				if (play == true) {
					cout << "\n Well done, you found a solution! \n";
					cout << "\n You did it in " << usermoves << " moves and used " << hints << " hints!\n";
					cout << "\n The computer did it in " << *compmoves << " moves!\n\n";
					int computermoves = *compmoves;
					datasaver.write(username, startword, targetword, time_at_b, time_at_e, hints, usedwords, usermoves, computermoves);
				}
				else {
					cout << "\n You gave up! :( \n\n";
					datasaver.write(username, startword, targetword, time_at_b, time_at_e);
				}
				delete compmoves;
			}
			else {
				if (operation == 3)
				{
					cout << "\n Type the username: \n\n";
					string username;
					cin >> username;
					int uniquewords = datasaver.getUniqueWords(username);
					double procent = datasaver.getExtraData(username);
					if (procent != -1) {
						cout <<"\n "<< username << " has used " << uniquewords << " unique words across all games! \n";
						cout << " " << username << " has completed " << procent << "% of all games started\n\n";

					}
					else {
						cout << "\n User not found! \n\n";
					}
				}
			}
		}
	}
}
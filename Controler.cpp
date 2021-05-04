#include "Controler.h"

Controler::Controler() {
	dict = new Dictionary;
}

string Controler::getStart(int size) {
	/**
	* @param size - an integer representing the size of a word
	* 
	* @return
	* returns a string representing a random word of the choosen length
	**/
	return dict->randomWord(size);
}

string Controler::getTarget(string startword, int diff)
{
	/**
	* @param startword - the starting word
	* @param diff - an integer representing the difficulty
	* 
	* @return
	* returns a string representing the target word which is based on the starting word and the difficulty provided as param.
	* the function always returns a word for which there exists a path from the sword to the tword
	**/
	srand(time(NULL));
	int lvl;
	if (diff == 1) {
		lvl = rand() % 3 + 1;
	}
	else
	{
		if (diff == 2) {
			lvl = rand() % 3 + 3;
		}
		else {
			if (diff == 3) {
				lvl = rand() % 4 + 5;
			}
			else {
				lvl = rand() % 5 + 9;
			}
		}
	}
	Graph graf{ dict->getdict(startword.length())};
	return graf.DFS(startword, lvl);
}

int Controler::getHint(string prevword, string targetword, vector<string>& hintwords) 
{
	/**
	* @param prevword - a string representing the last valid word in the game
	* @param targetword - the target word
	* @param hintwords - a vector of strings containing a path from the startword to the targetword
	* 
	* If the prevword is not found in the hintwords vector, then hintwords gets overwritten with a optimal path from
	* the prevword to the targetword, otherwise hintwords does not get modified
	* 
	* @return
	* returns an integer representing the position in prevword where the user should modify a letter
	**/
	bool helped = false;
	string hint;
	for (int i = hintwords.size() - 1; i >= 0 and !helped; i--) 
		if (hintwords[i] == prevword)
		{
			helped = true;
			hint = hintwords[i - 1];
		}
	if (helped == false) {
		int* st = new int;
		hintwords = AutomaticMode(prevword, targetword, st);
		delete st;
		hint = hintwords[hintwords.size() - 2];
	}
	for (int j = 0; j < hint.length(); j++)
		if (hint[j] != prevword[j])
			return j;
}

vector<string> Controler::AutomaticMode(string startword, string targetword,int* moves) {
	/**
	* @param startword - starting word
	* @param targetword - target word
	* @param moves - a pointer to an integer 
	* 
	* the function modifies the value pointed to by moves to an integer representing the optimal number of moves needed to reach
	* the target word
	* @return
	* The function returns a vector of strings representing the path from the startword to the targetword
	**/
	Graph graf{dict->getdict(startword.length())};
	 return graf.BFS(startword, targetword, moves);
}

Dictionary* Controler::getaddressdict()
{
	/**
	* @return
	* the function returns a pointer to a Dictionary
	**/
	return dict;
}

Controler::~Controler()
{
	delete dict;
}

#include "Analytics.h"

void Analytics::write(string username, string sword, string tword, string start_time, string end_time, int hints, vector<string> words, int usermoves, int compmoves)
{
	/**
	* @param username - a string with the username
	* @param sword - the starting word
	* @param tword - the target word
	* @param start_time - a string containing the starting time of the game
	* @param end_time - a string containing the ending time of the game
	* @param hint - an integer representing the number of hints used
	* @param words - a string vector containing all the words the player used
	* @param usermoves - an integer representing how many moves the user made
	* @param compmoves - an integer representing the optimal number of moves
	* 
	*  The function writes to the file "username.txt" data about a given match
	**/
	of.open("username.txt", fstream::app);
	of << "USERNAME: " << username << "; STARTWORD: " << sword << "; TARGETWORD: " << tword << "; STARTIME: " << start_time << "; ENDTIME: " << end_time << "; HINTS: " << hints<<";";
	of << " WORDS: ";
	for (int i = 0; i < words.size(); i++)
		of << words[i] << " ";
	of << ";";
	of << " USERMOVES: " << usermoves << "; COMPMOVES: " << compmoves<<";\n";
	of.close();
}

void Analytics::write(string& username, string& sword, string& tword, string start_time, string end_time)
{
	/**
	* @param username - a string with the username
	* @param sword - the starting word
	* @param tword - the target word
	* @param start_time - a string containing the starting time of the game
	* @param end_time - a string containing the ending time of the game
	* 
	* The function writes to the file "username.txt" data about a given match
	**/
	of.open("username.txt", fstream::app);
	of << "USERNAME: " << username << "; STARTWORD: " << sword << "; TARGETWORD: " << tword << "; STARTIME: "<<start_time<<"; ENDTIME: "<<end_time<<"ABANDONED_GAME\n";
	of.close();
}

int Analytics::getUniqueWords(string username) {
	/**
	* @param username - string that contains the username
	* 
	* @return
	* the function returns an integer representing the number of unique words the user has used in all games
	**/
	ifstream g("username.txt");
	set<string> uniquewords;
	int i = 1;
	for (std::string line; getline(g, line); )
	{
		if (i % 3 == 1) {
			int pos = line.find(username);
			if (pos != string::npos) {
				getline(g, line);
				getline(g, line);
				if (line.find("ABANDONED_GAME") == string::npos) {
					int res = line.find(";", 17);
					string wds = line.substr(19, res - 20);
					while ((res = wds.find(" ")) != string::npos) {
						string actualword = wds.substr(0, res);
						uniquewords.insert(actualword);
						wds.erase(0, res+1);
					}
					uniquewords.insert(wds);
				}
				i += 2;
			}
		}
		i++;
	}
    return uniquewords.size();
}

double Analytics::getExtraData(string username) {
	/**
	* @param - username
	* 
	* @return
	* the function returns a rational number from 0 to 100 representing the rate of completion that a user has
	* or -1 if the user is not found in the "username.txt" file
	**/
	int nrHints = 0;
	double diff, nraban = 0, nrtotal = 0;
	ifstream g("username.txt");
	int i = 1;
	for (std::string line; getline(g, line);) {
		if (i % 3 == 1) {
			int pos = line.find(username);
			if (pos != string::npos) {
				nrtotal++;
				getline(g, line);
				getline(g, line);
				if (line.find("ABANDONED_GAME") != string::npos)
					nraban++;
				i += 2;
			}
		}
		i++;
	}
	if (nrtotal != 0) {
		diff = (nraban / nrtotal) * 100;
		diff = 100 - diff;
	}
	else 
		diff = -1;
	return diff;
}
#include "Graph.h"

Graph::Graph( unordered_set<string> dict){
	/**
	* This is the constructor of the graph, it assigns the unordered_set of strings a subset of the Dictionary where all words
	* have the same length
	**/
	this->dict = dict;
}

vector<string> Graph::BFS(string startword, string targetword,int* moves) {
	/**
	* @param startword - the starting word
	* @param targetword - the target word
	* @param moves - a pointer to an integer
	* 
	* the function computes the optimal route from the startword to the targetword and assigns the value representing the number of steps
	* to the memory location pointed by moves
	* 
	* @return
	* returns a vector of strings representing the path from the startword to the targetword if it exists.
	* if it doesn't, it returns an empty vector
	**/
	*moves = 0;
	vector<cell> queue;
	vector<string> result;
	queue.push_back({ startword,-1 });
	int index = 0;
	bool found = false;
	string parent,aux;
	while (index < queue.size() and !found) {
		parent = queue[index].first;
		dict.erase(parent);
		for (int i = 0; i < parent.length() and !found; i++) {
			aux = parent;
			for (int j = 0; j < 26 and !found; j++) {
				aux[i] = 'a' + j;
				if (dict.find(aux) != dict.end())
				{
					queue.push_back({ aux, index });
					if (aux == targetword)
						found = true;
				}
			}
		}
		index++;
	}
	if (found == false) {
		return result;
	}
	else {
		string word = queue[queue.size() - 1].first;
		int prev = queue[queue.size() - 1].second;
		while (prev != -1) {
			(*moves)++;
			result.push_back(word);
			word = queue[prev].first;
			prev = queue[prev].second;
		}
		result.push_back(startword);
		return result;
	}
}

void Graph::depth(string word,string* po, int k, int lvl) {
	/**
	* @param word - a word
	* @param po - a pointer to a string
	* @param k - an integer representing the current level
	* @param lvl - an integer representing the desired level
	* 
	* This function is recursive. For a given word, it computes all of it's neighbours (and then removes them from the dictionary)
	* in the graph of the dictionary.
	* It then randomly selects one of the neighbours for which it calls the function depth with k = k+1
	* Once k = lvl or the word has no neighbours, the function stops and that specific word becomes the targetword
	* 
	**/
	*po = word;
	if (k < lvl) {
		vector<string> ngh;
		string aux;
		for (int i = 0; i < word.length(); i++) {
			aux = word;
			for (int j = 0; j < 26; j++) {
				aux[i] = 'a' + j;
				if (dict.find(aux) != dict.end()) {
					ngh.push_back(aux);
					dict.erase(aux);
				}
			}
		}
		if (ngh.size() != 0) {
			srand(time(NULL));
			int lucky = rand() % ngh.size();
			depth(ngh[lucky], po, k + 1, lvl);
		}
	}
}

string Graph::DFS(string startword, int lvl) {
	/**
	* @param startword - the starting word
	* @param lvl - an integer representing a level
	* 
	* @return
	* returns a string representing the targetword
	**/
	string* pt = new string;
	dict.erase(startword);
	depth(startword, pt, 0, lvl);
	string result = *pt;
	delete pt;
	return result;
}

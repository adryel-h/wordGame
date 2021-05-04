#pragma once
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
#include <time.h>
using namespace std;
typedef pair<string, int> cell;
class Graph
{
private:
	unordered_set<string> dict;
public:
	Graph(unordered_set<string> dict);
	vector<string> BFS(string startword, string targetword,int* moves);
	string DFS(string startword, int lvl);
	void depth(string word,string* po, int k, int lvl);
};


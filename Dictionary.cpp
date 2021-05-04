#include "Dictionary.h"


Dictionary::Dictionary() {
    /**
    * This is the constructor of the Dictionary
    * It reads all the words from the "words_alpha.txt" file and adds them to the corresponding set
    * depending on their lengths.
    * the Dictionary class can be seen as a partition of a normal Dictionary where each word belongs to one set
    * and the specific set to which it belongs depends on the length of the word
    **/

    vector<string> aux;
    aux.reserve(3776);
    ifstream file("words_alpha.txt");
    constexpr size_t bufferSize = 1024;
    unique_ptr<char[]> buffer(new char[bufferSize]);
    while (file)
    {
        file.read(buffer.get(), bufferSize);
        aux.push_back(buffer.get());
    }
    string delimiter = "\n", token,temp;
    int delimlen = delimiter.length();
    size_t pos;
    for (int i = 0; i < aux.size(); i++) { 
        pos = 0;
        temp = aux[i];
        while ((pos = temp.find(delimiter)) != string::npos) {
            token = temp.substr(0, pos);
            dict[token.length()].insert(token);
            temp.erase(0, pos + delimlen);
        }
    }


}

unordered_set<string> Dictionary::getdict(int size) {
    /**
    * @param size - integer
    * 
    * @return
    * returns an unordered set of strings representing a subset of the dictionary where all the words have the length size
    **/
    return dict[size];
}

string Dictionary::randomWord(int sizeW) {
    /**
    * @param sizeW - an integer
    * 
    * @return
    * returns a random word from the Dictionary of length sizeW
    **/
    int sizeContainer = dict[sizeW].size();
    srand(time(NULL));
    int lucky = rand() % sizeContainer, pos = 0;
    for (auto it = dict[sizeW].begin(); it != dict[sizeW].end(); ++it)
    {
        if (pos == lucky)
            return *it;
        pos++;
    }
}

bool Dictionary::find(string word)
{
    /**
    * @param word - a word
    * 
    * @return 
    * returns true or false depending on whether word is an actual word from the dictionary
    **/
    if (dict[word.length()].find(word) != dict[word.length()].end())
        return true;
    return false;
}

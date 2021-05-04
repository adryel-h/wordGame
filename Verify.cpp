#include "Verify.h"

Verify::Verify(Dictionary* p)
{
    dict = p;
}

bool Verify::validstart(string word)
{
    /**
    * @param word - a string
    * 
    * @return
    * returns true or false depending on whether word is an actual word from the Dictionary
    **/
    return dict->find(word);
}

bool Verify::validtarget(string word, int length)
{
    /**
    * @param word - a string
    * @param length - an integer representing a size
    * 
    * @return
    * returns true or false depending on whether word is an actual word from the dictionary and if it's size is equal to length
    **/
    if (validstart(word) and word.length() == length)
        return true;
    return false;
}

bool Verify::validsize(int size)
{
    if (size >= 1)
        return true;
    return false;
}

bool Verify::validmove(string prevword, string curword) {
    /**
    * @param prevword - a word
    * @param curword - a string
    * 
    * @return
    * returns true if and only if curword is an actual word from the dictionary obtained by modifying 1 and only 1 letter
    * of prevword
    **/
    if (curword == "1" or curword == "0")
        return true;
    if (!validtarget(curword, prevword.size()))
        return false;
    int nr = 0;
    for (int i = 0; i < curword.size() and nr < 2; i++)
        if (prevword[i] != curword[i])
            nr++;
    if (nr != 1)
        return false;
    return true;
}

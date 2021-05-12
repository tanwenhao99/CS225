/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            auto& vec = dict[word];
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            vec.push_back(word.at(0));
            for (unsigned i = 1; i < word.length(); i++) {
                unsigned j = 0;
                while (j < vec.size()) {
                    if (word.at(i) < vec[j]) {
                        vec.insert(vec.begin() + j, word.at(i));
                        break;
                    }
                    j++;
                }
                if (j == vec.size())
                    vec.push_back(word.at(i));
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto word : words) {
        auto& vec = dict[word];
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        vec.push_back(word.at(0));
        for (unsigned i = 1; i < word.length(); i++) {
            unsigned j = 0;
            while (j < vec.size()) {
                if (word.at(i) < vec[j]) {
                    vec.insert(vec.begin() + j, word.at(i));
                    break;
                }
                j++;
            }
            if (j == vec.size())
                vec.push_back(word.at(i));
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> ret;
    auto itr = dict.find(word);
    if (itr == dict.end())
        return ret;
    auto str1 = itr->second;
    for (auto& pair : dict) {
        auto str2 = pair.second;
        if (str1.size() == str2.size()) {
            bool flag = true;
            for (unsigned i = 0; i < str1.size(); i++) {
                if (str1[i] != str2[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                ret.push_back(pair.first);
        }
    }
    return ret;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for (auto& word : dict) {
        bool flag = false;
        for (auto& vec : ret) {
            if (find(vec.begin(), vec.end(), word.first) != vec.end()) {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        auto anagram = get_anagrams(word.first);
        if (anagram.size() > 1) 
            ret.push_back(anagram);
    }
    return ret;
}

// POS Tagger 
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <regex>

using namespace std;


vector<string> tokenize(const string &text) {
    vector<string> words;
    stringstream ss(text);
    string word;

    unordered_set<string> abbreviations = {"Mr.", "Dr.", "U.S.", "Ph.D.", "e.g.", "i.e."};
    while (ss >> word) {

        if (!abbreviations.count(word) && ispunct(word.back())) {
            word.pop_back();
        }
        words.push_back(word);
    }

    return words;
}


string determinePOSTag(const string &word, const string &prevWord) {

    regex pastTenseVerb(".*ed$");   
    regex gerundVerb(".*ing$");     
    regex pluralNoun(".*s$");       
    
    if (regex_match(word, pastTenseVerb)) return "VBD";  
    if (regex_match(word, gerundVerb)) return "VBG";     
    if (regex_match(word, pluralNoun)) return "NNS";    
    
    if (prevWord == "a" || prevWord == "an" || prevWord == "the") return "NN";

    if (isupper(word[0]) && prevWord != "") return "NNP";

    if (word == "is" || word == "was" || word == "are") return "VBZ";

    return "NN";  
}

int main() {
    ifstream file("dictionary.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string text, line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    vector<string> words = tokenize(text);
    vector<pair<string, string>> taggedWords;
    
    string prevWord = "";
    for (const string &word : words) {
        string posTag = determinePOSTag(word, prevWord);
        taggedWords.push_back({word, posTag});
        prevWord = word;  
    }

    cout << "POS Tagged Text:\n";
    for (const auto &tagged : taggedWords) {
        cout << tagged.first << "/" << tagged.second << " ";
    }
    cout << endl;

    return 0;
}

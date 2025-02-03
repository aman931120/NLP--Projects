#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>

using namespace std;

string removePunctuation(const string &word) {
    string cleanWord;
    for (char ch : word) {
        if (isalpha(ch)) {
            cleanWord += ch;
        }
    }
    return cleanWord;
}

bool containsConsecutiveVowels(const string &word) {
    regex vowelPattern("[aeiouAEIOU]{2}");  
    return regex_search(word, vowelPattern);
}

void findWordsWithConsecutiveVowels(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        string cleanWord = removePunctuation(word);
        if (containsConsecutiveVowels(cleanWord)) {
            cout << cleanWord << endl;  
        }
    }
    file.close();

}

int main() {
    findWordsWithConsecutiveVowels("dictionary.txt");
    return 0;
}

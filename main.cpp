#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "BST.h"

using namespace std;

struct ComparePairFirst {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) const {
        return a.first > b.first; // Sort in ascending order based on the first element (Hamming distance)
    }
};

bool isASCII(const string& word) {
    for (char c : word) {
        if (static_cast<unsigned char>(c) > 127) {
            return false; // Non-ASCII character found
        }
    }
    return true; // All characters are ASCII
}

// Function to compute Hamming Distance between two strings
int hammingDistance(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    int minLength = min(len1, len2);
    int distance = max(len1, len2) - minLength;

    for (int i = 0; i < minLength; ++i) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            ++distance;
        }
    }

    return distance;
}

int dictionaryWordCount(BST<string> * d[26])
{
    int counter = 0;
    for (int i = 0; i < 26; i++)
    {
       counter+= d[i]->inorderTraversal().size();
    }
    return counter;
}

int main() {
    BST<string>* dictionary[26] = { nullptr }; // Initialize all pointers to nullptr

    // Initialize BST objects for each alphabet
    for (int i = 0; i < 26; ++i) {
        dictionary[i] = new BST<string>();
    }
    string wordlist;
    cout << "Enter File Path of WordList File: ";
    cin >> wordlist;
    ifstream wordlistFile(wordlist);
    if (!wordlistFile) {
        cerr << "Error: Unable to open wordlist file." << endl;
        return 1;
    }

    string word; bool read = false;
    while (wordlistFile >> ws >> word) { // Skip leading whitespace before reading each word
        if (isASCII(word)) {
            char firstChar = tolower(word[0]); // Convert to lowercase here
            if (isalpha(firstChar)) {
                int index = firstChar - 'a';
                dictionary[index]->insert(word);
                read = true;
              
            }
            else {
                cerr << "Error: Invalid character '" << firstChar << "' encountered." << endl;
            }
        }
    }
    if (read)cout << "Wordlist file read successfully" << endl;
    wordlistFile.close();
    
    ofstream updatedDictionary(wordlist, ios::app);


    if (!updatedDictionary) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }
    bool enter;
    cout << "Do you wish to add any additional words: Enter '0' for No or '1' for Yes" << endl;
    cin >> enter;
    if (enter)
    {
        cout << "Enter words to add to dictionary: to stop enter '0'" << endl;
        do
        {
            cin >> word;
            if (isASCII(word)) {
                char firstChar = tolower(word[0]); // Convert to lowercase here
                if (isalpha(firstChar)) {
                    int index = firstChar - 'a';
                    dictionary[index]->insert(word);
                    updatedDictionary << endl;
                    updatedDictionary << word;

                }
                else {
                    if(word !="0")
                    cout << "Error: Invalid character '" << firstChar << "' encountered." << endl;
                }
            }
        }

        while (word != "0");
    }
    
    wordlistFile.close();

    cout << "The dictionary contains " << dictionaryWordCount(dictionary) << " words" << endl;
    
    string input;
    cout << "Enter File Path of Input File: ";
    cin >> input;
    ifstream inputFile(input);
    priority_queue<pair<int, string>, vector<pair<int, string>>, ComparePairFirst> q;
    int count;
    while (inputFile >> word)
    {
        int index = tolower(word[0]) - 'a';
        count = 0;
        if (!dictionary[index]->search(word))
        {
            vector<string> temp = dictionary[index]->inorderTraversal();
            for (string x : temp)
            {
                q.push({ hammingDistance(word, x), x });
                if (q.top().first == 1)
                    count++;
                if (count >= 5)
                    break;
            }
            if (count < 5)
            {
                for (int i = 0; i < 26; i++)
                {
                    if (i == index)
                        continue;
                    vector<string> temp = dictionary[i]->inorderTraversal();
                    for (string x : temp)
                    {
                        q.push({ hammingDistance(word, x), x });
                        if (q.top().first == 1)
                            count++;
                        if (count >= 5)
                            break;
                    }
                }
            }
        }

        // Check if q is not empty before accessing its top element
        if (!q.empty())
        {
            string x1 = q.top().second;
            q.pop();
            string x2 = q.top().second;
            q.pop();
            string x3 = q.top().second;
            q.pop();
            string x4 = q.top().second;
            q.pop();
            string x5 = q.top().second;
            while (!q.empty())
                q.pop();
            cout << "Mispelled Word: " << word << endl << "Suggestions: " << x1 << ", " << x2 << ", " << x3 << ", " << x4 << ", " << x5 << endl;
        }
    }

   

    // Free memory for BST objects
    for (int i = 0; i < 26; ++i) {
        delete dictionary[i];
    }

    return 0;
}

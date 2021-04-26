#include<iostream>
#include <utility>
#include <fstream>

using namespace std;
struct words {
    string word;
    words *next;
    words *synonym;
};

words *creatWord(string word, words *synonym) {
    auto *node = new words{std::move(word), nullptr, synonym};
    return node;
}

void addWord(words *&head, words *node);

void addSynonym(words *&node, const string &synonym);

void printWord(words *node);

void printAllWords(words *head);

words *findWord(words *head, const string &word);

void changeWord(words *&head, const string &oldWord, const string &newWord);

void deleteWord(words *&head, const string &word);

void deleteSynonym(words *&word, const string &synonym);

void addListTofWords(words *&head, words *linkList);

void deleteListOfWords(words *&head, words *linkList);

words *creatWordWithArray(string str[], int size);

string wordsToString(words *node);

void writeInFile(words *head);

int countWord(const string &str);

words *readFromFile(const string &address);

void stringToArray(string str, string ans[], int size);

void menuPrint();

void addWordPrint(words *&head);

void addSynonymPrint(words *&head);

void findWordPrint(words *&head);

void deleteWordPrint(words *&head);

void deleteSynonymPrint(words *&head);

void changeNameWordPrint(words *&head);

void readFromFilePrint(words *&head);

int main() {
    words *head = nullptr;
    int command;
    bool check = true;
    while (check) {
        menuPrint();
        cin >> command;
        switch (command) {
            case 1:
                addWordPrint(head);
                break;
            case 2:
                addSynonymPrint(head);
                break;
            case 3:
                findWordPrint(head);
                break;
            case 4:
                deleteWordPrint(head);
                break;
            case 5:
                deleteSynonymPrint(head);
                break;
            case 6:
                printAllWords(head);
                break;
            case 7:
                changeNameWordPrint(head);
                break;
            case 8:
                writeInFile(head);
                break;
            case 9:
                readFromFilePrint(head);
                break;
            case 10:
                check = false;
                cout << "Bye" << endl;
                break;
            default:
                cout << "Invalid\n Enter a number" << endl;

        }
    }
    return 0;
}

void menuPrint() {
    cout << "1-Add word" << endl;
    cout << "2-Add synonym" << endl;
    cout << "3-Find word" << endl;
    cout << "4-Delete word" << endl;
    cout << "5-Delete synonym" << endl;
    cout << "6-Print all word" << endl;
    cout << "7-Change name" << endl;
    cout << "8-Write in file" << endl;
    cout << "9-Read from file" << endl;
    cout << "10-Exit" << endl;
}

void addWordPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    int len;
    cin >> word;
    cout << "Enter number of synonym" << endl;
    auto temp = creatWord(word, nullptr);
    cin >> len;
    string t;
    for (int i = 0; i < len; ++i) {
        cout << "Enter synonym" << endl;
        cin >> t;
        addSynonym(temp, t);
    }
    addWord(head, temp);

}

void addSynonymPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    int len;
    cin >> word;
    cout << "Enter number of synonym" << endl;
    auto temp = findWord(head, word);
    cin >> len;
    string t;
    for (int i = 0; i < len; ++i) {
        cout << "Enter synonym" << endl;
        cin >> t;
        addSynonym(temp, t);
    }
    addWord(head, temp);
}

void findWordPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    cin >> word;
    auto temp = findWord(head, word);
    if (temp == nullptr)
        cout << "This word does not exist" << endl;
    else
        printWord(temp);
}

void deleteWordPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    cin >> word;
    deleteWord(head, word);
}

void deleteSynonymPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    cin >> word;
    auto temp = findWord(head, word);
    printWord(temp);
    int len;
    cout << "Enter number of synonym" << endl;
    cin >> len;
    string t;
    for (int i = 0; i < len; ++i) {
        cin >> t;
        deleteSynonym(temp, t);
    }
}

void changeNameWordPrint(words *&head) {
    cout << "Enter word" << endl;
    string word;
    cin >> word;
    auto temp = findWord(head, word);
    if (temp == nullptr)
        return;
    cout << "Enter new name" << endl;
    cin >> word;
    changeWord(head, temp->word, word);

}

void readFromFilePrint(words *&head) {
    cout << "Enter address" << endl;
    string address;
    cin >> address;
    addListTofWords(head, readFromFile(address));
}

void printWord(words *node) {
    if (node == nullptr) {
        cout << "This is null\n";
        return;
    }
    cout << "Word: " << node->word << "\tsynonym: ";
    words *temp = node->synonym;
    while (temp != nullptr) {
        cout << temp->word << "  ";
        temp = temp->next;
    }
    cout << endl;
}

void printAllWords(words *head) {
    auto temp = head;
    while (temp != nullptr) {
        printWord(temp);
        temp = temp->next;
    }
}

void addWord(words *&head, words *node) {
    auto temp = head;
    if (head == nullptr) {
        head = node;
        return;
    }

    while (temp->next != nullptr && temp->next->word.compare(node->word) < 0)
        temp = temp->next;
    if (temp->next == nullptr)
        temp->next = node;
    else {
        node->next = temp->next;
        temp->next = node;
    }

}

words *findWord(words *head, const string &word) {
    auto temp = head;
    while (temp != nullptr && temp->word != word)
        temp = temp->next;
    return temp;
}

void changeWord(words *&head, const string &oldWord, const string &newWord) {
    auto item = findWord(head, oldWord);
    item->word = newWord;
}

void addSynonym(words *&node, const string &synonym) {
    addWord(node->synonym, creatWord(synonym, nullptr));
}

void deleteWord(words *&head, const string &word) {
    if (head == nullptr) {
        printWord(head);
        return;
    }
    auto item1 = head;
    if (head->word == word) {
        head = head->next;
        return;
    }
    auto item2 = item1->next;
    while (item2 != nullptr && item2->word != word) {
        item1 = item1->next;
        item2 = item2->next;
    }
    if (item2 == nullptr)
        cout << "The word do not exist\n";
    else {
        item1->next = item2->next;
        delete item2;
    }

}

void deleteSynonym(words *&word, const string &synonym) {
    deleteWord(word->synonym, synonym);
}

void addListTofWords(words *&head, words *linkList) {
    auto temp = linkList;
    while (temp != nullptr) {
        addWord(head, temp);
        temp = temp->next;
    }
}

void deleteListOfWords(words *&head, words *linkList) {
    auto temp = linkList;
    while (temp != nullptr) {
        deleteWord(head, temp->word);
        temp = temp->next;
    }
}

words *creatWordWithArray(string str[], int size) {
    auto node = creatWord(str[0], nullptr);
    for (int i = 1; i < size; ++i)
        addSynonym(node, str[i]);

    return node;
}

string wordsToString(words *node) {
    string ans = node->word + " ";
    auto temp = node->synonym;
    while (temp != nullptr) {
        ans += temp->word + " ";
        temp = temp->next;
    }
    return ans;
}

void writeInFile(words *head) {
    ofstream writer("data.txt");
    auto temp = head;
    while (temp != nullptr) {
        writer << wordsToString(temp) << endl;
        temp = temp->next;
    }
    writer.close();
}

int countWord(const string &str) {
    int ans = 0;
    for (char s:str)
        if (s == ' ')
            ans++;
    return ans;
}

void stringToArray(string str, string ans[], int size) {
    for (int i = 0; i < size; ++i) {
        ans[i] = str.substr(0, str.find(' '));
        str = str.substr(str.find(' ') + 1, str.size() - str.find(' '));
    }

}

words *readFromFile(const string &address) {
    words *head = nullptr;
    string line;
    ifstream read(address);
    getline(read, line);
    int size = countWord(line);
    while (!read.eof()) {
        string word[size];
        stringToArray(line, word, size);
        addWord(head, creatWordWithArray(word, size));
        getline(read, line);
    }
    return head;

}

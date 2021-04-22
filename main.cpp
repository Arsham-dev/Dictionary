#include<iostream>
#include <utility>

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

int main() {
    auto head = new words{"ali", nullptr, nullptr};
    for (int i = 10; i > 0; --i) {
        auto temp = creatWord(to_string(i) + "i", nullptr);
        addWord(head, temp);
    }
    deleteWord(head, "5i");
    printAllWords(head);

    return 0;
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
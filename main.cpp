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

void printWord(words *node);

void printAllWords(words *head);

int main() {
    auto item=creatWord("ali", nullptr);
    printAllWords(item);
    return 0;
}

void printWord(words *node) {
    cout << "Word: " << node->word << ": ";
    words *temp = node->synonym;
    while (temp != nullptr) {
        cout << temp->word << ", ";
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
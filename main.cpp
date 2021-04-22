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

void printWord(words *node);

void printAllWords(words *head);

int main() {

    return 0;
}

void printWord(words *node) {
    cout << "Word: " << node->word << "\tsynonym: ";
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
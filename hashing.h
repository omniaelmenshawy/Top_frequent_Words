#ifndef UNTITLED3_HASHING_H
#define UNTITLED3_HASHING_H
#include <string>
#include "node.h"
const int size = 6500;

template <class Type>
class hashing {
public:
    node* table[size];
    hashing();
    long long hashFunction(std::string const& str);
    void insert(std::string& words, int count);
    ~hashing();
};
extern const int size;

template <class Type>
hashing<Type>::hashing() {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}
template <class Type>
long long hashing<Type>::hashFunction(std::string const& str) {
    int p = 47;
    long long power_of_p = 1;
    long long hash_val = 0;
    for (int i = 0; i < str.length(); i++) {
        hash_val = (hash_val + (str[i] - 'a' + 1) * power_of_p) % size;
        power_of_p = (power_of_p * p) % size;
    }
    return abs(hash_val);
}
template <class Type>
void hashing<Type>::insert(std::string& words, int count) {
    node* newWord, * current, * trailCurrent;
    int n = 0; int m = 0; int sum = 0;
    int key = hashFunction(words);
    if (table[key] != NULL) {
        current = table[key];
        trailCurrent = NULL;
        if (table[key]->getWords() == words) {
            m = table[key]->getCount();
            sum = count + m;
            table[key]->setCount(sum);
            return;
        }
        else {
            while (current != NULL && current->getWords() != words) {
                trailCurrent = current;
                current = current->getLink();
            }
            if (current == NULL) {
                newWord = new node(words, count);
                newWord->setLink(NULL);
                trailCurrent->setLink(newWord);
            }
            else {
                int a = current->getCount();
                int s = a + count;
                current->setCount(s);
            }

        }
    }
    else {
        newWord = new node(words, count);
        newWord->setLink(NULL);
        table[key] = newWord;

    }

}
template <class Type>
hashing<Type>::~hashing() {
    node* temp;
    node* temp_next;
    for (int i = 0; i < size; i++) {
        temp = table[i];
        while (temp != NULL) {
            temp_next = temp->getLink();
            delete temp;
            temp = temp_next;
        }
        table[i] = NULL;
    }
}

#endif //UNTITLED3_HASHING_H

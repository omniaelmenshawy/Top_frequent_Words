#ifndef UNTITLED3_NODE_H
#define UNTITLED3_NODE_H
#include <string>

class node {
protected:
    std::string words;
    int count;
    node* link;
public:
    node(const std::string& words, int count);
    node();
    const std::string& getWords() const;
    int getCount() const;
    void setCount(int count);
    node* getLink() const;
    void setLink(node *link);
    void setWords(const std::string& words);
};



node::node(const std::string& words, int count) : words(words), count(count) {
    link = NULL;
}

node::node() {
    words = "";
    count = 0;
    link = NULL;
}

const std::string& node::getWords() const {
    return words;
}

int node::getCount() const {
    return count;
}

void node::setCount(int count) {
    node::count = count;
}

node* node::getLink() const {
    return link;
}

void node::setLink(node* link) {
    node::link = link;
}

 void node::setWords(const std::string& words) {
    node::words = words;
}
#endif //UNTITLED3_NODE_H

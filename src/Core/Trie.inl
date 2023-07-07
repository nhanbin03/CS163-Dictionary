#include "Trie.h"

template <class Data>
Trie<Data>::Node::Node(Data data, int numChild)
: data(data) {
    child.assign(numChild, nullptr);
}

template <class Data>
Trie<Data>::Node::~Node() {
    for (int i = 0; i < child.size(); i++) {
        if (child[i] != nullptr)
            delete child[i];
    }
}

template <class Data>
Trie<Data>::Trie(std::string charSet) {
    mRoot = nullptr;
    mNumChild = charSet.size();
    for (int i = 0; i < charSet.size(); i++) {
        mMapping[charSet[i]] = i;
    }
}

template <class Data>
Trie<Data>::StatusID Trie<Data>::insert(const Data& newData) {
    std:: string word = newData.str;
    Node* cur = mRoot;
    if (cur == nullptr){
        cur = new Node(newData(), mNumChild);
    }
    for (int i = 0; i < word.size(); i++){
        int index = mMapping[word[i]];
        if (cur->child[index] == nullptr){
            cur->child[index] = new Node(newData(), mNumChild);
        }
        cur = cur->child[index];
    }
    if (cur->isEmpty == false){
        return StatusID::DUPLICATED;
    }
    cur->data = newData;
    cur->isEmpty = false;
    return StatusID::SUCCESS;
}

template <class Data>
Trie<Data>::StatusID Trie<Data>::remove(const std::string& keyword) {
    return StatusID();
}

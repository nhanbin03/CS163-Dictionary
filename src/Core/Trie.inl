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
    return StatusID();
}

template <class Data>
Trie<Data>::StatusID Trie<Data>::remove(const std::string& keyword) {
    return StatusID();
}

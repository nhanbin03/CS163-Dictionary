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
Trie<Data>::Trie(const std::string& charSet) {
    mRoot = nullptr;
    mNumChild = charSet.size();
    for (int i = 0; i < charSet.size(); i++) {
        mMapping[charSet[i]] = i;
    }
}

template <class Data>
Trie<Data>::~Trie() {
    delete mRoot;
}

template <class Data>
typename Trie<Data>::StatusID Trie<Data>::insert(const Data& newData) {
    std::string word = newData->str;
    if (mRoot == nullptr) {
        mRoot = new Node(Data(), mNumChild);
    }
    Node* cur = mRoot;
    for (int i = 0; i < word.size(); i++) {
        int index = mMapping[word[i]];
        if (cur->child[index] == nullptr) {
            cur->child[index] = new Node(Data(), mNumChild);
        }
        cur = cur->child[index];
    }
    if (cur->isEmpty == false) {
        return StatusID::DUPLICATED;
    }
    cur->data = newData;
    cur->isEmpty = false;
    return StatusID::SUCCESS;
}

template <class Data>
typename Trie<Data>::StatusID Trie<Data>::remove(const std::string& keyword) {
    Node* cur = mRoot;
    if (cur == nullptr) {
        return StatusID::NOT_FOUND;
    }
    for (int i = 0; i < keyword.size(); i++) {
        int index = mMapping[keyword[i]];
        if (cur->child[index] == nullptr) {
            return StatusID::NOT_FOUND;
        }
        cur = cur->child[index];
    }
    if (cur->isEmpty == true) {
        return StatusID::NOT_FOUND;
    }
    cur->isEmpty = true;
    return StatusID::SUCCESS;
}

template <class Data>
typename Trie<Data>::StatusID Trie<Data>::getData(const std::string& keyword,
                                                  Data& returnedData) {
    Node* tmp;
    return getData(keyword, returnedData, tmp);
}

template <class Data>
std::vector<Data> Trie<Data>::getPrefixMatches(const std::string& keyword) {
    std::vector<Data> results;
    Data returnedData;
    Node* cur = nullptr;
    Trie<Data>::getData(keyword, returnedData, cur);
    if (cur != nullptr) {
        Trie<Data>::getResults(cur, results);
    }
    return results;
}

template <class Data>
inline void Trie<Data>::clear() {
    delete mRoot;
    mRoot = nullptr;
}

template <class Data>
void Trie<Data>::getResults(Node* cur, std::vector<Data>& results) {
    if (cur == nullptr) {
        return;
    }
    if (!cur->isEmpty) {
        results.push_back(cur->data);
    }
    for (int i = 0; i < cur->child.size(); i++) {
        Trie<Data>::getResults(cur->child[i], results);
    }
}

template <class Data>
typename Trie<Data>::StatusID Trie<Data>::getData(const std::string& keyword,
                                                  Data& returnedData,
                                                  Node*& returnedNode) {
    Node* cur = mRoot;
    if (cur == nullptr)
        return StatusID::NOT_FOUND;
    for (int i = 0; i < keyword.size(); i++) {
        int index = mMapping[keyword[i]];
        if (cur->child[index] == nullptr)
            return StatusID::NOT_FOUND;
        cur = cur->child[index];
    }

    returnedData = cur->data;
    returnedNode = cur;
    if (cur->isEmpty == true)
        return StatusID::NOT_FOUND;

    return StatusID::SUCCESS;
}

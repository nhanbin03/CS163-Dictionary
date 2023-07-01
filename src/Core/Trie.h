#ifndef CORE_TRIE_H
#define CORE_TRIE_H

#include <string>
#include <vector>

template <class Data>
class Trie {
public:
    enum class StatusID {
        SUCCESS,
        NOT_FOUND,
        DUPLICATED,
    };

public:
    class Node {
        Data data;
        std::vector<Node*> child;
        Node(Data data, int numChild);
        ~Node();
    };

public:
    Trie(std::string charSet);
    ~Trie();

    StatusID insert(const Data& newData);
    StatusID remove(const std::string& keyword);
    StatusID getData(const std::string& keyword,
                     Data& returnedData); // searchs for the keyword and returns
                                          // the data found to returnedData
    std::vector<Data*> getPrefixMatches(const std::string& keyword);

private:
    int mMapping[256]; // convert char to child index
    int mNumChild;

    Node* mRoot;
};

#include "Trie.inl"

#endif // CORE_TRIE_H

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
    struct Node {
        Data data;
        std::vector<Node*> child;
        bool isEmpty{true};
        Node(Data data, int numChild);
        ~Node();
    };

public:
    Trie(const std::string& charSet);
    ~Trie();

    StatusID insert(const Data& newData);
    StatusID remove(const std::string& keyword);

    // searchs for the keyword and returns
    // the data found to returnedData
    // data's node found to returnedNode
    StatusID getData(const std::string& keyword, Data& returnedData);

    std::vector<Data*> getPrefixMatches(const std::string& keyword);

    void clear();

private:
    int mMapping[256]; // convert char to child index
    int mNumChild;

    Node* mRoot;

private:
    void getResults(Node* cur, std::vector<Data*>& results);
    StatusID getData(const std::string& keyword, Data& returnedData,
                     Node*& returnedNode);
};

#include "Trie.inl"

#endif // CORE_TRIE_H

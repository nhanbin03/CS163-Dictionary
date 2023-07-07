#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
class Core {
public:
    struct Word;

    struct Definition {
        std::string str;
        Word *word;

        Definition(const std::string &str);
    };

    struct Word {
        std::string str;
        std::vector<Definition *> defs;
        bool IsFavorite ;
        Word(const std::string &str);
    };

    struct DefWord {
        std::string str;
        std::vector<Definition *> defs;

        DefWord(const std::string &str);
    };

public:
    Core(const std::string &directory);
    ~Core();

    void saveToFile();
    void addFavorite(Word *word);
    void removeFavorite(Word *word);
    bool isFavorite(Word *word);

private:
    std::string mDataDirectory;

    std::vector<Word *> mWordCollection;
    std::vector<Definition *> mDefCollection;
};

#endif // CORE_CORE_H

#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Trie.h"

class Core {
public:
    static constexpr int RESULT_LIMIT = 20;

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
        bool IsFavorite;
        Word(const std::string &str);
    };

    struct DefWord {
        std::string str;
        std::vector<Definition *> defs;

        DefWord(const std::string &str);
    };

public:
    Core(const std::string &specifier, const std::string &charSet);
    ~Core();

    std::vector<Word *> searchKeyword(const std::string &inputString);
    std::vector<Word *> searchDefinition(const std::string &inputString);

    void updateHistory(Word *word);
    std::vector<Word *> getHistory();

    Word *addWord(std::string wordString);
    Definition *addDefinition(std::string defString, Word *word);
    void editDefinition(Definition *def, const std::string &newDef);
    void removeWord(Word *word); // Caution!! Remember to delete its definitions
                                 // AND the word in history

    Word *getRandomWord();

    void addFavorite(Word *word);
    void removeFavorite(Word *word);
    bool isFavorite(Word *word);
    std::vector<Word *> getFavoriteList();

    // pair::first is the question, pair::second [1..4] are choices, [0] is the
    // answer
    std::pair<Word *, std::array<Definition *, 5>> getWordQuiz();
    std::pair<Definition *, std::array<Word *, 5>> getDefinitionQuiz();

    void resetDefault();

private:
    Trie<Word*> mWordSet;
    Trie<DefWord*> mDefWordSet;

    std::string mDataSpecifier; // can be "emoji", "engeng", "engvie", "slang"
                                // or "vieeng"

    std::vector<Word *> mWordCollection;
    std::vector<Definition *> mDefCollection;

    std::vector<Word *> mHistory;

private:
    void loadFromFile();
    void saveToFile();
    std::string extractFirstWord(const std::string& input);
    void loadDataFromSpecifier(const std::string& mdataspecifier, std::vector<std::string>& words);
};

#endif // CORE_CORE_H

#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Trie.h"

class Core {
public:
    static constexpr int RESULT_LIMIT = 20;

public:
    struct Word;

    struct Definition {
        std::string orgStr;
        std::string str;
        Word *word;

        int rating;

        Definition(const std::string &str);

        bool isDeleted();
    };

    struct Word {
        std::string orgStr;
        std::string str;
        std::vector<Definition *> defs;
        bool IsFavorite{false};
        Word(const std::string &str);

        bool isDeleted();
    };

    struct DefWord {
        std::string str;
        std::vector<Definition *> defs;

        DefWord(const std::string &str);
    };

public:
    Core(const std::string &dataName, const std::string &specifier,
         const std::string &wordCharSet, const std::string &defCharSet);
    ~Core();

    std::string getDataName();

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
    Trie<Word *> mWordSet;
    Trie<DefWord *> mDefWordSet;

    std::string mDataName;
    std::string mDataSpecifier; // can be "emoji", "engeng", "engvie", "slang"
                                // or "vieeng"

    std::vector<Word *> mWordCollection;
    std::vector<Definition *> mDefCollection;
    std::vector<DefWord *> mDefWordCollection;

    std::vector<Word *> mHistory;

private:
    void loadFromFile();
    void saveToFile();
    std::string extractFirstWord(const std::string &input);
    void loadDataFromSpecifier(const std::string &mdataspecifier,
                               std::vector<std::string> &words);
    void loadDataFromHistory(const std::string &mdataspecifier2);
    std::string extractSecondWord(const std::string &input);
    void loadWordLocal(const std::string &mdataspecifier3);
    std::string extractWord1(const std::string &input);
    std::string extractWord2(const std::string &input);

    void ratingCleanUp();
    void equivalentFilter1(std::vector<Definition *> &defResults,
                           const std::string &inputString);
    void equivalentFilter2(std::vector<Definition *> &defResults,
                           const std::string &inputString);
};

#endif // CORE_CORE_H

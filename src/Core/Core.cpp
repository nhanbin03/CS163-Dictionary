#include "Core.h"
#include "../Helper.h"

Core::Word::Word(const std::string& str)
: str(normalize(str)) {
}

Core::Definition::Definition(const std::string& str)
: str(normalize(str)) {
}

Core::DefWord::DefWord(const std::string& str)
: str(normalize(str)) {
}

Core::Core(const std::string& specifier, const std::string& charSet)
: mDataSpecifier(specifier)
, mWordSet(charSet)
, mDefWordSet(charSet) {
}

Core::~Core() {
}

void Core::addFavorite(Word* word) {
    if (word->IsFavorite == false) {
        word->IsFavorite = true;
    } else {
        std::cout << "already added" << std::endl;
        return;
    }
}

void Core::removeFavorite(Word* word) {
    if (word->IsFavorite == true) {
        word->IsFavorite = false;
    } else {
        std::cout << "this word is not favorite word yet" << std::endl;
        return;
    }
}

bool Core::isFavorite(Word* word) {
    return word->IsFavorite;
}

void Core::saveToFile() {
    /*
    std::string filePath = mDataDirectory + "/data.txt";
    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        for (Word* word : mWordCollection) {
            for (Definition* def : word->defs) {
                outputFile << word->str << "\t" << def->str << std::endl;
            }
        }
        outputFile.close();
        std::cout << "Data saved to " << filePath << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }
    */
}

std::vector<Core::Word*> Core::searchKeyword(const std::string& inputString) {
    return mWordSet.getPrefixMatches(normalize(inputString));
}

Core::Word* Core::getRandomWord() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, mWordCollection.size() - 1);
    int randomIndex = dist(gen);
    return mWordCollection[randomIndex];
}

std::pair<Core::Word*, std::array<Core::Definition*, 5>> Core::getWordQuiz() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create array of choices. Choice[0] is the answer.
    Definition* choices[5];
    // Get the random definition.
    Word* question = getRandomWord();
    std::uniform_int_distribution<> dist(0, question->defs.size() - 1);
    int randomIndex = dist(gen);
    choices[0] = question->defs[randomIndex];
    // Get the other 4 random definitions. One of them is the answer.
    std::uniform_int_distribution<> dist1(1, 4);
    randomIndex = dist1(gen);
    choices[randomIndex] = question->defs[randomIndex];
    for (int i = 1; i < 5; i++) {
        if (i != randomIndex) {
            Word* randomWord = getRandomWord();
            while (randomWord == question) {
                randomWord = getRandomWord();
            }
            std::uniform_int_distribution<> dist2(0,
                                                  randomWord->defs.size() - 1);
            int randomIndex2 = dist2(gen);
            choices[i] = randomWord->defs[randomIndex2];
        }
    }
    return std::make_pair(
        question, std::array<Definition*, 5>{choices[0], choices[1], choices[2],
                                             choices[3], choices[4]});
}

std::pair<Core::Definition*, std::array<Core::Word*, 5>>
Core::getDefinitionQuiz() {
    // Get a definition.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, mDefCollection.size() - 1);
    int randomIndex = dist(gen);
    Definition* question = mDefCollection[randomIndex];
    // Create array of choices. Choice[0] is the answer.
    Word* choices[5];
    choices[0] = question->word;
    // Get the other 4 random words. One of them is the answer.
    std::uniform_int_distribution<> dist1(1, 4);
    randomIndex = dist1(gen);
    choices[randomIndex] = question->word;
    for (int i = 1; i < 5; i++) {
        if (i != randomIndex) {
            Word* randomWord = getRandomWord();
            while (randomWord == question->word) {
                randomWord = getRandomWord();
            }
            choices[i] = randomWord;
        }
    }
    return std::make_pair(
        question, std::array<Word*, 5>{choices[0], choices[1], choices[2],
                                       choices[3], choices[4]});
}

std::vector<Core::Word*> Core::getFavoriteList() {
    std::vector<Word*> favoriteList;
    for (Word* word : mWordCollection) {
        if (word->IsFavorite) {
            favoriteList.push_back(word);
        }
    }
    return favoriteList;
}
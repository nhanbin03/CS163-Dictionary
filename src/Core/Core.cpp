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

std::vector<Core::Word*> Core::searchKeyword(const std::string &inputString){
    return mWordSet.getPrefixMatches(normalize(inputString));
}

Core::Word* Core::getRandomWord(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, mWordCollection.size() - 1);
    int randomIndex = dist(gen);
    return mWordCollection[randomIndex];
}

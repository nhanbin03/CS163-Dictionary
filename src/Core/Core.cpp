#include "Core.h"

Core::Word::Word(const std::string& str)
: str(str) {
}

Core::Definition::Definition(const std::string& str)
: str(str) {
}

Core::DefWord::DefWord(const std::string& str)
: str(str) {
}

Core::Core(const std::string& directory, const std::string& charSet)
: mDataDirectory(directory)
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
}

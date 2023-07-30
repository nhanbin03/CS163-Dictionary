#include "Core.h"
#include "algorithm"
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

void Core::updateHistory(Word *word) {
    if (word != nullptr) {
        bool found = false;
        for (int i = 0; i < mHistory.size(); i++) {
            if (mHistory[i] == word) {
                found = true;
                mHistory.erase(mHistory.begin() + i);
                break;
            }
        }
//If we found that the word was already in the vector, we remove it
//then insert it at the beginning of vector
//else, remove the last element in vector and insert word.
        if (found) {
            mHistory.insert(mHistory.begin(), word);
        } else {
            if (mHistory.size() >= RESULT_LIMIT) {
                mHistory.erase(mHistory.end());
            }
            mHistory.insert(mHistory.begin(), word);
        }
    }
}

std::vector<Core::Word *> Core::getHistory() {
    return mHistory;
}

void Core::removeWord(Word *word) {
    if (word != nullptr) {
        for (int i = 0; i < mHistory.size(); i++) {
            if (mHistory[i] == word) {
                mHistory.erase(mHistory.begin() + i);
                break;
            }
        }
        mWordSet.remove(word->str);
        for (int i = 0; i < word->defs.size(); i++) {
            auto iter = std::find(mDefCollection.begin(), mDefCollection.end(),
                               word->defs[i]);
            mDefCollection.erase(iter);
            delete word->defs[i];
        }
        delete word;
    }
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
std:: string Core::extractFirstWord(const std::string& input) {
    std::string firstWord;
    size_t pos = input.find('\t');
    if (pos != std::string::npos) {
        firstWord = input.substr(0, pos);
    } else {
        firstWord = input;
    }
    return firstWord;
}

void Core:: loadDataFromSpecifier(const std::string& mdataspecifier, std::vector<std::string>& words) {
    std::string dataFilePath = mdataspecifier + "/data.txt";
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
    words.push_back( extractFirstWord(line));
    
    }

    file.close();
for( int i=0;i<words.size();i++)
{
    Word* myWord;
    if (mWordSet.getData(words[i],myWord)==Trie<Word*>::StatusID::SUCCESS) 
   addFavorite(myWord);
else // thong bao loi 
std:: cout<<"error";
}

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
void Core::loadDataFromHistory(const std::string& mdataspecifier2 ) 
{ 
    std::string dataFilePath = mdataspecifier2 + "/data.txt";//duong dan cua history
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) 
	{   Word* myWord;
        if (mWordSet.getData(extractFirstWord(line),myWord)==Trie<Word*>::StatusID::SUCCESS) 
    mHistory.push_back( myWord);
    
    }

    file.close();

}
std::string Core::  extractWord1(const std::string& input) {
    std::string firstWord;
    size_t pos = input.find(' ');
    if (pos != std::string::npos) {
        firstWord = input.substr(0, pos);
    } else {
        firstWord = input;
    }
    return firstWord;
}
std::string Core:: extractWord2(const std::string& input) {
    std::string secondWord;
    size_t pos = input.find('\t');
    if (pos != std::string::npos) {
      
        secondWord = input.substr(pos + 1);
    } 
    
    return secondWord;
}
std::string Core:: extractSecondWord(const std::string& input) {
    std::string secondWord;
    size_t pos = input.find('\t');
    if (pos != std::string::npos) {
        
        secondWord = input.substr(pos + 1);
    } 
    
    return secondWord;
}
void Core::loadWordLocal(const std::string& mdataspecifier3) {
    std::string dataFilePath = mdataspecifier3 + "/data.txt";//duong dan local
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string s = extractFirstWord(line);
        
        Word* myWord ;
         if (mWordSet.getData(s,myWord)==Trie<Word*>::StatusID::NOT_FOUND)
		{Word* a=new Word (s);
        mWordCollection.push_back(a);
          mWordSet.insert(a);
        }
    }

    file.close();
}
void Core::loadDefWordLocal(const std::string& mdataspecifier4) {
    std::string dataFilePath = mdataspecifier4 + "/data.txt";
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string s = extractSecondWord(line);
        normalize(s);
        std:: string TheWord = extractFirstWord(line);
        Word* k = new Word(TheWord);
        Definition* i= addDefinition(s, k);
        // mDefCollection.push_back(i);
        // Nguyen cai dong while duoi nay lap voi cai check trong ham addDefinition a, doan nay dua xuong duoi kia la ok roi
        while (!line.empty()) {
            DefWord* myDefWord;
            if (mDefWordSet.getData(extractWord1(line), myDefWord) == Trie<DefWord*>::StatusID::NOT_FOUND) {
                DefWord * a = new DefWord(s);
                
                mDefWordSet.insert( a);
            }
            line = extractWord2(line);
        }
    }

    file.close();
}

Core::Word* Core::addWord(std::string wordString){
    Word* newword = new Word(wordString);
    if (mWordSet.insert(newword) == Trie<Word*>::StatusID::SUCCESS){
        mWordCollection.push_back(newword);
    }
    // if (Trie<Word*>::insert(newword) == Trie<Word*>::StatusID::DUPLICATED){
    //     return mWordCollection[std::find(mWordCollection.begin(), mWordCollection.end(), newword)];
    // }
    return newword;
}

Core::Definition* Core::addDefinition(std::string defString, Word *word){
    Definition* newDef = new Definition(defString);
    newDef->word = word;
    bool check = true;
    for (int i = 0; i < word->defs.size(); i++){
        if (word->defs[i]->str == defString){
            check = false;
            break;
        }
    }
    if (check){
        word->defs.push_back(newDef);
        mDefCollection.push_back(newDef);
        
        while (!defString.empty()) {
            DefWord* myDefWord;
            if (mDefWordSet.getData(extractWord1(defString), myDefWord) == Trie<DefWord*>::StatusID::NOT_FOUND) {
                DefWord* a = new DefWord(defString);
                
                mDefWordSet.insert(a);
            }
            defString = extractWord2(defString);
        }
    }
    return newDef;
}

void Core::editDefinition(Core::Definition *def, const std::string &newDef){
    std::string defString = def->str;
    while (!defString.empty()) {    
        mDefWordSet.remove(extractWord1(defString));
        defString = extractWord2(defString);
    }
    def->word->defs.erase(std::find(def->word->defs.begin(), def->word->defs.end(), def));
    std::string s = extractSecondWord(newDef);
    normalize(s);
    std:: string TheWord = extractFirstWord(newDef);
    Word* k = new Word(TheWord);
    Definition* editDef= addDefinition(s, k);
}
void loadFromFile()
{   
    string mdataspecifier ;// duoong dan cua favorite(sau nay se them sau)
     string mdataspecifier2;
      string mdataspecifier3;
       string mdataspecifier4;
     loadDataFromSpecifier(const std::string& mdataspecifier, std::vector<std::string>& words);
     loadDataFromHistory(const std::string& mdataspecifier2 ) ;
  
     loadWordLocal(const std::string& mdataspecifier3) ;
    loadDefWordLocal(const std::string& mdataspecifier4);
  
    
}
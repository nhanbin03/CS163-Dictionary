#include "Core.h"
#include "algorithm"
#include "../Helper.h"

#include <cassert>

Core::Word::Word(const std::string& str)
: orgStr(str), str(convertToNonAccentVN(str)) {
}

bool Core::Word::isDeleted() {
    return str == "";
}

Core::Definition::Definition(const std::string& str)
: orgStr(str), str(normalize(str)) {
    rating = 0;
}

bool Core::Definition::isDeleted() {
    return str == "";
}

Core::DefWord::DefWord(const std::string& str)
: str(str) {
}

Core::Core(const std::string& specifier, const std::string& wordCharSet,
           const std::string defCharSet)
: mDataSpecifier(specifier)
, mWordSet(wordCharSet)
, mDefWordSet(defCharSet) {
    std::cout << "Loading " <<  mDataSpecifier << "...\n";
    loadFromFile();
}

Core::~Core() {
    saveToFile();

    for (auto ptr : mWordCollection) {
        delete ptr;
    }
    for (auto ptr : mDefCollection) {
        delete ptr;
    }
    for (auto ptr : mDefWordCollection) {
        delete ptr;
    }
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
                mHistory.pop_back();
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
        mWordSet.remove(word->str);
        for (int i = 0; i < word->defs.size(); i++) {
            word->defs[i]->str = "";
        }
        word->str = "";
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
    // Save to local
    std::string localFilePath = "data/local/" + mDataSpecifier + "/data.txt";
    std::ofstream localOutputFile(localFilePath);

    if (localOutputFile.is_open()) {
        for (Word* word : mWordCollection) {
            assert(word != nullptr);
            if (!word->isDeleted()) {
                for (Definition* def : word->defs) {
                    assert(def != nullptr);
                    if (!def->isDeleted()) {
                        localOutputFile << word->orgStr << "\t" << def->orgStr << std::endl;
                    }
                }
            }
        }
        localOutputFile.close();
        std::cout << "Data saved to " << localFilePath << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }

    // Save to favorite
    std::string favoriteFilePath = "data/favorite/" + mDataSpecifier + "/data.txt";
    std::ofstream favoriteOutputFile(favoriteFilePath);

    if (favoriteOutputFile.is_open()) {
        for (Word* word : getFavoriteList()) {
            if (!word->isDeleted()) {
                favoriteOutputFile << word->orgStr << "\n";
            }
        }
        favoriteOutputFile.close();
        std::cout << "Data saved to " << favoriteFilePath << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }

    // Save to history
    std::string historyFilePath = "data/history/" + mDataSpecifier + "/data.txt";
    std::ofstream historyOutputFile(historyFilePath);

    if (historyOutputFile.is_open()) {
        for (Word* word : mHistory) {
            if (!word->isDeleted()) {
                historyOutputFile << word->orgStr << "\n";
            }
        }
        historyOutputFile.close();
        std::cout << "Data saved to " << historyFilePath << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }
}

std::vector<Core::Word*> Core::searchKeyword(const std::string& inputString) {
    return mWordSet.getPrefixMatches(inputString);
}

std::vector<Core::Word*> Core::searchDefinition(const std::string& inputString) {
    std::string normalizedString = normalize(inputString);
    std::vector<Definition*> defResults = mDefCollection;
    equivalentFilter1(defResults, normalizedString);
    equivalentFilter2(defResults, normalizedString);

    std::vector<Word*> ret;
    for (auto defPtr : defResults) {
        if (defPtr->isDeleted()) continue;
        bool isDuplicated = false;
        for (auto wordPtr : ret) {
            if (defPtr->word == wordPtr) {
                isDuplicated = true;
            }
        }
        if (!isDuplicated) {
            ret.push_back(defPtr->word);
        }
        if (ret.size() == RESULT_LIMIT) {
            break;
        }
    }

    return ret;
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
    choices[randomIndex] = choices[0];
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

void Core::resetDefault() {
    std::string dataPath = "data/dictionary-data/" + mDataSpecifier;

    mWordSet.clear();
    mDefWordSet.clear();
    for (auto ptr : mWordCollection) {
        delete ptr;
    }
    mWordCollection.clear();
    for (auto ptr: mDefCollection) {
        delete ptr;
    }
    mDefCollection.clear();

    mHistory.clear();
    loadWordLocal(dataPath);
}

std::string Core::extractFirstWord(const std::string& input) {
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
        if (mWordSet.getData(words[i], myWord)
            == Trie<Word*>::StatusID::SUCCESS)
            addFavorite(myWord);
        else // thong bao loi
            std::cout << "Error: Cannot find favorite word\n";
    }

}

std::vector<Core::Word*> Core::getFavoriteList() {
    std::vector<Word*> favoriteList;
    for (Word* word : mWordCollection) {
        if (!word->isDeleted() && word->IsFavorite) {
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
	{   
        Word* myWord;
        if (mWordSet.getData(line,myWord)==Trie<Word*>::StatusID::SUCCESS) 
            mHistory.push_back(myWord);

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

void Core::ratingCleanUp() {
    for (auto defPtr : mDefCollection) {
        defPtr->rating = 0;
    }
}

void Core::equivalentFilter1(std::vector<Definition*>& defResults,
                             const std::string& inputString) {
    ratingCleanUp();

    for (auto wordStr : split(inputString, ' ')) {
        DefWord* defWord;
        if (mDefWordSet.getData(wordStr, defWord) == Trie<DefWord*>::StatusID::SUCCESS) {
            for (auto defPtr : defWord->defs) {
                if (!defPtr->isDeleted())
                    defPtr->rating++;
            }
        }
    }

    sort(defResults.begin(), defResults.end(),
         [](Definition* x, Definition* y) {
             return x->rating > y->rating;
         });

    defResults.resize(RESULT_LIMIT * RESULT_LIMIT);

    while (defResults.size() && defResults.back()->rating == 0) 
        defResults.pop_back();
}

void Core::equivalentFilter2(std::vector<Definition*>& defResults,
                             const std::string& inputString) {
    ratingCleanUp();
    
    std::vector<std::string> inputList = split(inputString, ' ');
    for (auto defPtr : defResults) {
        if (defPtr->isDeleted()) continue;

        std::vector<std::string> defList = split(defPtr->str, ' ');
        
        std::vector<std::vector<int>> dp(inputList.size() + 1, std::vector<int>(defList.size() + 1, 0));

        for (int i = 1; i <= inputList.size(); i++) {
            for (int j = 1; j <= defList.size(); j++) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                if (inputList[i - 1] == defList[j - 1])
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }

        defPtr->rating = dp[inputList.size()][defList.size()];
    }

    sort(defResults.begin(), defResults.end(),
         [](Definition* x, Definition* y) {
             return x->rating > y->rating;
         });
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
    int i = 0;
    while (std::getline(file, line)) {
        std::string s = extractFirstWord(line);
        Word* myWord;
        i++;
        // if (mDataSpecifier == "engvie" && i > 67000)
        //     std::cout << i << " " << s << "\n";
        Word* a = new Word(s);
        if (mWordSet.getData(a->str,myWord)==Trie<Word*>::StatusID::NOT_FOUND)
		{
            mWordCollection.push_back(a);
            mWordSet.insert(a);
            std::string s = extractSecondWord(line);
            addDefinition(s, a);
        } else {
            std::string s = extractSecondWord(line);
            addDefinition(s, myWord);
            delete a;
        }
    }

    file.close();
}

Core::Word* Core::addWord(std::string wordString){
    Word* newword = new Word(wordString);
    if (mWordSet.insert(newword) == Trie<Word*>::StatusID::SUCCESS){
        mWordCollection.push_back(newword);
    } else {
        delete newword;
        newword = nullptr;
    }
    return newword;
}

Core::Definition* Core::addDefinition(std::string defString, Word *word){
    Definition* newDef = new Definition(defString);
    newDef->word = word;
    /* This is not necessary, and it wastes a lot of time */
    // bool check = true;
    // for (int i = 0; i < word->defs.size(); i++){
    //     if (word->defs[i]->str == defString){
    //         check = false;
    //         break;
    //     }
    // }
    // if (check){
    word->defs.push_back(newDef);
    mDefCollection.push_back(newDef);

    for (auto defWordStr : split(newDef->str, ' ')) {
        DefWord* myDefWord;
        if (defWordStr.size() <= 2) continue;
        if (mDefWordSet.getData(defWordStr, myDefWord) == Trie<DefWord*>::StatusID::NOT_FOUND) {
            myDefWord = new DefWord(defWordStr);
            mDefWordCollection.push_back(myDefWord);
            mDefWordSet.insert(myDefWord);
        }
        myDefWord->defs.push_back(newDef);
    }
    // }
    return newDef;
}

void Core::editDefinition(Core::Definition *def, const std::string &newDef){
    def->str = "";
    addDefinition(newDef, def->word);
}

void Core:: loadFromFile()
 {   
    std::vector<std::string> words;
    std::string favoritePath = "data/favorite/" + mDataSpecifier;
    std::string localPath = "data/local/" + mDataSpecifier;
    std::string historyPath = "data/history/" + mDataSpecifier;
    loadWordLocal(localPath);
    std::cout << "Done loading local\n";
    loadDataFromSpecifier(favoritePath,  words);
    std::cout << "Done loading favorite\n";
    loadDataFromHistory(historyPath);
    std::cout << "Done loading history\n";
 }

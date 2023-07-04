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

Core::Core(const std::string& directory)
: mDataDirectory(directory) {
}

Core::~Core() {
}

void Core::addFavorite(Word *word)
{
    if(word->IsFavorite==false)
    {
        word->IsFavorite=true;
    }
    else
    {
        std::cout<<"already added"<<std::endl;
        return ;
    }
}
void Core::removeFavorite(Word *word)
{
    if(word->IsFavorite==true)
    {
        word->IsFavorite=false;
    }
    else
    {
        std::cout<<"this word is not favorite word yet"<<std::endl;
        return ;
    }
}
bool Core::isFavorite(Word *word)
{
    return word->IsFavorite;
}

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
void addFavorite(Word *word)
{
    if(word->IsFavorite==false)
    {
        word->IsFavorite=true;
    }
    else
    {
        cout<<"already added"<<endl;
        return ;
    }
}
void removeFavorite(Word *word)
{
    if(word->IsFavorite==true)
    {
        word->IsFavorite=false;
    }
    else
    {
        cout<<"this word is not favorite word yet"<<endl;
        return ;
    }
}
bool isFavorite(Word *word)
{
    return;
}

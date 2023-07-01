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

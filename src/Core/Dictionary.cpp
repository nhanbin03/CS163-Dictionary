#include "Dictionary.h"

Core Dictionary::CORE[] = {
    // Core(
    //     "engeng",
    //     " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
    //     "abcdefghijklmnopqrstuvwxyz"),
    // Core(
    //     "engvie",
    //     " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
    //     "abcdefghijklmnopqrstuvwxyz"),
    // Core(
    //     "vieeng",
    //     " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
    //     "abcdefghijklmnopqrstuvwxyz"),
    Core(
        "slang",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz"),
    // Core(
    //     "emoji",
    //     " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
    //     "abcdefghijklmnopqrstuvwxyz")
};

Dictionary& Dictionary::getInstance() {
    static Dictionary instance;
    return instance;
}

Core& Dictionary::getDict() {
    return mCurDict;
}

Dictionary::Dictionary() :
mCurDict(CORE[0]) {
}

Dictionary::~Dictionary() {
}

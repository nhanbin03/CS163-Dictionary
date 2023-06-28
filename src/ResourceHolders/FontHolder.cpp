#include "FontHolder.h"

#include <cassert>
#include <iostream>

const int FontHolder::VN_CODEPOINTS[] = {
    97,   65,   224,  192,  7843, 7842, 227,  195,  225,  193,  7841, 7840,
    259,  258,  7857, 7856, 7859, 7858, 7861, 7860, 7855, 7854, 7863, 7862,
    226,  194,  7847, 7846, 7849, 7848, 7851, 7850, 7845, 7844, 7853, 7852,
    98,   66,   99,   67,   100,  68,   273,  272,  101,  69,   232,  200,
    7867, 7866, 7869, 7868, 233,  201,  7865, 7864, 234,  202,  7873, 7872,
    7875, 7874, 7877, 7876, 7871, 7870, 7879, 7878, 102,  70,   103,  71,
    104,  72,   105,  73,   236,  204,  7881, 7880, 297,  296,  237,  205,
    7883, 7882, 106,  74,   107,  75,   108,  76,   109,  77,   110,  78,
    111,  79,   242,  210,  7887, 7886, 245,  213,  243,  211,  7885, 7884,
    244,  212,  7891, 7890, 7893, 7892, 7895, 7894, 7889, 7888, 7897, 7896,
    417,  416,  7901, 7900, 7903, 7902, 7905, 7904, 7899, 7898, 7907, 7906,
    112,  80,   113,  81,   114,  82,   115,  83,   116,  84,   117,  85,
    249,  217,  7911, 7910, 361,  360,  250,  218,  7909, 7908, 432,  431,
    7915, 7914, 7917, 7916, 7919, 7918, 7913, 7912, 7921, 7920, 118,  86,
    119,  87,   120,  88,   121,  89,   7923, 7922, 7927, 7926, 7929, 7928,
    253,  221,  7925, 7924, 122,  90,   32,   33,   34,   35,   36,   37,
    38,   39,   40,   41,   42,   43,   39,   45,   46,   47,   48,   49,
    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
    62,   63,   64,   91,   92,   93,   94,   95,   96,   123,  124,  125,
    126,  127,  0,    1,    2,    3,    4,    5,    6,    7,    8,    9,
    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
    22,   23,   24,   25,   26,   27,   28,   29,   30,   31};

FontHolder::FontHolder() {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING)
        mResourceMap[i][FontID::None] = std::make_unique<Font>();
}

FontHolder::~FontHolder() {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING)
        for (auto& p : mResourceMap[i]) {
            UnloadFont(*p.second);
        }
}

FontHolder& FontHolder::getInstance() {
    static FontHolder instance;
    return instance;
}

void FontHolder::load(FontID id, const std::string& filename) {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING) {
        std::unique_ptr<Font> resource(new Font());
        int glyphCount = (sizeof VN_CODEPOINTS) / (sizeof VN_CODEPOINTS[0]);
        *resource =
            LoadFontEx(filename.c_str(), i, (int*)VN_CODEPOINTS, glyphCount);
        insertResource(i, id, std::move(resource));
    }
}

Font& FontHolder::get(FontID id, int size) {
    if (size > MAX_SIZE)
        size = MAX_SIZE;
    size = (size - 1) / ROUNDING * ROUNDING
         + ROUNDING; // Round to upper multiple of ROUNDING
    if (size > MAX_SIZE)
        size -= ROUNDING;

    auto found = mResourceMap[size].find(id);
    if (found == mResourceMap[size].end()) {
        return *mResourceMap[size][FontID::None];
    }
    SetTextureFilter(found->second->texture, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

const Font& FontHolder::get(FontID id, int size) const {
    if (size > MAX_SIZE)
        size = MAX_SIZE;
    size = (size - 1) / ROUNDING * ROUNDING
         + ROUNDING; // Round to upper multiple of ROUNDING
    if (size > MAX_SIZE)
        size -= ROUNDING;

    auto found = mResourceMap[size].find(id);
    if (found == mResourceMap[size].end()) {
        return *mResourceMap[size].at(FontID::None);
    }
    SetTextureFilter(found->second->texture, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

void FontHolder::insertResource(int size, FontID id,
                                std::unique_ptr<Font> resource) {
    auto insertStatus = mResourceMap[size].emplace(id, std::move(resource));
    assert(insertStatus.second == true);
}

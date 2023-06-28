#ifndef RESOURCEHOLDERS_TEXTUREHOLDER_H
#define RESOURCEHOLDERS_TEXTUREHOLDER_H

#include "ResourceIdentifiers.h"

#include "raylib.h"

#include <map>
#include <memory>
#include <string>

// Singleton
class TextureHolder {
public:
    static TextureHolder& getInstance();

    void load(TextureID id, const std::string& filename);

    Texture2D& get(TextureID id);
    const Texture2D& get(TextureID id) const;

private:
    TextureHolder();
    TextureHolder(TextureHolder const&) = delete;
    void operator= (TextureHolder const&) = delete;
    ~TextureHolder();
    std::map<TextureID, std::unique_ptr<Texture2D>> mResourceMap;

private:
    void insertResource(TextureID id, std::unique_ptr<Texture2D> resource);
};

#endif // RESOURCEHOLDERS_TEXTUREHOLDER_H

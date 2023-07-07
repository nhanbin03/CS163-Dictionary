#include "GUIComponentHelper.h"

void scaleTexture(Texture2D& source, Vector2 newSize) {
    Image img = LoadImageFromTexture(source);
    ImageResize(&img, newSize.x, newSize.y);
    source = LoadTextureFromImage(img);
}
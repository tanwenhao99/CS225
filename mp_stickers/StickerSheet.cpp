#include "StickerSheet.h"

void StickerSheet::_copy(StickerSheet const & other) {
    delete base;
    delete[] stickers;
    delete[] xValue;
    delete[] yValue;
    lowest = other.lowest;
    max_stickers = other.max_stickers;
    base = new Image(*other.base);
    stickers = new Image[max_stickers];
    xValue = new unsigned[max_stickers];
    yValue = new unsigned[max_stickers];
    for (unsigned i = 0; i < max_stickers; i++) {
        stickers[i] = other.stickers[i];
        xValue[i] = other.xValue[i];
        yValue[i] = other.yValue[i];
    }
}

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    lowest = 0;
    max_stickers = max;
    base = new Image(picture);
    stickers = new Image[max_stickers];
    xValue = new unsigned[max_stickers];
    yValue = new unsigned[max_stickers];
    for (unsigned i = 0; i < max_stickers; i++) 
        xValue[i] = -1;
}

StickerSheet::~StickerSheet() {
    delete base;
    delete[] stickers;
    delete[] xValue;
    delete[] yValue;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    base = NULL;
    stickers = NULL;
    xValue = NULL;
    yValue = NULL;
    _copy(other);
}

StickerSheet const & StickerSheet::operator= (StickerSheet const & other) {
    if (this != &other)
        _copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image * newStickers = new Image[max];
    unsigned * newX = new unsigned[max];
    unsigned * newY = new unsigned[max];
    if (max > max_stickers) {
        for (unsigned i = 0; i < max_stickers; i++) {
            newStickers[i] = stickers[i];
            newX[i] = xValue[i];
            newY[i] = yValue[i];
        }
        for (unsigned i = max_stickers; i < max; i++) 
            newX[i] = -1;
        if ((int)lowest == -1)
            lowest = max_stickers;
    } else if (max < max_stickers) {
        if (lowest >= max)
            lowest = -1;
        for (unsigned i = 0; i < max; i++) {
            newStickers[i] = stickers[i];
            newX[i] = xValue[i];
            newY[i] = yValue[i];
        }
    }
    delete[] stickers;
    delete[] xValue;
    delete[] yValue;
    stickers = newStickers;
    xValue = newX;
    yValue = newY;
    max_stickers = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if ((int)lowest == -1)
        return -1;
    int val = (int)lowest;
    stickers[lowest] = sticker;
    xValue[lowest] = x;
    yValue[lowest] = y;
    while (lowest < max_stickers && (int)xValue[lowest] != -1) 
        lowest++;
    if (lowest == max_stickers)
        lowest = -1;
    return val;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= max_stickers || (int)xValue[index] == -1) 
        return false;
    xValue[index] = x;
    yValue[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    xValue[index] = -1;
    if (index < lowest)
        lowest = index;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= max_stickers || (int)xValue[index] == -1) 
        return NULL;
    return &stickers[index];
}

Image StickerSheet::render() const {
    Image picture(*base);
    for (unsigned i = 0; i < max_stickers; i++) {
        if ((int)xValue[i] != -1) {
            if ((stickers[i].width() + xValue[i]) > picture.width() && (stickers[i].height() + yValue[i]) > picture.height())
                picture.resize(stickers[i].width() + xValue[i], stickers[i].height() + yValue[i]);
            else if ((stickers[i].width() + xValue[i]) > picture.width())
                picture.resize(stickers[i].width() + xValue[i], picture.height());
            else if ((stickers[i].height() + yValue[i]) > picture.height())
                picture.resize(picture.width(), stickers[i].height() + yValue[i]);
            for (unsigned x = 0; x < stickers[i].width(); x++) {
                for (unsigned y = 0; y < stickers[i].height(); y++) {
                    if (stickers[i].getPixel(x, y).a != 0)
                        picture.getPixel(xValue[i] + x, yValue[i] + y) = stickers[i].getPixel(x, y);
                }
            }
        }
    }
    return picture;
}
/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        StickerSheet const & operator= (StickerSheet const & other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        Image render() const;
    private:
        Image * stickers;
        Image * base;
        unsigned * xValue;
        unsigned * yValue;
        unsigned lowest;
        unsigned max_stickers;
        void _copy(StickerSheet const & other);
};

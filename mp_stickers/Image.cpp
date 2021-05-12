#include "Image.h"
using namespace cs225;

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += amount;
            if (pixel.l > 1)
                pixel.l = 1;
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l < 0)
                pixel.l = 0;
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += amount;
            if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= amount;
            if (pixel.s < 0)
                pixel.s = 0;
        }
    }
}

void Image::grayscale() {
    desaturate(1);
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.h += degrees;
            if (pixel.h >= 360)
                pixel.h -= 360;
            if (pixel.h < 0)
                pixel.h += 360;
        }
    }
}

void Image::illinify() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h >= (216 + 11) / 2 && pixel.h <= (360 + 216 + 11) / 2)
                pixel.h = 216;
            else
                pixel.h = 11;
        }
    }
}

void Image::scale(double factor) {
    HSLAPixel * ImageData = new HSLAPixel[width() * height()];
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            ImageData[x + y * width()] = getPixel(x, y);
        }
    }
    resize(width() * factor, height() * factor);
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & oldPixel = ImageData[(int)(x / factor) + (int)(y / factor) * (int)(width() / factor)];
            pixel.h = oldPixel.h;
            pixel.s = oldPixel.s;
            pixel.l = oldPixel.l;
            pixel.a = oldPixel.a;
        }
    }
    delete[] ImageData;
}

void Image::scale(unsigned w, unsigned h) {
    double factor;
    if ((double)w / width() > (double)h / height())
        factor = (double)h / height();
    else
        factor = (double)w / width();
    scale(factor);
} 
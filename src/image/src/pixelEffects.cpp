#ifndef PIXELEFFECT_H
#define PIXELEFFECT_H
#include "../include/pixelEffects.hpp"
#endif

void GrayscaleEffect::applyPixelTransform(uint8_t* pixels, int index, void* args){
    int pixel_intensity = (pixels[index] + pixels[index+1] + pixels[index+2]) / 3; 
    pixels[index] = pixel_intensity;
    pixels[index+1] = pixel_intensity;
    pixels[index+2] = pixel_intensity;
}

void ChannelFilterEffect::applyPixelTransform(uint8_t* pixels, int index, void* args){
    pixels[index] = b * pixels[index];
    pixels[index+1] = g * pixels[index+1];
    pixels[index+2] = r * pixels[index+2];
}

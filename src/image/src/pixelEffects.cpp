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

void ColorFilterEffect::applyPixelTransform(uint8_t* pixels, int index, void* args){
    pixels[index] = b * pixels[index];
    pixels[index+1] = g * pixels[index+1];
    pixels[index+2] = r * pixels[index+2];
}

void IntensityEffect::applyPixelTransform(uint8_t* pixels, int index, void* args){
    switch(type){
        case INTENSITY_SCALE:
            pixels[index] = math::clamp<int>(pixels[index]*intensityScale, 0, 255);
            pixels[index+1] = math::clamp<int>(pixels[index+1]*intensityScale, 0, 255);
            pixels[index+2] = math::clamp<int>(pixels[index+2]*intensityScale, 0, 255);
            break;
        case INTENSITY_TRANSFORM:
            pixels[index] = math::clamp<int>(pixels[index]+intensityTransform, 0, 255);
            pixels[index+1] = math::clamp<int>(pixels[index+1]*intensityTransform, 0, 255);
            pixels[index+2] = math::clamp<int>(pixels[index+2]*intensityTransform, 0, 255);
            break;
    }
}

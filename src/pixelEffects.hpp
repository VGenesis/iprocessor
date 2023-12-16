#ifndef EFFECT_H
#define EFFECT_H
#include "effect.hpp"
#endif

class GrayscaleEffect : public PixelEffect{
    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args){
            int pixel_intensity = (pixels[index] + pixels[index+1] + pixels[index+2]) / 3; 
            pixels[index] = pixel_intensity;
            pixels[index+1] = pixel_intensity;
            pixels[index+2] = pixel_intensity;
        }

    public:
        GrayscaleEffect(const char* name): PixelEffect(name)
        {}

        ~GrayscaleEffect() = default;

        virtual void print(){
            PixelEffect::print();
            printf("grayscale\n");
        }
};

class ChannelFilterEffect : public PixelEffect{
    private:
        bool r, g, b;

    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args){
            pixels[index] = b? pixels[index] : 0;
            pixels[index+1] = g? pixels[index+1] : 0;
            pixels[index+2] = r? pixels[index+2] : 0;
        }
            
    public:
        ChannelFilterEffect(const char* name, bool r, bool g, bool b):
            PixelEffect(name),
            r(r), g(g), b(b)
        {}

        ~ChannelFilterEffect() = default;

        virtual void print(){
            PixelEffect::print();
            const char* r_str = r? "on" : "off";
            const char* g_str = g? "on" : "off";
            const char* b_str = b? "on" : "off";
            printf("color filter r=%s g=%s b=%s", r_str, g_str, b_str);
        }

};

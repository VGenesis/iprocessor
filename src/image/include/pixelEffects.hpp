#ifndef EFFECT_H
#define EFFECT_H
#include "effect.hpp"
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

class GrayscaleEffect : public PixelEffect{
    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args);

    public:
        GrayscaleEffect(const char* name): PixelEffect(name)
        {}

        ~GrayscaleEffect() = default;

        virtual void print(){
            PixelEffect::print();
            printf("grayscale\n");
        }
};

class ColorFilterEffect : public PixelEffect{
    private:
        float r, g, b;

    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args);
            
    public:
        ColorFilterEffect(const char* name, float r, float g, float b):
            PixelEffect(name),
            r(r), g(g), b(b)
        {}

        ~ColorFilterEffect() = default;

        virtual void print(){
            PixelEffect::print();
            const char* r_str = r? "on" : "off";
            const char* g_str = g? "on" : "off";
            const char* b_str = b? "on" : "off";
            printf("color filter r=%s g=%s b=%s", r_str, g_str, b_str);
        }
};

enum IntensityEffectType{
    INTENSITY_SCALE,
    INTENSITY_TRANSFORM
};

class IntensityEffect : public PixelEffect{
    private:
        IntensityEffectType type;
        float intensityScale{1.0};
        int intensityTransform{0};
        
    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args);


    public:
        IntensityEffect(const char* name, int intensityTransform): 
            PixelEffect(name),
            type(INTENSITY_TRANSFORM),
            intensityTransform(intensityTransform)
        {};

        IntensityEffect(const char* name, float intensityScale): 
            PixelEffect(name),
            type(INTENSITY_TRANSFORM),
            intensityScale(intensityScale)
        {};

        virtual void print(){
            PixelEffect::print();
            std::string typeStr = (type == INTENSITY_SCALE)
                ? "Intensity Scale: " + std::to_string(intensityScale)
                : "Intensity Transform: " + std::to_string(intensityTransform);
            printf("%s", typeStr.c_str());
        }
};


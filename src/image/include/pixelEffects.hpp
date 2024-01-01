#ifndef EFFECT_H
#define EFFECT_H
#include "effect.hpp"
#endif

class GrayscaleEffect : public PixelEffect{
    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args) = 0;

    public:
        GrayscaleEffect(const char* name): PixelEffect(name)
        {}

        ~GrayscaleEffect() = default;

        virtual void print(){
            PixelEffect::print();
            printf("grayscale\n");
        }
};

class ChannelFilterEffect : protected PixelEffect{
    private:
        float r, g, b;

    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args) = 0;
            
    public:
        ChannelFilterEffect(const char* name, float r, float g, float b):
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

//enum IntensityFilterType{
//    INTENSITY_SCALE,
//    INTENSITY_TRANSFORM
//};
//class IntensityFilter : protected PixelEffect{
//    private:
//        float intensityScale;
//        int intensityTransform;
//        IntensityFilterType type;
//        
//};

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <sys/types.h>

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

class Effect{
    protected:
        const char* name;

        Effect(const char* name): name{name}
        {}

        ~Effect() = default;
    public:
        virtual SDL_Surface* applyEffect(SDL_Surface* surface) = 0;

        virtual void print(){
            printf("%s: ", name);
        }
};

class PixelEffect : public Effect{
    protected:
        virtual void applyPixelTransform(uint8_t* pixels, int index, void* args) = 0;

    public:
        PixelEffect(const char* name): Effect(name)
        {}

        ~PixelEffect() = default;

        virtual SDL_Surface* applyEffect(SDL_Surface* surface){
            int index_offset = 0;
            int bpp = surface->pitch / surface->w; 
            if(bpp == 4) index_offset++;

            SDL_LockSurface(surface);
            uint8_t* pixels = (uint8_t*)surface->pixels;

            for(int i = 0; i < surface->h; i++){
                for(int j = 0; j < surface->w; j++){
                    int index = (surface->w * i + j) * bpp + index_offset;
                    applyPixelTransform(pixels, index, NULL);
                }
            }

            SDL_UnlockSurface(surface);
            return surface;
        }

        virtual void print(){
            Effect::print();
            printf("pixel-per-pixel transform - ");
        }
};

class ImageEffect : public Effect{
    public:
        virtual SDL_Surface* applyEffect(SDL_Surface* surface) = 0;

        virtual void print(){
            printf("image property effect - ");
        }
};

class SpatialEffect : public Effect{
    protected:
        virtual void applySpatialTransformation(uint8_t* pixels, SDL_Surface* mask, int index) = 0;

    public:
        virtual SDL_Surface* applyEffect(SDL_Surface* surface) = 0;

        virtual void print(){
            printf("spatial transformation - ");
        }
};


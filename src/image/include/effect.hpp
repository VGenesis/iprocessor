#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <bits/fs_fwd.h>
#include <cmath>
#include <cstdint>
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
    private:
        int mask_size;
        
    protected:
        virtual void applySpatialTransformation(uint8_t* pixels, uint8_t* mask, int index) = 0;

    public:
        SpatialEffect(const char* name, int mask_size):
            Effect(name),
            mask_size(mask_size)
        {}

        virtual SDL_Surface* applyEffect(SDL_Surface* surface){
            int bpp = surface->pitch / surface->w;
            SDL_Surface* expImage = SDL_CreateRGBSurface(
                    0,
                    surface->w + 2*mask_size,
                    surface->h + 2*mask_size,
                    bpp,
                    0, 0, 0, 255
                    );

            uint8_t* pixels = static_cast<uint8_t*>(expImage->pixels);
            int mask_w = 2*mask_size+1;
            int mask_h = mask_w;
            for(int i = mask_size; i < expImage->w-mask_size; i++){
                for(int j = mask_size; j < expImage->h-mask_size; j++){
                    int index = (i*surface->w + j) * bpp;
                    SDL_Surface* mask_surface = SDL_CreateRGBSurface(
                            0, mask_h, mask_w, bpp,
                            0, 0, 0, 255
                            );

                    SDL_Rect srcrect = {i - mask_size, j - mask_size, mask_w, mask_h};
                    SDL_BlitSurface(expImage, &srcrect, mask_surface, NULL);
                    uint8_t* mask = static_cast<uint8_t*>(mask_surface->pixels);
                    applySpatialTransformation(pixels, mask, index);
                }
            }

            return surface;
        }

        virtual void print(){
            printf("spatial transformation - ");
        }
};

class FrequentialEffect : public Effect{
    protected:
        virtual void applySpatialTransformation(uint8_t* pixels, SDL_Surface* mask, int index) = 0;

    public:
        virtual SDL_Surface* applyEffect(SDL_Surface* surface) = 0;

        virtual void print(){
            printf("frequecy-space  - ");
        }
};


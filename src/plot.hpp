#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_sensor.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#endif

#ifndef EFFECT_H
#define EFFECT_H
#include "effect.hpp"
#endif

#ifndef LIST_H
#define LIST_H
#include "list.hpp"
#endif

#ifndef STDIO_H
#define STDIO_H 
#include <stdio.h>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

class Plot{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* image;
        SDL_Surface* renderSurf;
        
        std::vector<Effect*> effects;
        
    public:
        bool running{true};

        Plot(const char* url){
           image = SDL_LoadBMP(url);
           window = SDL_CreateWindow(
                    url,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    image->w,
                    image->h,
                    SDL_WINDOW_HIDDEN
                    );

           renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

           SDL_PixelFormat* pf = image->format;
           renderSurf = SDL_CreateRGBSurface(0, image->w, image->h, 24, 0, 0, 0, 255);
        }

        Plot(const char* name, SDL_Surface* image){
            this->image = image;
            window = SDL_CreateWindow(
                    name,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    image->w,
                    image->h,
                    SDL_WINDOW_SHOWN
                    );

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            renderSurf = SDL_CreateRGBSurface(0, this->image->w, this->image->h, this->image->pitch / this->image->w, 0, 0, 0, 0);
        }

        ~Plot(){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_FreeSurface(image);
            SDL_FreeSurface(renderSurf);
        }

        void quit(){
            free(this);
        }

        void addEffect(Effect* effect){
            effects.push_back(effect);
        }

        void update(){
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                    printf("Window closed\n");
                }
            }

            SDL_Rect srcrect = {0, 0, image->w, image->h};
            SDL_BlitSurface(image, &srcrect, renderSurf, &srcrect);
            
            SDL_SetSurfaceBlendMode(renderSurf, SDL_BLENDMODE_BLEND);
            for(Effect* effect : effects)
                renderSurf = effect->applyEffect(renderSurf);
        }

        void render(){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_BLENDMODE_BLEND);
            SDL_RenderClear(renderer);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, renderSurf);
            SDL_Rect srcrect = {0, 0, image->w, image->h};
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_RenderPresent(renderer);
        }

        void printEffects(){
            for(Effect* effect : effects){
                effect->print();
            }
        }

        void hide(){
            SDL_SetWindowOpacity(window, 0.0);
        }

        void show(){
            SDL_SetWindowOpacity(window, 1.0);
        }
};

#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#endif

#ifndef EFFECT_H
#define EFFECT_H
#include "effect.hpp"
#endif

#ifndef LIST_H
#define LIST_H
#include "../../ds/include/list.hpp"
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef MUTEX
#define MUTEX
#include <mutex>
#endif

#ifndef ATOMIC
#define ATOMIC
#include <atomic>
#endif

class Plot{
    private:
        std::string url {""};
        SDL_Window* window {nullptr};
        SDL_Renderer* renderer {nullptr};
        SDL_Surface* image {nullptr};
        SDL_Surface* renderSurf {nullptr};

        std::vector<Effect*> effects;
        std::mutex mtx;

        bool running{false};


        Plot(std::string url, SDL_Surface* image){
            mtx.lock();

            SDL_ClearError();
            this->url = url;
            this->image = image;
            SDL_PixelFormat* pf = image->format;
            renderSurf = SDL_CreateRGBSurface(0, image->w, image->h, 24, 0, 0, 0, 255);

            window = SDL_CreateWindow(
                    url.c_str(),
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    image->w,
                    image->h,
                    SDL_WINDOW_HIDDEN
                    );

            if(SDL_Init(SDL_INIT_VIDEO) < 0){
                std::cout << "Could not initialize SDL video system. Error: " << SDL_GetError() << std::endl;
                SDL_Quit();
            }

            const char* err = SDL_GetError();
            if(strlen(err) > 0){
                std::cout << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            mtx.unlock();
        }

    public:
        
        static Plot* createInstance(std::string url){
            SDL_ClearError();
            SDL_Surface* image = SDL_LoadBMP(url.c_str());
            std::string err (SDL_GetError());
            if(!err.empty()){
                std::cout << err << std::endl;
                SDL_ClearError();
                return nullptr;
            }

            return new Plot(url, image);
        }

        ~Plot(){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_FreeSurface(image);
            SDL_FreeSurface(renderSurf);
            SDL_Quit();
        }

        std::string getURL() {return url;}

        SDL_Window* getWindow() {return window;}

        bool is_running() {return running;}

        void setTitle(std::string name, int fps){
            mtx.lock();

            std::string title = name + " @" + std::to_string(fps) + "fps";
            SDL_SetWindowTitle(window, title.c_str());

            mtx.unlock();
        }

        void show(){
            mtx.lock();

            SDL_ShowWindow(window);
            running = true;

            mtx.unlock();
        }

        void addEffect(Effect* effect){
            mtx.lock();
            
            effects.push_back(effect);

            mtx.unlock();
        }

        void update(){
            mtx.lock();

            SDL_Event event;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
                    if(event.window.windowID == SDL_GetWindowID(window)){
                        SDL_HideWindow(window);
                        running = false;
                        mtx.unlock();
                        return;
                    }
                }
            }

            // SDL_Rect srcrect = {0, 0, image->w, image->h};
            // SDL_BlitSurface(image, &srcrect, renderSurf, &srcrect);

            //SDL_SetSurfaceBlendMode(renderSurf, SDL_BLENDMODE_BLEND);
            //for(Effect* effect : effects)
                //renderSurf = effect->applyEffect(renderSurf);

            mtx.unlock();
        }

        void render(){
            mtx.lock();

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_Rect srcrect = {0, 0, image->w, image->h};
            SDL_RenderCopy(renderer, texture, &srcrect, &srcrect);

            SDL_RenderPresent(renderer);

            mtx.unlock();
        }

        void printEffects(){
            mtx.lock();

            for(Effect* effect : effects){
                effect->print();
            }

            mtx.unlock();
        }

};

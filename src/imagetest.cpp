#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <iostream>

int main(){
    std::string url = "./assets/images/640x480.bmp";

    SDL_Init(0);

    SDL_Surface* image = SDL_LoadBMP(url.c_str());
    SDL_Window* window = SDL_CreateWindow(
            "window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            image->w,
            image->h,
            SDL_WINDOW_SHOWN
    );
    std::cout << SDL_GetError() << std::endl;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_Rect srcrect = {0, 0, image->w, image->h};
        SDL_RenderCopy(renderer, texture, &srcrect, &srcrect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

}

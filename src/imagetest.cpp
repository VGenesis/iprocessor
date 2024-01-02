#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <string>

#include "glad/include/glad/glad.h"
#include <GL/gl.h>

#define FPS 12

int main(){
    std::string url1 = "./assets/images/640x480.bmp";
    std::string url2 = "./assets/images/abstract2.bmp";

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Surface* image1 = SDL_LoadBMP(url1.c_str());
    SDL_Surface* image2 = SDL_LoadBMP(url2.c_str());
    SDL_Window* window1 = SDL_CreateWindow("image1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image1->w, image1->h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Window* window2 = SDL_CreateWindow("image2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image2->w, image2->h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window1);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, 0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer* renderer2 = SDL_CreateRenderer(window2, 0, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer1, image1);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer2, image2);
    SDL_Rect srcrect1 = {0, 0, image1->w, image1->h};
    SDL_Rect srcrect2 = {0, 0, image1->w, image1->h};

    bool running = true;
    bool window1_running = true;
    bool window2_running = true;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
                if(event.window.windowID == SDL_GetWindowID(window1)){
                    SDL_DestroyWindow(window1);
                    window1_running = false;
                }else{
                    SDL_DestroyWindow(window2);
                    window2_running = false;
                }
                running = window1_running || window2_running;
            }
        }

        SDL_GL_MakeCurrent(window1, context);
        SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
        SDL_RenderClear(renderer1);

        SDL_RenderCopy(renderer1, texture1, &srcrect1, &srcrect1);
        SDL_RenderPresent(renderer1);
        SDL_GL_SwapWindow(window1);

        SDL_GL_MakeCurrent(window2, context);
        SDL_SetRenderDrawColor(renderer2, 0, 0, 0, 255);
        SDL_RenderClear(renderer2);

        SDL_RenderCopy(renderer2, texture2, &srcrect2, &srcrect2);
        SDL_RenderPresent(renderer2);
        SDL_GL_SwapWindow(window2);

    }

    SDL_DestroyWindow(window1);
    SDL_DestroyWindow(window2);

    SDL_Quit();

}

#ifndef MAIN_HPP
#define MAIN_HPP
#include "main.hpp"
#include "glad/include/glad/glad.h"
#include <SDL2/SDL_video.h>
#endif

#ifndef ATOMIC
#define ATOMIC
#include <atomic>
#endif

#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif

#define FPS 24

std::mutex cli_mtx;

void effectCommand(std::vector<std::string> args){
    if(args.empty()){
        std::cout << "Insufficient arguments provided." << std::endl;
        return;
    }

    std::string cmd = args.front();
    int cmdCode = getCode(cmd, effectCommands);
    switch(cmdCode){
        case EFFECT_CREATE:
            break;
        case EFFECT_APPLY:
            break;
        case EFFECT_REMOVE:
            break;
        default:
            break;
    }
}
void applyCommand(std::vector<std::string> args, std::atomic<bool>* running){
    std::string cmd = args.front();
    int cmdCode = getCode(cmd, commands);

    args.erase(args.begin(), args.begin()+1);

    switch(cmdCode){
        case CMD_EXIT:
        case CMD_QUIT:
            running->store(false);
            break;
        case CMD_HELP:
            helpCommand();
            break;
        case CMD_IMAGE:
            imageCommand(args);
            break;
        case CMD_EFFECT:
            effectCommand(args);
            break;
        default:
            cli_mtx.lock();
            std::cout << "Unrecognized command. Type 'help' to view supported commands.\n";
            cli_mtx.unlock();
            break;
    }
}

void cli_init(std::atomic<bool>* running){
    std::vector<std::string> start_cmd ({"image", "read", "assets/images/640x480.bmp"});
    applyCommand(start_cmd, running);
    applyCommand(start_cmd, running);
}

void threadf_cli(std::atomic<bool>* running){
    cli_init(running);
    
    while(running->load()){;
        std::string input;
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> words = strsplit(input);

        std::string cmd = words.front();
        applyCommand(words, running);
        
    }

    cli_mtx.lock();
    std::cout << "CLI Thread Ended." << std::endl;
    cli_mtx.unlock();
}

void GL_init(std::atomic<SDL_GLContext> gl_context, Plot* plot){
    gl_context.store(plot->getWindow());

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void threadf_image_update(std::atomic<bool>* running, std::atomic<SDL_GLContext>* gl_context){
    static long time = SDL_GetTicks64();
    static long prev_time = time;
    static long frametime = time;

    static long tick_ms = 1e3 / FPS;
    static int frames = 0;
    
    while (running->load()) {
        time = SDL_GetTicks64();
        long ms = time - prev_time;
        while(ms > tick_ms){
            for(std::pair<std::string, Plot*> image : images){
                Plot* plot = image.second;
                if(plot->is_running()){
                    SDL_Window* window = plot->getWindow();
                    SDL_GL_MakeCurrent(window, gl_context->load());
                    plot->update();
                    plot->render();
                    SDL_GL_SwapWindow(window);
                }
            }
            ms -= tick_ms;
            frames++;
            prev_time = time;
        }


        if(time - frametime > 1000){
            for(std::pair<std::string, Plot*> image : images){
                Plot* plot = image.second;
                plot->setTitle(image.first, frames);
            }
            
            frames = 0;
            frametime += 1000;
        }

    }

    cli_mtx.lock();
    std::cout << "Image Thread Ended." << std::endl;
    cli_mtx.unlock();
}

int main(){
    static std::atomic<bool> running;
    running.store(true);
    static std::atomic<SDL_GLContext> gl_context;
    gl_context.store(nullptr);

    std::thread cli_thread (threadf_cli, &running);
    std::thread image_thread (threadf_image_update, &running, &gl_context);

    image_thread.join();
    cli_thread.join();


    return 0;

}

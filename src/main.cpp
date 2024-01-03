#ifndef MAIN_HPP
#define MAIN_HPP
#include "main.hpp"
#include "glad/include/glad/glad.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <shared_mutex>
#include <tuple>
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
    std::vector<std::string> start_cmds = {
            "image read assets/images/640x480.bmp img0",
            "image read assets/images/640x480.bmp img1",
            "image read assets/images/640x480.bmp img2",
            "image read assets/images/abstract2.bmp img3",
            "image read assets/images/abstract2.bmp img4",
            "image read assets/images/abstract2.bmp img5",
    };

    for(std::string cmd : start_cmds){
        std::vector<std::string> args = text::strsplit(cmd);
        applyCommand(args, running);
    }
}

void threadf_cli(std::atomic<bool>* running){
    cli_init(running);
    
    while(running->load()){;
        std::string input;
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> words = text::strsplit(input);

        std::string cmd = words.front();

        cli_mtx.lock();
        applyCommand(words, running);
        cli_mtx.unlock();
    }

    cli_mtx.lock();
    std::cout << "CLI Thread Ended." << std::endl;
    cli_mtx.unlock();
}

void GL_init(std::atomic<SDL_GLContext>& gl_context){
    gl_context.store(nullptr);

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
            for(auto image : images){
                Plot* plot = image.second;
                if(plot->is_running()){
                    plot->update();
                    plot->render(gl_context);
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
    GL_init(gl_context);

    std::thread cli_thread (threadf_cli, &running);
    std::thread image_thread (threadf_image_update, &running, &gl_context);

    image_thread.join();
    cli_thread.join();

    delete &cli_thread;
    delete &image_thread;
    delete &images;
    delete &effects;

    return 0;

}

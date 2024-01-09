#ifndef MAIN_HPP
#define MAIN_HPP
#include "main.hpp"
#endif

#define FPS 24

std::mutex cli_mtx;

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
        applyCommand(cmd, running);
    }
}

void threadf_cli(std::atomic<bool>* running){
    cli_init(running);
    
    while(running->load()){;
        std::string cmd;
        std::cout << "> ";
        getline(std::cin, cmd);

        cli_mtx.lock();
        applyCommand(cmd, running);
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

    static long tick_ms = 1e3 / FPS;
    
    while (running->load()) {
        time = SDL_GetTicks64();
        long ms = time - prev_time;
        while(ms > tick_ms){
            updateImages(gl_context);
            ms -= tick_ms;
            prev_time = time;
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

    return 0;

}

#ifndef VECTOR
#define VECTOR
#include <SDL2/SDL_video.h>
#include <vector>
#endif

#ifndef STRING 
#define STRING 
#include <string>
#endif

#ifndef IMAGE_COMMANDS
#define IMAGE_COMMANDS
#include "image_cmds.hpp"
#endif

#ifndef EFFECT_COMMANDS
#define EFFECT_COMMANDS
#include "effect_cmds.hpp"
#endif

#define HELP_FILE "./assets/data/help.txt"

void updateImages(std::atomic<SDL_GLContext>* gl_context);

int getCode(std::string cmd, std::vector<std::string> commands);

void applyCommand(std::string command, std::atomic<bool>* running);
void helpCommand();
void imageCommand(std::vector<std::string> args);
void effectCommand(std::vector<std::string> args);

void exitCommand(std::atomic<bool>* running);

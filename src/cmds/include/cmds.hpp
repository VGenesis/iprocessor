#ifndef SDL_VIDEO
#define SDL_VIDEO
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef OPTIONAL
#define OPTIONAL
#include <optional>
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

void updateImages(std::pair<std::string, std::string>* affect = nullptr);
void renderImages(std::atomic<SDL_GLContext>* gl_context, SDL_Event& e);

int getCode(std::string cmd, std::vector<std::string> commands);

void applyCommand(std::string command, std::atomic<bool>* running);
void helpCommand();
void imageCommand(std::vector<std::string> args);
void effectCommand(std::vector<std::string> args);

void exitCommand(std::atomic<bool>* running);

#ifndef MISC_H
#define MISC_H
#include "misc/include/misc.hpp"
#endif

#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef PLOT_H
#define PLOT_H
#include "image/include/plot.hpp"
#endif

#ifndef EFFECT_H
#define EFFECT_H
#include "image/include/effect.hpp"
#endif

#ifndef EFFECTS
#define EFFECTS
#include "image/include/pixelEffects.hpp"
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

const std::vector<std::string> commands {"exit", "quit", "help", "image", "effect"};
enum Commands{
    CMD_EXIT,
    CMD_QUIT,
    CMD_HELP,
    CMD_IMAGE,
    CMD_EFFECT
};

const std::vector<std::string> imageCommands {"read", "show", "save", "delete"};
enum ImageCommands{
    IMAGE_READ,
    IMAGE_SHOW,
    IMAGE_SAVE,
    IMAGE_DELETE
};


const std::vector<std::string> effectCommands = {"create", "apply", "remove"};
enum EffectCommands{
    EFFECT_CREATE,
    EFFECT_APPLY,
    EFFECT_REMOVE
};

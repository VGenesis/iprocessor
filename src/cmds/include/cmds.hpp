#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING 
#define STRING 
#include <string>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
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

std::unordered_map<std::string, Plot*> images;
std::unordered_map<std::string, Effect*> effects;

const std::vector<std::string> commands {"exit", "quit", "help", "image", "effect"};
enum Commands{
    CMD_EXIT,
    CMD_QUIT,
    CMD_HELP,
    CMD_IMAGE,
    CMD_EFFECT
};

const std::vector<std::string> imageCommands {"read", "show", "list", "save", "delete"};
enum ImageCommands{
    IMAGE_READ,
    IMAGE_SHOW,
    IMAGE_LIST,
    IMAGE_SAVE,
    IMAGE_DELETE
};

const std::vector<std::string> effectCommands = {"create", "apply", "remove"};
enum EffectCommands{
    EFFECT_CREATE,
    EFFECT_APPLY,
    EFFECT_REMOVE
};

int getCode(std::string cmd, std::vector<std::string> commands){
    int cmdCode = 0;
    for(std::string command : commands){
        if(cmd == command)
            return cmdCode;

        cmdCode++;
    }
    return -1;
}

void helpCommand(){
    std::ifstream helpfile;
    helpfile.open(HELP_FILE);

    char c;
    while(helpfile.good()){
        helpfile.get(c);
        std::cout << c;
    }
}

void imageCommand(std::vector<std::string> args){
    if(args.empty()){
        std::cout << "Insufficient arguments provided. 'image' command family requires at least 2." << std::endl;
        return;
    }

    std::string cmd = args.front();
    int cmdCode = getCode(cmd, imageCommands);

    args.erase(args.begin(), args.begin()+1);
    switch(cmdCode){
        case IMAGE_READ:
            imageRead(args, images);
            imageRead({"assets/images/default.bmp", "__default"}, images);
            imageDelete({"__default"}, images);
            break;
        case IMAGE_SHOW:
            imageShow(args, images);
            break;
        case IMAGE_LIST:
            imageList(args, images);
            break;
        case IMAGE_SAVE:
            imageSave(args, images);
            break;
        case IMAGE_DELETE:
            imageDelete(args, images);
            break;
        default:
            std::cout << "Unknown image command. Type 'help to view commands." << std::endl;
            break;
    }
}

void effectCommand(std::vector<std::string> args){
    if(args.empty()){
        std::cout << "Insufficient arguments provided." << std::endl;
        return;
    }

    std::string cmd = args.front();
    args.erase(args.begin(), args.begin()+1);
    int cmdCode = getCode(cmd, effectCommands);
    switch(cmdCode){
        case EFFECT_CREATE:
            effect_create(args, effects);
            break;
        case EFFECT_REMOVE:
            effect_remove(args, effects);
            break;
        default:
            break;
    }
};

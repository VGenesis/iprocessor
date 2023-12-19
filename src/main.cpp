#ifndef MAIN_H
#define MAIN_H
#include "main.hpp"
#include <fstream>
#include <string>
#include <unordered_map>
#endif

std::unordered_map<std::string, Plot> images;
std::unordered_map<std::string, Effect> effects;
bool running = true;

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
    helpfile.open("cmds.txt");

    char c;
    while(helpfile.good()){
        helpfile.get(c);
        std::cout << c;
    }

}

void imageRead(std::vector<std::string> args){
    std::string name = "";
    std::string url = "";

    switch(args.size()){
        case 0:
            std::cout << "Insufficient arguments provided. 'image create' requires at least 3" << std::endl;
            return;
        case 1:
            url = args.front();
            break;
        case 2:
            name = args.front();
            url = (args.begin()+1)->front();
            break;
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
            imageRead(args);
            break;
        case IMAGE_SHOW:
            break;
        case IMAGE_SAVE:
            break;
        case IMAGE_DELETE:
            break;
        default:
            break;
    }
}


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

void applyCommand(std::vector<std::string> args){
    std::string cmd = args.front();
    int cmdCode = getCode(cmd, commands);

    args.erase(args.begin(), args.begin()+1);

    switch(cmdCode){
        case CMD_EXIT:
        case CMD_QUIT:
            running = false;
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
            std::cout << "Unrecognized command. Type 'help' to view supported commands.\n";
            break;
    }

}

int main(){
    std::string input;
    
    while(running){
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> words = strsplit(input);

        std::string cmd = words.front();
        applyCommand(words);
    }
    return 0;

}

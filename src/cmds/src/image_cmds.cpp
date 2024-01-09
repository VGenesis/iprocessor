#ifndef IMAGE_CMDS_HPP
#define IMAGE_CMDS_HPP
#include "../include/image_cmds.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef UNORDERED_LIST
#define UNORDERED_LIST
#include <unordered_map>
#endif


static int img_id = 0;

void imageRead(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){
    std::string name = "";
    std::string url = "";

    switch(args.size()){
        case 0:
            std::cout << "Insufficient arguments provided. 'image create' requires at least 3" << std::endl;
            return;
        case 1:
            url = args[0];
            break;
        case 2:
            name = args[1];
            url = args[0];
            if(images.find(name) != images.end()){
                std::cout << "Image named '" << name << "' already exists" << std::endl;
                return;
            }
            break;
        default:
            std::cout << "Too many arguments provided. Expected 1 or 2 arguments." << std::endl;
            return;
    }

    if(name == ""){
        std::string basename = "img";
        if(images.empty()) {
            name = basename + std::to_string(img_id);
            img_id++;
        }else do{
            name = basename + std::to_string(img_id);
            img_id++;
        }while(images.find(name) != images.end());
    }

    Plot* image = Plot::createInstance(url);
    if(image != nullptr){
        std::pair<std::string, Plot*> newImage (name, image);
        images.insert(newImage);
        if(name != "__default") std::cout << "Created new image '" << name << "'." << std::endl;
    }else{
        std::cout << "Could not load image, invalid path '" << url << "'." << std::endl;
    }
}

void imageShow(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){
    std::string name = "";
    switch(args.size()){
        case 0:
            std::cout << "Insufficient arguments provided. 'image show' requires exactly 1 argument." << std::endl;
            return;
        case 1:
            name = args[0];
            break;
        default:
            std::cout << "Too many arguments(" << args.size() << ") provided. Expected 1 argument." << std::endl;
            return;
    }

    auto hit = images.find(name);
    if(hit != images.end()){
        Plot* plot = hit->second;
        plot->show();
    }else{
        std::cout << "Image '" << name << "' not found." << std::endl;
    }
}

void imageList(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){
    std::cout << "Image list: " << images.size() << " images" << std::endl;
    for(auto iter : images){
        std::cout << "\t" << iter.first << " = " << iter.second->getURL() << std::endl;
    }
}

void imageSave(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){
    std::string name = "";
    std::string url = "";
    switch(args.size()){
        case 0:
        case 1:
            std::cout << "Insufficient arguments provided. 'image save' requires exactly 1 argument." << std::endl;
            return;
        case 2:
            name = args[0];
            url = args[1];
            break;
        default:
            std::cout << "Too many arguments(" << args.size() << ") provided. Expected 1 argument." << std::endl;
            return;
    }

    std::ofstream file(url.c_str());
    file.clear();
    file.close();

    Plot* plot = images.find(name)->second;
    plot->update();
    SDL_SaveBMP(plot->getRenderSurf(), url.c_str());
    std::string err = SDL_GetError();

    if(err == "") std::cout << "Image '" << name << "' saved to file '" << url << "' successfully." << std::endl;
    else std::cout << err << std::endl;
}

void imageDelete(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){
    std::string name = "";
    switch(args.size()){
        case 0:
            std::cout << "Insufficient arguments provided. 'image save' requires exactly 1 argument." << std::endl;
            return;
        case 1:
            name = args[0];
            break;
        default:
            std::cout << "Too many arguments(" << args.size() << ") provided. Expected 1 argument." << std::endl;
            return;
    }

    auto deleted_image = images.find(name);
    if(deleted_image->second->is_running()){
        printf("Failed to remove image '%s': image is currently being shown\n", name.c_str());
    } else if(deleted_image != images.end()){
        if(name != "__default") printf("Image '%s' removed successfully\n", name.c_str());
        images.erase(name);
    } else{
        printf("Failed to remove image '%s': image not loaded\n", name.c_str());
    }
}

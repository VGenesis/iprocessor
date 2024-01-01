#ifndef IMAGE_CMDS_HPP
#define IMAGE_CMDS_HPP
#include "../include/image_cmds.hpp"
#include <ostream>
#include <string>
#include <unordered_map>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
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
            url = args[0];
            name = args[1];
            if(images.find(name) != images.end()){
                std::cout << "Image named '" << name << "' already exists" << std::endl;
                return;
            }
            break;
        default:
            std::cout << "Too many arguments provided. Expected 1 or 2 arguments." << std::endl;
            return;
    }

    std::string basename = "img";
    if(images.empty()) {
        name = basename + std::to_string(img_id);
        img_id++;
    }else while(images.find(basename + std::to_string(img_id)) != images.end()){
        img_id++;
    }

    Plot* image = Plot::createInstance(url);
    if(image != nullptr){
        std::pair<std::string, Plot*> newImage (name, image);
        images.insert(newImage);
        std::cout << "Created new image '" << name << "'." << std::endl;
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
    for(std::unordered_map<std::string, Plot*>::iterator iter = images.begin(); iter != images.end(); iter++){
        std::cout << "\t" << iter->first << " = " << iter->second->getURL() << std::endl;
    }
}

void imageSave(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){

}

void imageDelete(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images){

}

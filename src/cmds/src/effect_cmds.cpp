#ifndef CMDS_H
#define CMDS_H
#include "../../cmds/include/cmds.hpp"
#include <optional>
#endif

#ifndef EFFECT_CMDS
#define EFFECT_CMDS
#include "../include/effect_cmds.hpp"
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef PIXELEFFECT_H
#define PIXELEFFECT_H
#include "../../image/include/pixelEffects.hpp"
#endif

const std::vector<std::string> noarg_effects = {"grayscale", "hist", "fft"};
enum NoargEffectType{
    EFF_GRAYSCALE,
    EFF_HIST,
    EFF_FFT
};

void effect_create_noargs(std::string name, std::string type, std::unordered_map<std::string, Effect*>& effects){
    NoargEffectType efftype = (NoargEffectType) (std::find(noarg_effects.begin(), noarg_effects.end(), type) - noarg_effects.begin());
    
    switch(efftype){
        case EFF_GRAYSCALE:
            effects.insert({name, new GrayscaleEffect(name.c_str())});
            break;
        case EFF_HIST:
            effects.insert({name, nullptr}); 
            break;
        case EFF_FFT:
            effects.insert({name, nullptr}); 
            break;
    }
}

const std::vector<std::string> warg_effects = {"colorfilter", "intensity"};
enum WargEffectType {
   EFF_COLORFILTER,
   EFF_INTENSITY
};

void effect_create_colorfilter(std::string name, std::vector<std::string> args, std::unordered_map<std::string, Effect*>& effects){
    if(args.size() < 3){
        printf("Insufficient arguments provided for 'colorfilter' effect. Required 3 arguments.\n");
    }else{
        printf("%s", args[0].c_str());
        float r = stof(args[0]);
        float g = stof(args[1]);
        float b = stof(args[2]);
        effects.insert({name, new ColorFilterEffect(name.c_str(), r, g, b)});
    }
}

void effect_create_intensity(std::string name, std::vector<std::string> args, std::unordered_map<std::string, Effect*>& effects){
    if(args.size() < 1){
        printf("Insufficient arguments provided for 'intensity' effect. Required 1 arguments.\n");
    }else{
        if(args[0][0] == '+' || args[0][0] == '-'){
            int transform = stoi(args[0]);
            effects.insert({name, new IntensityEffect(name.c_str(), transform)});
        }else{
            float scale = stof(args[0]);
            effects.insert({name, new IntensityEffect(name.c_str(), scale)});
        }
    }
}

void effect_create_withargs(std::string name, std::string type, std::vector<std::string> args, std::unordered_map<std::string, Effect*>& effects){
    WargEffectType efftype = (WargEffectType) (std::find(warg_effects.begin(), warg_effects.end(), type) - warg_effects.begin());

    switch(efftype){
        case EFF_COLORFILTER:
            effect_create_colorfilter(name, args, effects);
            break;
        case EFF_INTENSITY:
            effect_create_intensity(name, args, effects);
            break;
    }
}

void effect_create(std::vector<std::string> args, std::unordered_map<std::string, Effect*>& effects){
    std::string name = "";
    std::string type = "";

    switch(args.size()){
        case 0:
        case 1:
            printf("Insufficient arguments provided. Command 'effect create' requires at least 2.\n");
            return;
        case 2:
            name = args[0];
            type = args[1];
            effect_create_noargs(name, type, effects);
            printf("Created %s effect '%s'.\n", type.c_str(), name.c_str());
            break;
        default:
            name = args[0];
            type = args[1];
            args.erase(args.begin(), args.begin()+1);
            effect_create_withargs(name, type, args, effects);
            printf("Created %s effect '%s'.\n", type.c_str(), name.c_str());
            break;
    }
}

void effect_apply(std::vector<std::string> args, std::unordered_map<std::string, Effect *>& effects){
    std::pair<std::string, std::string>* affect;

    switch(args.size()){
        case 0:
        case 1:
            printf("Insufficient arguments provided. Command 'effect apply' requires exactly 2 arguments.\n");
            return;
        case 2:
            affect->first = args[0];
            affect->second = args[1];
            updateImages(affect);
            break;
        default:
            printf("Too many arguments provided. Command 'effect apply' requires exactly 2 arguments.\n");
            return;
    }
}

void effect_list(std::vector<std::string> args, std::unordered_map<std::string, Effect *>& effects){
    for(auto pair : effects){
        Effect* effect = pair.second;
        effect->print();
    }
}

void effect_remove(std::vector<std::string> args, std::unordered_map<std::string, Effect*>& effects){
    std::string name = "";
    switch(args.size()){
        case 0:
            printf("Insufficient arguments provided. Command 'effect remove' requires 1 argument.\n");
            return;
        case 1:
            name = args[0];
            break;
        case 2:
            printf("Too many arguments provided. Command 'effect remove' requires 1 argument.\n");
            return;
    }

    if(effects.find(name) != effects.end()){
        effects.erase(name);
        printf("Effect '%s' successfully removed.\n", name.c_str());
    }else{
        printf("Failed to remove effect '%s': effect does not exist.\n", name.c_str());
    }
}

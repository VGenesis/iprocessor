#ifndef EFFECT_CMDS
#define EFFECT_CMDS
#include "../include/effect_cmds.hpp"
#include <stdexcept>
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

void effect_create_noargs(std::string name, std::string type, std::unordered_map<std::string, Effect*> effects){
    NoargEffectType efftype = (NoargEffectType) (std::find(noarg_effects.begin(), noarg_effects.end(), type) - noarg_effects.begin());
    
    switch(efftype){
        case EFF_GRAYSCALE:
            effects.insert({name, new GrayscaleEffect(name.c_str())});
            break;
        case EFF_HIST:
            break;
        case EFF_FFT:
            break;
    }
}

const std::vector<std::string> warg_effects = {"colorfilter", "intensity"};
enum WargEffectType {
   EFF_COLORFILTER,
   EFF_INTENSITY
};

void effect_create_withargs(std::string name, std::string type, std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects){
    WargEffectType efftype = (WargEffectType) (std::find(warg_effects.begin(), warg_effects.end(), type) - warg_effects.begin());

    switch(efftype){
        case EFF_COLORFILTER:
            break;
        case EFF_INTENSITY:
            break;
    }
}

void create_effect_colorfilter(std::string name, std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects){
    if(args.size() != 3){
        printf("Invalid argument count. Command 'create effect colorfilter' requires 3 arguments.\n");
    }else{
        try{
            double r = stof(args[0]);
            double g = stof(args[1]);
            double b = stof(args[2]);

            effects.insert({name, new ColorFilterEffect(name.c_str(), r, g, b)});
        }catch(std::invalid_argument e){
            printf("%s", e.what());
        }
    }
}

void create_effect_intensity(std::string name, std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects){
    if(args.size() != 2){
        printf("Invalid argument count. Command 'create effect colorfilter' requires 2 arguments.\n");
    }else{
        try{
            std::string efftype = args[0];

            if(efftype[0] == '+' | efftype[0] == '-'){
                bool neg = (efftype[0] == '-')? true : false;
                efftype.erase(efftype.begin(), efftype.end());
                int transform = std::stoi(efftype) * (-1)^neg;
                effects.insert({name, new IntensityEffect(name.c_str(), transform)});
            }else{
                float scale = std::stof(efftype);
                effects.insert({name, new IntensityEffect(name.c_str(), scale)});
            }
        }catch(std::invalid_argument e){
            printf("%s", e.what());
        }
    }
}

void effect_create(std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects){
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
            break;
        default:
            name = args[0];
            type = args[1];
            args.erase(args.begin(), args.begin()+1);
            effect_create_withargs(name, type, args, effects);
            break;
    }
}

void effect_remove(std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects){
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

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
#endif

#ifndef EFFECT_H
#define EFFECT_H
#include "../../image/include/effect.hpp"
#endif

void effect_create(std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects);
void effect_remove(std::vector<std::string> args, std::unordered_map<std::string, Effect*> effects);

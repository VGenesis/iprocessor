#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING 
#define STRING 
#include <string>
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
#endif

#ifndef PLOT_HPP
#define PLOT_HPP
#include "../../image/include/plot.hpp"
#endif

void imageRead(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images);
void imageShow(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images);
void imageList(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images);
void imageSave(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images);
void imageDelete(std::vector<std::string> args, std::unordered_map<std::string, Plot*>& images);

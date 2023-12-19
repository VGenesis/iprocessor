#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

std::vector<std::string> strsplit(std::string str){
    std::vector<std::string> words; 
    int pos = 0;
    while(pos != -1){
        int split_pos = str.find(" ", pos);
        std::string substr = str.substr(pos, split_pos - pos);
        words.push_back(substr);
        
        pos = (split_pos == -1)? split_pos : split_pos+1;
    }
    return words;
}

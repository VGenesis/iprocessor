#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> strsplit(std::string str){
    std::vector<std::string> words; 
    int pos = 0;
    while(pos != -1){
        int split_pos = str.find(" ", pos);
        std::string substr = str.substr(pos, split_pos - pos);
        words.push_back(substr);
        
        pos = (split_pos == -1)? split_pos : split_pos+1;
        std::cout << pos << std::endl;


    }
    return words;
}

int main(){
    std::string line = "123 234 345 456";
    std::vector<std::string> words = strsplit(line);
    for(std::string word : words){
        std::cout << word << std::endl;
    }
    return 0;

}

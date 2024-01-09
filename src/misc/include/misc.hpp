#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

namespace text{
    std::vector<std::string> strsplit(std::string str);
}

namespace math{
    template <typename D>
        D clamp(D value, D min, D max){
            if(value > max) return max;
            else if(value < min) return min;
            else return value;
        }   
}

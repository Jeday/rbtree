#include "text_stat.h"


/// comparator for string and counter
class comp{
typedef std::pair<std::string,unsigned long> pr;
public:
    bool operator()(pr t, pr t1){
        return t<t1;
    }
};




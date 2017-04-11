
#include "rb_multi_set.h"
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[])
{
    multiset<int> s;
    s.insert(4);
    s.insert(2);
    s.insert(6);
    s.insert(8);
    s.insert(4);
    s.insert(4);
    s.insert(6);
    s.insert(10);

    auto it = s.begin();
    while(it !=  s.end())
      std::cout<<*(++it)<< " ";

    s.clear();
    std::cout<<s.empty();

}

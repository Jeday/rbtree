#include <iostream>
#include "rb_multi_set.h"
using namespace std;

int main(int argc, char *argv[])
{
    multiset<int> s;
    s.insert_value(1);

    s.insert_value(2);

    s.insert_value(3);

    s.insert_value(4);

    s.insert_value(5);

    s.delete_value(3);


}

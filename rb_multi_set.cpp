#include "rb_multi_set.h"
#include "ctime"
#include "set"
void time_test(){
   time_t start;
   time_t time_passed;
   double res;
   std::set<int> st;
   multiset<int> mst;

   start = clock();
   for(int i = 0; i< 10000;++i){
           st.insert(rand());
       }
   time_passed = clock();
   res = double(time_passed-start)/CLOCKS_PER_SEC;




}


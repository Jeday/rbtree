#include "rb_multi_set.h"
#include <ctime>
#include <set>
#include <iostream>

void time_test(int cnt){
   time_t start;
   time_t time_passed;
   double res;
   std::set<int> st;
   deb_multiset<int> mst;

   start = clock();
   for(int i = 0; i< cnt;++i){
           st.insert(rand());
       }
   time_passed = clock();
   res = double(time_passed-start)/CLOCKS_PER_SEC;

   double mt_res;
   start = clock();
   for(int i = 0; i< cnt;++i){
           mst.insert(rand());
       }
   time_passed = clock();
   mt_res = double(time_passed-start)/CLOCKS_PER_SEC;

   std::cout<<"Time test for "<<cnt<<" insertions of rand int"<<std::endl;
   std::cout<<"Set :"<<res<<" sec."<<'\n'<<"Multiset : "<<mt_res<<" sec. with "<< mst.left_rotations()+mst.right_rotations()<<" rotations"<<std::endl;

}


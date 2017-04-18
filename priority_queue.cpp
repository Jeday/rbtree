#include "priority_queue.h"
#include "deque"
#include <iostream>

void test_pq(){
    fixed_Priority_queue<int> pq(10);
    fixed_Priority_queue<int> d_pq(10);
    for(int i = 0; i<100; ++i){
            pq.push(i);
            d_pq.push(i);
        }
    while(!pq.empty() || !d_pq.empty()){
            if(pq.top() != d_pq.top())
                std::cout<<"ERROR ";
            else
                std::cout<<pq.top()<<" ";
            pq.pop();
            d_pq.pop();
        }


}

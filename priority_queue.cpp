#include "priority_queue.h"
#include "deque"
#include <iostream>

void test_pq(int d){
    Priority_queue<int> pq;
    Priority_queue<int> d_pq;
    for(int i = 0; i<d; ++i){
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

    std::cout<<std::endl;

    fixed_Priority_queue<int> _pq(20);
    for(int i = 0; i<d; ++i){
            _pq.push(i);
        }
    pq.build_heap();
    while(!_pq.empty()){
            std::cout<<_pq.top()<<" ";
            _pq.pop();
        }

    std::cout<<std::endl;



}

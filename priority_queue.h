#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include <algorithm>

std::push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last){}


template <class T, class Container = std::vector<T>, class Compare= std::less<typename Container::value_type> > class Priority_queue {
    Container A;
    using sz_t = Container::size_type;
    sz_t heap_size;


    void heapify(sz_t i){
      sz_t left = 2*i;
      sz_t right = 2*i+1;
      sz_t largest = i;
      if (left <= heap_size && A[left] > A[largest])
        largest = left;
      if (right <= heap_size && A[right] > A[largest])
        largest = right;
      if (largest != i){
          std::swap(A[i], A[largest]);
          heapify(largest);
          }
    }

    void build_heap(){
      heap_size = A.size();
      for(sz_t i = heap_sizep/2; i >= 1; --i)
         heapify(i);
    }



public:
    Priority_queue(){
        A = Container();
        heap_size = 0;
    }


    };

#endif // PRIORITY_QUEUE_H

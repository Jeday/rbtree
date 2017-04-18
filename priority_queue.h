#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include <algorithm>




template <class T, class Container = std::vector<T>, class Compare= std::less<typename Container::value_type> >
class Priority_queue {
    Container A;
    typedef typename Container::size_type sz_t;
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
      for(sz_t i = heap_size/2; i >= 1; --i)
         heapify(i);
    }




    void heap_insert(T key){
        heap_size+=1;
        sz_t i = heap_size;
        while(i>1 && A[i/2]<key){
                A[i] = A[i/2];
                i = i/2;
            }
        A[i] = key;
    }

    void heap_extract_max(){
        if(heap_size<1)
            return;
        A[1] = A[heap_size];
        heap_size = heap_size -1;
        heapify(1);
    }



public:
    Priority_queue(){
        A = Container();
        heap_size = 0;
    }

    T top(){return A[1];}

    void pop(){
        heap_extract_max();
    }

    void push(const T&k){
        heap_insert(k);
    }

    bool empty(){return heap_size<1;}



    };

void test_pq();

#endif // PRIORITY_QUEUE_H

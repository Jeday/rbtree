#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include <algorithm>






template <class T, class Container = std::vector<T>,class _Compare
          = std::less<typename Container::value_type> >
class Priority_queue {
protected:
      _Compare Compare;
    Container A;
    typedef typename Container::size_type sz_t;
    sz_t heap_size;


    void heapify(sz_t i){
      sz_t left = 2*i;
      sz_t right = 2*i+1;
      sz_t largest = i;
      if (left <= heap_size && Compare(A[left-1], A[largest-1]))
        largest = left;
      if (right <= heap_size && Compare(A[right-1], A[largest-1]))
        largest = right;
      if (largest != i){
          std::swap(A[i-1], A[largest-1]);
          heapify(largest);
          }
    }

    void build_heap(){
      heap_size = A.size();
      for(sz_t i = heap_size/2; i >= 1; --i)
         heapify(i);
    }




  virtual  void heap_insert(T key){
        heap_size+=1;
        sz_t i = heap_size;
        A.resize(heap_size);
        while(i>1 && Compare(A[(i)/2-1],key)){
                A[i-1] = A[i/2-1];
                i = i/2;
            }
       // A.resize(heap_size);
        A[i-1] = key;
        heapify(i);
    }
    void heap_extract_max(){
        if(heap_size<1)
            return;
        A[0] = A[heap_size-1];
        heap_size = heap_size -1;
        heapify(1);
    }



public:
    Priority_queue(){
        A = Container();
        heap_size = 0;
    }

    const T& top(){ return A[0];}

    void pop(){
        heap_extract_max();
    }

    void push(const T&k){
        heap_insert(k);
    }

    bool empty(){return heap_size<1;}


    };

template <class T,class _Compare
          = std::less<T> >
class fixed_Priority_queue {
protected:
    _Compare Compare;
    T *A;
    typedef size_t sz_t;
    sz_t heap_size;
    sz_t max_sz;


    void heapify(sz_t i){
      sz_t left = 2*i;
      sz_t right = 2*i+1;
      sz_t largest = i;
      if (left <= heap_size && Compare( A[left-1], A[largest-1]))
        largest = left;
      if (right <= heap_size && Compare(A[right-1], A[largest-1]))
        largest = right;
      if (largest != i){
          std::swap(A[i-1], A[largest-1]);
          heapify(largest);
          }
    }

    void build_heap(){
      heap_size = max_sz;
      for(sz_t i = heap_size/2; i >= 1; --i)
         heapify(i);
    }




  virtual  void heap_insert( const T &key){
        if (heap_size == max_sz)
            return;
        heap_size+=1;
        sz_t i = heap_size;
        while(i>1 && Compare(A[i/2-1],key)){
                A[i-1] = A[i/2-1];
                i = i/2;
            }
       // A.resize(heap_size);
        A[i-1] = key;
        heapify(i);
    }
    void heap_extract_max(){
        if(heap_size<1)
            return;
        A[0] = A[heap_size-1];
        heap_size = heap_size -1;
        heapify(1);
    }



public:
    fixed_Priority_queue(size_t mx){
        max_sz = mx;
        A = new T[mx];
        heap_size = 0;
    }

    const T& top(){ return A[0];}

    void pop(){
        heap_extract_max();
    }

    void push(const T&k){
        heap_insert(k);
    }

    bool empty(){return heap_size<1;}




    ~fixed_Priority_queue(){
    delete[] A;
}
    };

void test_pq(int);

#endif // PRIORITY_QUEUE_H

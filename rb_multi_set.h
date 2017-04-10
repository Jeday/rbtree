#ifndef RB_MULTI_SET_H
#define RB_MULTI_SET_H

#include <utility>
#include <iterator>

template<typename key_type>
class multiset{

    typedef key_type  value_type;

    /// color alias
     static const bool BLACK =false;
     static const bool RED = true;

    class node;

    using pair_type = std::pair<key_type,value_type>;

    /// _NLL black leaf
    node * _NLL;

    /// root node of rbtree
    node * root;
    /*
        node class
    */
    class node{
    public:
        pair_type data;
        node * left;
        node * right;
        node * parent;
        bool color;

        node(pair_type _data,node * _left = nullptr, node * _right = nullptr,node * _parent = nullptr, bool _color = BLACK):
            data(_data),
            left(_left),
           right(_right),
            color(_color),
            parent(_parent)
       {}

        /// _NLL constructor of BLACK leaf with uninit data
        node(node * p):
            left(nullptr),
            right(nullptr),
            parent(p),
            color(BLACK)
       {}


    };


public:
    multiset(){
        _NLL = new node(_NLL);
        _NLL->left= _NLL;
        _NLL->right = _NLL;
        _NLL->parent = _NLL;
        root = _NLL;


    }

private:

     node *grandparent(node *n) const
    {
     if (n == _NLL || n->parent == _NLL) {
         return _NLL;
     }

      return n->parent->parent;

    }

     node *uncle( node *n) const
     {
       node *g = grandparent(n);
      if (g == _NLL)
       return _NLL;
      if (n->parent == g->left)
       return g->right;
      else
       return g->left;
     }

     node * sibling( node *n) const
      {
          if (n == n->parent->left)
              return n->parent->right;
          else
              return n->parent->left;
      }

     bool is_leaf(node * n)const {
        return (n->right == _NLL) && (n->left == _NLL);
     }


     /// insert value as usual
     void insert_value(const key_type &v){
        node * n;
     node* r = root;
     if (r != _NLL)
         while(r != _NLL){
             if (less_than(v,r->data)){
                 if(r->left != _NLL)
                     r = r->left;
                 else {
                     r->left = new node ({v,v},_NLL,_NLL,r);
                     n=r->left;
                     r = _NLL;
                 }

             }
             else
             {
                 if(r->right != _NLL)
                     r = r->right;
                 else {
                     r->right = new node ({v,v},_NLL,_NLL,r);
                     n =r->right;
                     r = _NLL;
                 }

             }
         }
       else {root = new node ({v,v},_NLL,_NLL,_NLL,BLACK);
             _NLL->left = root;
             _NLL->right = root;
       return;
                 }
                 insert_case1(r);
     }


      void rotate_left( node *n)
      {
           node *pivot = n->right;

          pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
          if(pivot->parent == _NLL)
              set_root(pivot);

          if (n->parent != _NLL) {
              if (n->parent->left==n)
                  n->parent->left = pivot;
              else
                  n->parent->right = pivot;
          }

          n->right = pivot->left;
          if (pivot->left != _NLL)
              pivot->left->parent = n;

          n->parent = pivot;
          pivot->left = n;
      }

      void rotate_right( node *n)
      {
           node *pivot = n->left;

          pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
          if(pivot->parent == _NLL)
              set_root(pivot);
          if (n->parent != _NLL) {
              if (n->parent->left==n)
                  n->parent->left = pivot;
              else
                  n->parent->right = pivot;
          }

          n->left = pivot->right;
          if (pivot->right != _NLL)
              pivot->right->parent = n;

          n->parent = pivot;
          pivot->right = n;
      }

      bool less_than(const pair_type & f,const pair_type & s){
          return (f.first<s.first);
      }

      void insert_case1(node  *n)
      {
       if (n->parent == _NLL)
        n->color = BLACK;
       else
        insert_case2(n);
      }

      void insert_case2( node *n)
      {
          if (n->parent->color == BLACK)
              return; /* Tree is still valid */
          else
              insert_case3(n);
      }

      void  insert_case3( node *n)
      {
           node *u = uncle(n), *g;

          if ((u != _NLL) && (u->color == RED) && (n->parent->color == RED)) {
              n->parent->color = BLACK;
              u->color = BLACK;
              g = grandparent(n);
              g->color = RED;
              insert_case1(g);
          } else {
              insert_case4(n);
          }
      }

      void  insert_case4( node *n)
      {
           node *g = grandparent(n);

          if ((n == n->parent->right) && (n->parent == g->left)) {
              rotate_left(n->parent);
              n = n->left;
          } else if ((n == n->parent->left) && (n->parent == g->right)) {
              rotate_right(n->parent);
              n = n->right;
          }
          insert_case5(n);
      }

      void  insert_case5( node *n)
      {
           node *g = grandparent(n);

          n->parent->color = BLACK;
          g->color = RED;
          if ((n == n->parent->left) && (n->parent == g->left)) {
              rotate_right(g);
          } else {
              rotate_left(g);
          }
      }


      node * next(node * r ) const {

            if(r->parent!= _NLL && r->parent->left == r)
                return r->parent;
            else if(r->right != _NLL){
                  r = r->right;
                  while(r->left != _NLL)
                      r =r->left;
                  return r;
              }
            else
                return _NLL;

      }
      node * prev(node * r ) const  {
          if(r->left != _NLL){
                r = r->left;
                while(r->right != _NLL)
                    r =r->right;
                return r;
            }
            else if(r->parent != _NLL && r->parent->right == r)
                return r->parent;
            else
                return _NLL;

      }


      bool swap_left (node*  t){

        node* other = t->left;
          if (other != _NLL){
              /// change right childs
              /// other has right
              if(other->right){
                 /// t has right
                  if(t->right)
                     std::swap(other->right->parent,t->right->parent);
                  /// t has no right
                  else{
                    other->right->parent = t;
                 }
              }
              /// other has no right
              else{
                  /// t has right
                  if(t->right != _NLL)
                     t-> right->parent = other;
                  /// t has no right
                  /// do nothing
              }
              std::swap(other->right,t->right);

              t->left = other->left;
              if(other->left != _NLL){

                  other->left->parent = t;
              }

              other->parent  = t->parent;
              if(t->parent != _NLL){
                  if(t->parent->left == t)
                      t->parent->left = other;
                  else t->parent->right = other;
              }

              other->left = t;
              t->parent = other;

              return true;
        } else
          {
             return false;

          }

      }

      void set_root(node * r){
          _NLL->left = r;
          _NLL->right =r;
          root = r;
      }

      void free(node * r){
          if(r->parent !=_NLL){
              if(r->parent->left =r)
                  r->parent->left = _NLL;
               if(r->parent->right =r)
                   r->parent->right = _NLL;
          }
          delete r;

      }

      bool swap_right(node*  t){
          std::swap(t->right,t->left);
          bool res = swap_left(t);
          std::swap(t->parent->left,t->parent->right);
          return res;
      }


      void  delete_one_child( node *n)
      {
          if (n == root)
            set_root(n->left);
            while(swap_left(n)){}
            root->parent= _NLL;

           node *child;
           if (is_leaf(n->right)){
               child = n->left;
               swap_left(n);
           }
           else {
               child = n->right;
               swap_right(n);
           }
          if (n->color == BLACK) {
              if (child->color == RED)
                  child->color = BLACK;
              else
                  delete_case1(child);
          }
          free(n);
      }

      void  delete_case1( node *n)
      {
          if (n->parent != _NLL)
              delete_case2(n);
      }

      void delete_case2( node *n)
      {
           node *s = sibling(n);

          if (s->color == RED) {
              n->parent->color = RED;
              s->color = BLACK;
              if (n == n->parent->left)
                  rotate_left(n->parent);
              else
                  rotate_right(n->parent);
          }
          delete_case3(n);
      }

      void delete_case3( node *n)
      {
           node *s = sibling(n);

          if ((n->parent->color == BLACK) &&
              (s->color == BLACK) &&
              (s->left->color == BLACK) &&
              (s->right->color == BLACK)) {
              s->color = RED;
              delete_case1(n->parent);
          } else
              delete_case4(n);
      }

      void delete_case4( node *n)
      {
           node *s = sibling(n);

          if ((n->parent->color == RED) &&
              (s->color == BLACK) &&
              (s->left->color == BLACK) &&
              (s->right->color == BLACK)) {
              s->color = RED;
              n->parent->color = BLACK;
          } else
              delete_case5(n);
      }

      void delete_case5( node *n)
      {
           node *s = sibling(n);

          if  (s->color == BLACK) { /* this if statement is trivial,
      due to case 2 (even though case 2 changed the sibling to a sibling's child,
      the sibling's child can't be red, since no red parent can have a red child). */
      /* the following statements just force the red to be on the left of the left of the parent,
         or right of the right, so case six will rotate correctly. */
              if ((n == n->parent->left) &&
                  (s->right->color == BLACK) &&
                  (s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
                  s->color = RED;
                  s->left->color = BLACK;
                  rotate_right(s);
              } else if ((n == n->parent->right) &&
                         (s->left->color == BLACK) &&
                         (s->right->color == RED)) {/* this last test is trivial too due to cases 2-4. */
                  s->color = RED;
                  s->right->color = BLACK;
                  rotate_left(s);
              }
          }
          delete_case6(n);
      }

      void delete_case6( node *n)
      {
           node *s = sibling(n);

          s->color = n->parent->color;
              n->parent->color = BLACK;

          if (n == n->parent->left) {
                      s->right->color = BLACK;
              rotate_left(n->parent);
          } else {
              s->left->color = BLACK;
              rotate_right(n->parent);
          }
      }

      node *find_node(const value_type  &  v, node * r = nullptr) const  {
          if(r == nullptr)
              r = root;
          while(r != _NLL){
              if(r->data.first < v){
                  r = r->right;
              }
              else {
                  r = r->left;
              }
               return r;
          }
          return _NLL;
      }

      iterator::difference_type delete_value(key_type&  v){
          node * r = find_node(v);
          if (r != _NLL){
              delete_one_child(r);
              return 1+delete_value(v);
          }
          else
          {return 0;}
      }

public:

      class iterator
      {
          public:
              typedef iterator self_type;
              typedef pair_type& reference;
              typedef node* pointer;
              typedef std::bidirectional_iterator_tag iterator_category;
              typedef size_t difference_type;

              iterator(node * ptr) : ptr_(ptr) { }
              self_type operator++() { self_type i = *this; ptr_ = next(ptr_); return i; }
              self_type operator++(int junk) { ptr_=next(ptr_); return *this; }
              self_type operator--() { self_type i = *this; ptr_=prev(ptr_); return i; }
              self_type operator--(int junk) { ptr_=prev(ptr_); return *this; }
              reference operator*() { return ptr_->data; }
              self_type operator+(difference_type c){
                  self_type it = *this;
                  for(difference_type i = 0; i<c;++i ) ++it; return it; }
              //pointer operator->() { return ptr_; }
              bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
              bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
          private:
             node *  ptr_;
      };

      class const_iterator
      {
          public:
              typedef const_iterator self_type;
              typedef pair_type& reference;
              typedef node* pointer;
              typedef std::bidirectional_iterator_tag iterator_category;
              typedef size_t difference_type;

              const_iterator(node * ptr) : ptr_(ptr) { }
              self_type operator++() { self_type i = *this; ptr_ = next(ptr_); return i; }
              self_type operator++(int junk) { ptr_=next(ptr_); return *this; }
              self_type operator--() { self_type i = *this; ptr_=prev(ptr_); return i; }
              self_type operator--(int junk) { ptr_=prev(ptr_); return *this; }
              const reference operator*() { return ptr_->data; }
              self_type operator+(difference_type c){
                  self_type it = *this;
                  for(difference_type i = 0; i<c;++i ) ++it; return it; }
              //const pointer operator->() { return ptr_; }
              bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
              bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
          private:
             node *  ptr_;
      };

      iterator begin()
              {
                  auto r = root;
                  while(r->left)
                      r = r->left;
                  return iterator(r);
              }

              iterator end()
              {
                  return iterator(_NLL);
              }

              const_iterator cbegin() const
              {
                  auto r = root;
                  while(r->left)
                      r = r->left;
                  return const_iterator(r);
              }

              const_iterator cend() const
              {
                  return const_iterator(_NLL);
              }


              iterator lower_bound(key_type v){
                  node * r = root;
                  node * f = find_node({v,v});
                  if (f != _NLL)
                     return iterator(f);
                  else {
                         if (r == _NLL)
                             return iterator(r);
                         while(r!= _NLL){
                                 if (v <r->data.first){
                                    if (r->left != _NLL)
                                        r = r->left;
                                     else
                                        return iterator(r);
                                     }
                                 else {
                                         if (r->right != _NLL)
                                             r = r->right;
                                          else
                                             return iterator(r);

                                     }

                             }

                      }
              }

              iterator upper_bound(key_type v){
                  node * r = root;
                  node * f = find_node({v,v});
                  if (f != _NLL){
                          while(f->data.first == v)
                              f = next(f);
                          return f;
                      }
                  else {
                          if (r == _NLL)
                              return iterator(r);
                          while(r!= _NLL){
                                  if (v <r->data.first){
                                     if (r->left != _NLL)
                                         r = r->left;
                                      else
                                         return iterator(next(r));
                                      }
                                  else {
                                          if (r->right != _NLL)
                                              r = r->right;
                                           else
                                              return iterator(next(r));

                                      }

                              }


                      }
              }

              void insert(const key_type& v){
                  insert_value(v);
              }

              iterator find(const key_type&v) const{
                  return iterator(find_node(v,nullptr));
              }

              iterator::difference_type count(const key_type&v) const {
                  iterator it = find(v);
                  iterator::difference_type c = 0;
                  while(it != this->end()){
                      ++c;
                      iterator t = it+1;
                      if(t == _NLL || *t != *it)
                          return c;
                      }
                  return c; // c is 0;

              }

              void erase(const key_type& v){
                  return delete_value(v);
              }



};





#endif // RB_MULTI_SET_H
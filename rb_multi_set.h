#ifndef RB_MULTI_SET_H
#define RB_MULTI_SET_H

#include <utility> // swap
#include <iterator> // iterator traits
#include <ostream> // for stream writting
#include <string> // for delim
#include <functional>

template<typename key_type,class _Compare
         = std::less<key_type>>
class multiset{
protected:
    typedef key_type  value_type;
    typedef std::pair<key_type,size_t> pair_type;


    _Compare Compare;
    /// color alias
      //const bool BLACK = false;
    //  const bool RED = true;

    class node;

   // using pair_type = std::pair<key_type,value_type>;

    /// _NLL false leaf
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

        node(pair_type _data,node * _left = nullptr, node * _right = nullptr,node * _parent = nullptr, bool _color = false):
            data(_data),
            left(_left),
           right(_right),
            color(_color),
            parent(_parent)
       {}

        /// _NLL constructor of false leaf with uninit data
        node(node * p):
            left(nullptr),
            right(nullptr),
            parent(p),
            color(false)
       {}


    };


public:
    multiset(){
        _NLL = new node({value_type(),0});
        _NLL->left= _NLL;
        _NLL->right = _NLL;
        _NLL->parent = _NLL;
        root = _NLL;


    }

protected:

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
     virtual void insert_value(const key_type &v){

         node * n;
    node*      r = root;
     if (r != _NLL)
         while(r != _NLL){
             if (Compare(v,r->data.first)){
                 if(r->left != _NLL)
                     r = r->left;
                 else {
                     r->left = new node ({v,1},_NLL,_NLL,r,true);
                     n=r->left;
                     r = _NLL;
                 }

             }
             else if (!Compare(r->data.first,v)){
                     r->data.second+=1;
                     return;
                 }
             else
             {
                 if(r->right != _NLL)
                     r = r->right;
                 else {
                     r->right = new node ({v,1},_NLL,_NLL,r,true);
                     n =r->right;
                     r = _NLL;
                 }

             }
         }
       else {
                root = new node ({v,1},_NLL,_NLL,_NLL,true);
             _NLL->left = root;
             _NLL->right = root;
            n = root;

                 }
                 insert_case1(n);
     }

       /// virtual for counting in child class
      virtual  void rotate_left( node *n)
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
       /// *same*
      virtual  void rotate_right( node *n)
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


      void insert_case1(node  *n)
      {
       if (n->parent == _NLL)
        n->color = false;
       else
        insert_case2(n);
      }

      void insert_case2( node *n)
      {
          if (n->parent->color == false)
              return; /* Tree is still valid */
          else
              insert_case3(n);
      }

      void  insert_case3( node *n)
      {
           node *u = uncle(n), *g;

          if ((u != _NLL) && (u->color == true) && (n->parent->color == true)) {
              n->parent->color = false;
              u->color = false;
              g = grandparent(n);
              g->color = true;
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

          n->parent->color = false;
          g->color = true;
          if ((n == n->parent->left) && (n->parent == g->left)) {
              rotate_right(g);
          } else {
              rotate_left(g);
          }
      }


      /// same from BST task
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

      /// update _NLL with new root
      void set_root(node * r){
          _NLL->left = r;
          _NLL->right =r;
          root = r;
      }

      /// free node of data and delete
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
          node * y;
          if (n->left == _NLL || n->right == _NLL)
              y = n;
          else
              y = next(n);
          node * x;
          if(y->left != _NLL)
              x = y->left;
          else
              x = y->right;
          x->parent = y->parent;
          if(y->parent == _NLL)
              set_root(x);
          else {
                  if(y == y->parent->left)
                      y->parent->left = x;
                  else
                      y->parent->right = x;
              }
          if(y!=n)
              n->data = y->data;
          if (y->color == false)
              delete_case1(x);
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

          if (s->color == true) {
              n->parent->color = true;
              s->color = false;
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

          if ((n->parent->color == false) &&
              (s->color == false) &&
              (s->left->color == false) &&
              (s->right->color == false)) {
              s->color = true;
              delete_case1(n->parent);
          } else
              delete_case4(n);
      }

      void delete_case4( node *n)
      {
           node *s = sibling(n);

          if ((n->parent->color == true) &&
              (s->color == false) &&
              (s->left->color == false) &&
              (s->right->color == false)) {
              s->color = true;
              n->parent->color = false;
          } else
              delete_case5(n);
      }

      void delete_case5( node *n)
      {
           node *s = sibling(n);

          if  (s->color == false) { /* this if statement is trivial,
      due to case 2 (even though case 2 changed the sibling to a sibling's child,
      the sibling's child can't be true, since no true parent can have a true child). */
      /* the following statements just force the true to be on the left of the left of the parent,
         or right of the right, so case six will rotate correctly. */
              if ((n == n->parent->left) &&
                  (s->right->color == false) &&
                  (s->left->color == true)) { /* this last test is trivial too due to cases 2-4. */
                  s->color = true;
                  s->left->color = false;
                  rotate_right(s);
              } else if ((n == n->parent->right) &&
                         (s->left->color == false) &&
                         (s->right->color == true)) {/* this last test is trivial too due to cases 2-4. */
                  s->color = true;
                  s->right->color = false;
                  rotate_left(s);
              }
          }
          delete_case6(n);
      }

      void delete_case6( node *n)
      {
           node *s = sibling(n);

          s->color = n->parent->color;
              n->parent->color = false;

          if (n == n->parent->left) {
                      s->right->color = false;
              rotate_left(n->parent);
          } else {
              s->left->color = false;
              rotate_right(n->parent);
          }
      }


      node *find_node(const value_type  &  v, node * r = nullptr) const  {
          if(r == nullptr)
              r = root;
          while(r != _NLL){
              if(Compare(r->data.first, v)){
                  if (r->right != _NLL)
                  r = r->right;
                  else return r;
              }
              else {
                 if (r->left != _NLL)
                  r = r->left;
                 else return r;
              }
          }
          return _NLL;
      }




public:

      class iterator
      {
          public:
              typedef iterator self_type;
              typedef key_type& reference;
              typedef node* pointer;
              typedef std::bidirectional_iterator_tag iterator_category;
              typedef size_t difference_type;

              iterator(node * ptr,multiset<key_type> * f) : ptr_(ptr), father(f), cnt(1) { }
              self_type operator++() {
                  if(cnt != ptr_->data.second && ptr_->data.second != 0){
                      ++cnt;
                      return *this;
                      }
                  self_type i = *this;
                  ptr_ = father->next(ptr_);
                  cnt = 1;
                  return i; }
              self_type operator++(int junk) {
                  if(cnt != ptr_->data.second && ptr_->data.second != 0){
                      ++cnt;
                      return *this;
                      }
                  ptr_=father->next(ptr_);
                  cnt = 1;
                  return *this;
              }
              self_type operator--() {
                  if(ptr_->data.second > 1){
                      --cnt;
                      return *this;
                      }
                  self_type i = *this;
                  ptr_=father->prev(ptr_);
                  cnt = 1;
                  return i;
              }
              self_type operator--(int junk) {
                  if(ptr_->data.second > 1 && cnt !=1){
                      --cnt;
                      return *this;
                      }
                  ptr_=father->prev(ptr_);
                  cnt = 1;
                  return *this;
              }
              key_type operator*() { return ptr_->data.first; }
              self_type operator+(difference_type c){
                  self_type it = *this;
                  for(difference_type i = 0; i<c;++i ) ++it; return it; }
              //pointer operator->() { return ptr_; }
              bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
              bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
              difference_type count() const {
                  return ptr_->data.second;
              }
      protected:
             multiset<key_type> * father;
             node *  ptr_;
             size_t cnt;
      };



      class const_iterator: public iterator {
      public:
          const_iterator(node * ptr,multiset<key_type> * f) : iterator(ptr,f){}
          const key_type& operator*() { return iterator::ptr_->data ; }
          };

private:

      size_t delete_value(const key_type&  v){
          node * r = find_node(v);
          if (r != _NLL){
              size_t t = r->data.second;
                  delete_one_child(r);
              return t;
          }
          else
          {return 0;}
      }

public:

      iterator begin()
              {
                  auto r = root;
                  while(r->left != _NLL)
                      r = r->left;
                  return iterator(r,this);
              }

              iterator end()
              {
                  return iterator(_NLL,this);
              }

              const_iterator cbegin() const
              {
                  auto r = root;
                  while(r->left != _NLL)
                      r = r->left;
                  return const_iterator(r,this);
              }

              const_iterator cend() const
              {
                  return const_iterator(_NLL,this);
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
                                 if (v <r->data){
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
                          while(f->data == v)
                              f = next(f);
                          return f;
                      }
                  else {
                          if (r == _NLL)
                              return iterator(r);
                          while(r!= _NLL){
                                  if (v <r->data){
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

              size_t count(const key_type&v)  {
                  return find_node(v)->data.second;
              }

              size_t erase( const key_type& v){
                  return delete_value(v);
              }

              bool empty() const {
                  return cbegin() == cend();
              }

              bool empty(){
                  return begin() == end();
              }


              void clear() {
                  while(!empty()){
                      key_type t = *begin();
                      delete_value(t);
                    }
              }


              ~multiset(){
                  clear();
                  delete _NLL;
              }

              multiset(const multiset<key_type> & m):multiset(){
                  auto it =m.cbegin();
                  while(it != m.cend())
                    this->insert(*it);
              }

              void operator=(multiset<key_type> m){
                  this->clear();
                  delete _NLL;
                  _NLL  = nullptr;
                  root  = nullptr;
                  std::swap(_NLL,m._NLL);
                  std::swap(root,m.root);
              }

              bool operator==(const multiset<key_type> & m){
                  return root == m.root;
              }

              bool operator!=(const multiset<key_type> & m){
                  return ! (*this==m);
              }


              void write_to_stream(std::ostream &  os,std::string delim = ", "){
                  iterator it = this->begin();
                  while(it != this->end())
                      os<<*it++<<delim;
              }

              void write_to_stream_mid_delim(std::ostream &  os,std::string delim = ", "){
                  iterator it = this->begin();
                  while(it != this->end()){
                      os<<*it++;
                      if (it+1 != this->end())
                        os<<delim;
                      }
              }

              void read_from_stream(std::istream & is){
                  while (is) {
                          key_type t;
                          is>>t;
                          this->insert(t);
                      }

              }






};

template<typename key_type>
class deb_multiset: public multiset<key_type> {
protected:
    int rotate_left_cnt;
    int rotate_right_cnt;

    using nd = typename multiset<key_type>::node;

    virtual void rotate_left(nd * n){
        multiset<key_type>::rotate_left(n);
        ++rotate_left_cnt;
    }

    virtual void rotate_right(nd * n){
        multiset<key_type>::rotate_right(n);
        ++rotate_right_cnt;
    }

public:

    deb_multiset(): multiset<key_type>() {
        rotate_left_cnt = 0;
        rotate_right_cnt = 0;
    }

    int left_rotations(){ return rotate_left_cnt;}

    int right_rotations(){ return rotate_right_cnt;}

    void reset_rotations(){
        rotate_left_cnt = 0;
        rotate_right_cnt = 0;
    }


    };


/// time test;
void time_test(int cnt);


#endif // RB_MULTI_SET_H

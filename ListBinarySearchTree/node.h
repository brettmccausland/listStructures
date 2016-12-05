#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

using namespace std;
//                  {0,1}
//funtions I need (isleaf)
enum WHICH_CHILD {RIGHT,LEFT};
enum Node_errors{Nullptr_node_error};
template<typename T>
class node
{

    public:
         node(const T &d = T(), size_t c = 1);
         ~node();
         node(const node<T> &other);
         node<T>& operator=(const node<T> &other);
         node<T>& operator+=(size_t v);
         node<T>& operator-=(size_t v);

         void setNodeValue(const T &d = T(), size_t c = 1);
         const T& getData() const;
         size_t getCount() const;
         int operator++();
         int operator++(int);
         int operator--();
         int operator--(int);

         node<T>*& childPtr(WHICH_CHILD child);
         const node<T>* getChildPtr(WHICH_CHILD child) const;

         void setChildPtr(node<T>* ptr, WHICH_CHILD child);

//Node vs Node bool functions
         template<typename U>
         friend
         bool operator<(const node<U>& x, const node<U> &y);

         template<typename U>
         friend
         bool operator<=(const node<U>& x, const node<U> &y);

         template<typename U>
         friend
         bool operator==(const node<U>& x, const node<U> &y);

         template<typename U>
         friend
         bool operator!=(const node<U>& x, const node<U> &y);

         template<typename U>
         friend
         bool operator>=(const node<U>& x, const node<U> &y);

         template<typename U>
         friend
         bool operator>(const node<U>& x, const node<U> &y);

//Node vs Data

         template<typename U>
         friend
         bool operator<(const node<U>& x, const U &y);

         template<typename U>
         friend
         bool operator<=(const node<U>& x, const U &y);

         template<typename U>
         friend
         bool operator==(const node<U>& x, const U &y);

         template<typename U>
         friend
         bool operator!=(const node<U>& x, const U &y);

         template<typename U>
         friend
         bool operator>=(const node<U>& x, const U &y);

         template<typename U>
         friend
         bool operator>(const node<U>& x, const U &y);

//Data vs Node
         template<typename U>
         friend
         bool operator<(const U& x, const node<U> &y);

         template<typename U>
         friend
         bool operator<=(const U& x, const node<U> &y);

         template<typename U>
         friend
         bool operator==(const U& x, const node<U> &y);

         template<typename U>
         friend
         bool operator!=(const U& x, const node<U> &y);

         template<typename U>
         friend
         bool operator>=(const U& x, const node<U> &y);

         template<typename U>
         friend
         bool operator>(const U& x, const node<U> &y);

//Input / Output of Nodes
         template<typename U>
         friend
         ostream& operator<<(ostream &out, const node<U> &other);

         template<typename U>
         friend
         istream& operator>>(istream &in, node<U> &other);
         // ----------added member funtion-----------------
            bool isleaf();
            

         //------------------------------------------------

    private:
        // data (contents)
       // count (# of that contetnt
       // *childPointer  [child 1]&[child 2]
         T data;
         size_t count;
         node<T> *childPointer[2];

         void copy(const node<T> &other);
         void nukem();
};
// ----------added member funtion-----------------
template<typename T>
bool node<T>::isleaf()
{
    return (this->getChildPtr(LEFT) == NULL && this->getChildPtr(RIGHT)==NULL) ;
}
//
//------------------------------------------------
template<typename T>
node<T>::node(const T &d, size_t c)
{
    setNodeValue(d,c);
    childPointer[LEFT] = childPointer[RIGHT] = NULL;
}

template<typename T>
node<T>::~node()
{
    nukem();
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
node<T>& node<T>::operator+=(size_t v)
{
    count += v;
    return *this;
}

template<typename T>
node<T>& node<T>::operator-=(size_t v)
{
    count -= v;
    return *this;
}

template<typename T>
void node<T>::setNodeValue(const T &d , size_t c )
{
    data = d;
    count = c;
}

template<typename T>
const T& node<T>::getData() const
{
    return data;
}

template<typename T>
size_t node<T>::getCount() const
{
    return count;
}

template<typename T>
int node<T>::operator++(int)
{
    count++;
    return count;
}

template<typename T>
int node<T>::operator++()
{
    size_t temp = count;
    count++;
    return temp;
}
template<typename T>
int node<T>::operator--(int)
{
    return --count;
}

template<typename T>
int node<T>::operator--()
{
    size_t temp = count;
    --count;
    return temp;
}

template<typename T>
node<T>*& node<T>::childPtr(WHICH_CHILD child)
{
    return childPointer[child];
}


template<typename T>
const node<T>* node<T>::getChildPtr(WHICH_CHILD child) const
{
    return childPointer[child];
}
template<typename T>
void node<T>::setChildPtr(node<T>* ptr, WHICH_CHILD child)
{
    childPointer[child] = ptr;
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    count = other.count;
}

template<typename T>
void node<T>::nukem()
{
    data = T();
    count = 0;
    childPointer[LEFT] = childPointer[RIGHT] = NULL;
}

//Node vs Node bool functions
template<typename U>
bool operator<(const node<U>& x, const node<U> &y)
{
    return x.data < y.data;
}

template<typename U>
bool operator<=(const node<U>& x, const node<U> &y)
{
    return x.data <= y.data;
}

template<typename U>
bool operator==(const node<U>& x, const node<U> &y)
{
    return x.data == y.data;
}

template<typename U>
bool operator!=(const node<U>& x, const node<U> &y)
{
    return x.data != y.data;
}

template<typename U>
bool operator>=(const node<U>& x, const node<U> &y)
{
    return x.data >= y.data;
}

template<typename U>
bool operator>(const node<U>& x, const node<U> &y)
{
    return x.data > y.data;
}

//Node vs Data

template<typename U>
bool operator<(const node<U>& x, const U &y)
{
    return x.data < y;
}

template<typename U>
bool operator<=(const node<U>& x, const U &y)
{
    return x.data <= y;
}

template<typename U>
bool operator==(const node<U>& x, const U &y)
{
    return x.data == y;
}

template<typename U>
bool operator!=(const node<U>& x, const U &y)
{
    return x.data != y;
}

template<typename U>
bool operator>=(const node<U>& x, const U &y)
{
    return x.data >= y;
}

template<typename U>
bool operator>(const node<U>& x, const U &y)
{
    return x.data > y;
}

//Data vs Node
template<typename U>
bool operator<(const U& x, const node<U> &y)
{
    return x < y.data;
}

template<typename U>
bool operator<=(const U& x, const node<U> &y)
{
    return x <= y.data;
}

template<typename U>
bool operator==(const U& x, const node<U> &y)
{
    return x == y.data;
}

template<typename U>
bool operator!=(const U& x, const node<U> &y)
{
    return x != y.data;
}


template<typename U>
bool operator>=(const U& x, const node<U> &y)
{
    return x >= y.data;
}

template<typename U>
bool operator>(const U& x, const node<U> &y)
{
    return x > y.data;
}

//Input / Output of Nodes
template<typename U>
ostream& operator<<(ostream &out, const node<U> &other)
{
    out <<other.data<<"["<<other.count<<"] ";
    return out;
}

template<typename U>
istream& operator>>(istream &in, node<U> &other)
{
    char junk;
    in>>other.data>>junk>>other.count>>junk;
    return in;
}
#endif // NODE_H

#ifndef MYLIST_H
#define MYLIST_H

#include <cstdlib>

template<typename T>
class myList{
public:
	myList();
	virtual ~myList();
	myList(const myList<T>& other);
	myList<T>& operator=(const myList<T>& other);

	void insert(const T& d);
	void removeEnd();
	bool empty();
	void clear();
	unsigned int size() const;

	T& getData(int num) const;

protected:
	struct node{
		node* next;
		T data;
	};

	node* head;
	unsigned int qty;

	void copy(const myList<T>& other);
	void nukem();
};

template<typename T>
myList<T>::myList()
{
	qty  = 0;
	head = new node;
	head->next=NULL;
}

template<typename T>
myList<T>::~myList()
{
    clear();
    delete head;
}

template<typename T>
myList<T>::myList(const myList<T>& other)
{
	qty  = 0;
	head = new node;
	head->next=NULL;

	if(this!=&other){
	    copy(other);
	}
}

template<typename T>
myList<T>& myList<T>::operator=(const myList<T>& other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
void myList<T>::insert(const T& d){
	node* ptr = head;
    for(; ptr->next; ptr=ptr->next);

    node* nNode = new node;
	nNode->next = NULL;
	nNode->data = d;

	ptr->next = nNode;
	++qty;
}

template<typename T>
void myList<T>::removeEnd(){
	if(qty==0)
		return;
	if (qty--==1){
		delete head->next;
		head->next = NULL;
		return;
	}
	node* ptr = head;
	for(; ptr->next->next; ptr=ptr->next);
	delete ptr->next;
	ptr->next=NULL;
}

template<typename T>
T& myList<T>::getData(int num) const{
	
	node* ptr = head->next;
	for(unsigned int i = 0; i < num && ptr->next; ++i, ptr = ptr->next);

	return ptr->data;
}

template<typename T>
bool myList<T>::empty()
{
    return qty==0;
}

template<typename T>
void myList<T>::clear()
{
	nukem();
}

template<typename T>
unsigned int myList<T>::size() const
{
    return qty;
}

template<typename T>
void myList<T>::copy(const myList<T>& other)
{
	nukem();
	node* ptr  = head;
	node* ptr2 = other.head;

	while(ptr2->next){
		ptr2=ptr2->next;
		insert(ptr2->data);
	}
}

template<typename T>
void myList<T>::nukem()
{
	while(qty)
		removeEnd();
}

#endif // MYLIST_H

#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>
#include "myList.h"
 
using std::cin;
using std::type_info;
using std::string;
using std::endl;
using std::cout;
using std::ostream;
using std::istream;
using std::stringstream;
using std::getline;

enum LIST_QUEUE_ERRORS {LIST_QUEUE_EMPTY, LIST_QUEUE_FULL};

template<typename T>
class listQueue
{
public:
	listQueue(unsigned int s = 100);
	~listQueue();
	listQueue(const listQueue<T>& other);
	listQueue<T>& operator=(const listQueue<T>& other);

	bool full();
	bool empty();
	T front();
	void clear();
	unsigned int size() const;
	unsigned int max_size();
	void resize(unsigned int s = 20);
	listQueue<T>& operator<<(const T &d);
	listQueue<T>& operator>>(T &d);
	void enqueue(const T& d);
	void dequeue(T& d);
	T dequeue();

	template<typename Y>
	friend
	ostream& operator<<(ostream& out, const listQueue<Y>& que);

	template<typename Y>
	friend
	istream& operator>>(istream& in, listQueue<Y>& que);
 
private:
	myList<T> lque;
	unsigned int max_qty;

	void copy(const listQueue<T>& q);
	void nukem();
};

template<typename T>
listQueue<T>::listQueue(unsigned int s){
	max_qty = s;
}

template<typename T>
listQueue<T>::~listQueue(){
}

template<typename T>
listQueue<T>::listQueue(const listQueue<T>& other){
	copy(other);
}

template<typename T>
listQueue<T>& listQueue<T>::operator=(const listQueue<T>& other){
	copy(other);
	return *this;
}

template<typename T>
bool listQueue<T>::full(){
	return lque.size() == max_qty;

}

template<typename T>
bool listQueue<T>::empty(){
	return lque.size() == 0;
}

template<typename T>
T listQueue<T>::front(){
	return lque.getData(0);
}

template<typename T>
void listQueue<T>::clear(){
	lque.clear();
}

template<typename T>
unsigned int listQueue<T>::size() const{
	return lque.size();
}

template<typename T>
unsigned int listQueue<T>::max_size(){
	return max_qty;
}

template<typename T>
void listQueue<T>::resize(unsigned int s){
	max_qty = s;
}

template<typename T>
listQueue<T>& listQueue<T>::operator<<(const T &d){
	enqueue(d);
	return *this;
	//try returning this
}

template<typename T>
listQueue<T>& listQueue<T>::operator>>(T &d){
	dequeue(d);
	return *this;
}

template<typename T>
void listQueue<T>::enqueue(const T& d){
	if(full())
		throw LIST_QUEUE_FULL;
	lque.insert(d);
}

template<typename T>
void listQueue<T>::dequeue(T& d){
	if(empty())
		throw LIST_QUEUE_EMPTY;
	d = lque.removeFront();
}

template<typename T>
T listQueue<T>::dequeue(){
	if(empty())
		throw LIST_QUEUE_EMPTY;
	return lque.removeFront();
}

template <typename T>
void listQueue<T>::copy(const listQueue<T>& other){
	if(this == &other)
		return;
	lque    = other.lque;
	max_qty = other.max_qty;
}

template <typename T>
void listQueue<T>::nukem(){
	clear();
}


template<typename Y>
ostream& operator<<(ostream& out, const listQueue<Y>& lqueue){
	string eol = (&out == &cout ? ", " : "\n");

	Y data;
	listQueue<Y> temp = lqueue;
	for(int i = 0; i < lqueue.size(); i++){
		temp.dequeue(data);
		out << data << eol;
	}
	if(&cout == &out)
		cout<<"\b\b ";
	return out;

}

template<typename Y>
istream& operator>>(istream &in, listQueue<Y> &lqueue)
{
	stringstream ss;
	string line;
	Y data;

	if(&in == &cin)
		while(1){
			cout<<"Data: ";
			getline(in,line);
			if(line == "")
				break;
			ss<<line;
			ss>>data;
			ss.clear();
			lqueue.enqueue(data);
		}

	else{
		while(getline(in, line)){
			ss<<line;
			ss>>data;
			lqueue.enqueue(data);
			ss.clear();
		}
	}

	return in;
}

template<>
inline istream& operator>>(istream &in, listQueue<string> &lqueue)
{
	stringstream ss;
	string line;

	if(&in == &cin)
		while(1){
			cout<<"Data: ";
			getline(in,line);
			if(line == "")
				break;
			ss.clear();
			lqueue.enqueue(line);
		}

	else{
		while(getline(in, line)){
			lqueue.enqueue(line);
			ss.clear();
		}
	}

	return in;
}

template<>
inline istream& operator>>(istream &in, listQueue<char> &lqueue)
{
	stringstream ss;
	string line;

	if(&in == &cin)
		while(1){
			cout<<"Data: ";
			getline(in,line);
			if(line == "")
				break;
			ss.clear();
			for(unsigned int i = 0; i < line.size(); i++)
				lqueue.enqueue(line[i]);
		}

	else{
		while(getline(in, line)){
			for(unsigned int i = 0; i < line.size(); i++)
				lqueue.enqueue(line[i]);
			ss.clear();
		}
	}

	return in;
}

#endif

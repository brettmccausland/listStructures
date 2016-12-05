#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using std::ostream;
using std::istream;
using std::string;
using std::stringstream;
using std::string;
using std::cin;
using std::cout;

#include "myList.h"

enum LIST_STACK_ERRORS {LIST_STACK_IS_EMPTY, LIST_STACK_IS_FULL};

template<typename T>
class listStack : public myList<T>{
	public:
		listStack( unsigned int s = 100);
		~listStack();
		listStack(const listStack<T>& other);
		listStack<T>& operator=(const listStack<T>& other);

		listStack<T>& operator<<(const T& d); //Push, chainable
		listStack<T>& operator>>(T &d); // Pop, chainable

		T pop();
		T top();
		void push(const T& d);

		int max_size();
		bool full();

		template<typename Y>
		friend
		ostream& operator<<(ostream &out, const listStack<Y> &stack);

		template<typename Y>
		friend
		istream& operator>>(istream &in, listStack<Y> &stack);

	private:
		unsigned int max_qty;

		void copy(const listStack<T>& other);
};

template<typename T>
listStack<T>::listStack( unsigned int s )
{
	max_qty = s;
}

template<typename T>
listStack<T>::~listStack()
{
	this->nukem();
}

template<typename T>
listStack<T>::listStack(const listStack<T>& other)
{
	copy(other);
}

template<typename T>
listStack<T>& listStack<T>::operator=(const listStack<T>& other)
{
	if(this != &other)
		copy(other);
	return *this;
}

template<typename T>
listStack<T>& listStack<T>::operator<<(const T& d) //Push, chainable
{
	push(d);
	return *this;
}

template<typename T>
listStack<T>& listStack<T>::operator>>(T &d) // Pop, chainable
{
	d = pop();
	return *this;
}

template<typename T>
T listStack<T>::pop()
{
	if(this->empty())
		throw LIST_STACK_IS_EMPTY;

	T temp = top();
	this->removeEnd();
	return temp;
}

template<typename T>
T listStack<T>::top()
{
	if(this->empty())
		throw LIST_STACK_IS_EMPTY;
	return this->getData(this->size()-1);
}

template<typename T>
void listStack<T>::push(const T& data)
{
	if(full())
		throw LIST_STACK_IS_FULL;
	this->insert(data);
}

template<typename T>
int listStack<T>::max_size()
{
	return max_qty;
}

template<typename T>
bool listStack<T>::full()
{
	return this->size()==max_qty;
}

template<typename T>
void listStack<T>::copy(const listStack<T>& other)
{
	this->nukem();
	max_qty = other.max_qty;

	myList<T>::copy(dynamic_cast<const myList<T>& >(other));
}

template<typename Y>
ostream& operator<<(ostream &out, const listStack<Y> &stack)
{
	string eol = (&out == &cout ? " " : "\n");
	for(int i = stack.size()-1; i >= 0; i--)
		out<<stack.getData(i)<<eol;
	return out;
}

template<typename Y>
istream& operator>>(istream &in, listStack<Y> &stack)
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
			stack.push(data);
		}

	else{
		while(getline(in, line)){
			ss<<line;
			ss>>data;
			stack.push(data);
			ss.clear();
		}
	}

	return in;
}

template<>
istream& operator>>(istream &in, listStack<string> &stack)
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
			stack.push(line);
		}

	else{
		while(getline(in, line)){
			stack.push(line);
			ss.clear();
		}
	}

	return in;
}

template<>
istream& operator>>(istream &in, listStack<char> &stack)
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
				stack.push(line[i]);
		}

	else{
		while(getline(in, line)){
			for(unsigned int i = 0; i < line.size(); i++)
				stack.push(line[i]);
			ss.clear();
		}
	}

	return in;
}

#endif // LIST_STACK_H

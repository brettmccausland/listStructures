#ifndef MYSTACK_H
#define MYSTACK_H

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

enum STACK_ERRORS {STACK_IS_EMPTY, STACK_IS_FULL};

template<typename T>
class myStack
{
	public:
		myStack( unsigned int s = 100);
		~myStack();
		myStack(const myStack<T>& other);
		myStack<T>& operator=(const myStack<T>& other);

		myStack<T>& operator<<(const T& d); //Push, chainable
		myStack<T>& operator>>(T &d); // Pop, chainable

		T pop();
		T top();
		void push(const T& d);
		bool full();
		bool empty();
		void clear();
		int size() const;
		int max_size();

		template<typename Y>
		friend
		ostream& operator<<(ostream &out, const myStack<Y> &stack);


		template<typename Y>
		friend
		istream& operator>>(istream &in, myStack<Y> &stack);

	private:
		T* stk;
		unsigned int qty, max_qty;

		void copy(const myStack<T>& other);
		void nukem();
};

template<typename T>
myStack<T>::myStack( unsigned int s )
{
	stk = new T[max_qty = s];
	qty = 0;
}

template<typename T>
myStack<T>::~myStack()
{
	nukem();
}

template<typename T>
myStack<T>::myStack(const myStack<T>& other)
{
	copy(other);
}

template<typename T>
myStack<T>& myStack<T>::operator=(const myStack<T>& other)
{
	if(this != &other)
		copy(other);
	return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator<<(const T& d) //Push, chainable
{
	push(d);
	return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator>>(T &d) // Pop, chainable
{
	d = pop();
	return *this;
}

template<typename T>
T myStack<T>::pop()
{
	if(empty())
		throw STACK_IS_EMPTY;
	return stk[--qty];
}

template<typename T>
T myStack<T>::top()
{
	if(empty())
		throw STACK_IS_EMPTY;
	return stk[qty-1];
}

template<typename T>
void myStack<T>::push(const T& data)
{
	if(qty==max_qty)
		throw STACK_IS_FULL;
	stk[qty++] = data;
}

template<typename T>
bool myStack<T>::full()
{
	return qty == max_qty;
}

template<typename T>
bool myStack<T>::empty()
{
	return qty==0;
}

template<typename T>
void myStack<T>::clear()
{
	nukem();
}

template<typename T>
int myStack<T>::size() const
{
	return qty;
}

template<typename T>
int myStack<T>::max_size()
{
	return max_qty;
}

template<typename T>
void myStack<T>::copy(const myStack<T>& other)
{
	nukem();
	max_qty = other.max_qty;
	qty = other.qty;

	for(int i = 0; i < other.size(); i++)
		stk[i]=other.stk[i];
}

template<typename T>
void myStack<T>::nukem()
{
	while(qty>0)
		stk[--qty] = T();
}

template<typename Y>
ostream& operator<<(ostream &out, const myStack<Y> &stack)
{
	string eol = (&out == &cout ? " " : "\n");
	for(int i = stack.qty-1; i >= 0; i--)
		out<<stack.stk[i]<<eol;
	return out;
}


template<typename Y>
istream& operator>>(istream &in, myStack<Y> &stack)
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
istream& operator>>(istream &in, myStack<string> &stack)
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
istream& operator>>(istream &in, myStack<char> &stack)
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

#endif // MYSTACK_H

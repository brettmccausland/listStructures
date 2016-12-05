#include <iostream>
#include <string>
#include "myStack.h"
#include "listStack.h"

using namespace std;

string getLine();
void perform(string line);
string trimAndNormalize(string line);

int main()
{
	string line;
	while((line = getLine()) != "")
		perform(line);
	return 0;
}

string getLine()
{
	string line;
	cout<<"Input: ";
	getline(cin, line);
	return line;
}

void perform(string line)
{
	myStack<char> mystack(line.size());
	string normalized, reversed;
	normalized = trimAndNormalize(line);
	for(unsigned int i = 0; i < normalized.size(); i++)
		mystack<<normalized[i];
	while(!mystack.empty())
		reversed += mystack.pop();
	string isNot = reversed == normalized ? " is " : " is not ";
	cout<<line<<isNot<<"a palindrome"<<endl;

}

string trimAndNormalize(string line)
{
	//unsinged int gives run time errors
	//unsigned int pos
	int pos;
	for(unsigned int i = 0; i < line.size(); i++)
		line[i] = toupper(line[i]);
	
	//we are looking for spaces to delete, not the entire alphabet
	//while((pos = line.find("ABCDEFGHIJKLMNOPQRSTUVWXYZ")) < string::npos)
	while((pos = line.find(' ')) < string::npos)
		line.erase(pos, 1);
	return line;
}
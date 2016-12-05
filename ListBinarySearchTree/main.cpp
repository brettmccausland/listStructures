#include <cstdlib>
#include <iostream>
#include <fstream>
#include "bst.h"

#define MAXTREE 2

using namespace std;
//1. Correct the binary tree written in class so that it runs correctly.
//2. Convert the tree from number 1 above to be vector-based.
//In this version, all functions, including balancing, must be implemented.
//In addition, the vector should grow only as necessary
//-- meaning that, at most, there should be only one layer of nodes more than what is necessary to store the tree.
//(REMEMBER THAT A VECTOR COPIES THE ITEM THAT IS PLACED INTO IT!!!!! This could be a REAL problem that effects efficiency!)
//Note: The DSW algorithm used in 1 to rebalance the tree works only on linked-lists!
bool again();
void menu(bst<char> tree[],int &toUse);
void perform(bst<char> &myTree, char selection, int &touse);
void driver();
// changes are made
int main(int argc, char *argv[])
{
    system("clear");
  bst<char> tree[MAXTREE];
  int touse=0;
  do
  {
    menu(tree, touse);
  }while(again());
  driver();
  return 0;
}

bool again()
{
   char ans;
   cout<<"Do you want to do this again? ";
   cin >> ans;
   return toupper(ans) == 'Y';
}


void perform(bst<char> tree[], char selection, int &touse)
{
   char value;
   int order;
   char name[30];
   switch(toupper(selection))
   {

     case '+' :
     case 'E' : cout<<"What value do you want to put into the tree? ";
                cin>> value;
                tree[touse].insert(value);
                break;

     case '-' :
     case 'D' : cout<<"What value do you want to see if it is in the tree? ";
                cin>> value;
                if(tree[touse].remove(value))
                   cout<<value<<" removed successfully"<<endl;
                else
                   cout<<"Item not in tree -- therefore it was not removed."<<endl;
                break;

     case 'B' : if(tree[touse].balanced())
                    cout<<"Your tree is balanced!"<<endl;
                else
                {
                   tree[touse].rebalance();
                   cout<<"Your tree is now balanced!"<<endl;
                }
                break;

     case 'P' : cout<<tree[touse]<<endl;
                break;

     case 'F' : cout<<"What value do you want to see if it is in the tree? ";
                cin>> value;
                if(tree[touse].find(value))
                     cout<<"The tree has this value in it"<<endl;
                else
                    cout<<"The tree does not have this value in it"<<endl;
                break;


     case 'C' : cout<<"There are "<<tree[touse].totalData()<<" items in the tree "<<endl;
                break;

     case 'N' : cout<<"There were "<<tree[touse].totalData()<<" items in the tree you just disposed"<<endl;
                tree[touse].clear();
                break;

     case 'S' : do
                {
                   cout<<"Enter 1 for a PREORDER, 2 for INORDER and 3 for POSTORDER ";
                   cin>>order;
                }while(order<1 || order > 3);
                switch(order)
                {
                    case 1: tree[touse].setTraversal(PRE_ORDER);
                            break;
                    case 2: tree[touse].setTraversal(IN_ORDER);
                            break;
                    case 3: tree[touse].setTraversal(POST_ORDER);
                            break;
                }
                break;

     case 'T' : do
                {
                   cout<<"Which tree do you want to use: ";
                   cin>>order;
                }while(order < 0 || order > MAXTREE);
                break;


     case 'W' : {
                  ofstream out;
                  cout<<"What is the name of the file you want to write to: ";
                  cin>>name;
                  out.open(name);
                  out<<tree[touse];
                  out.close();
                  break;
                }

     case 'R' : {
                  ifstream in;
                  cout<<"What is the name of the file you want to read from: ";
                  cin>>name;
                  in.open(name);
                  in>>tree[touse];
                  in.close();
                  break;
                }

     case 'Q' : cout<<"Goodbye"<<endl;
   }
}
void driver()
{
    //when printing use pre order transversal
    bst<int> mytree;
    mytree.insert(9);
    mytree.print();
//     mytree.insert('e');
//      mytree.insert('d');
//       mytree.insert('L');
//       mytree.insert('z');
//        mytree.insert('c');
//         mytree.insert('r');
//          mytree.insert('w');
//          mytree.insert('t');
//           mytree.insert('u');
//            mytree.insert('i');
//             mytree.insert('L');
//             mytree.insert('o');
//              mytree.insert('p');
//               mytree.insert('x');
//                mytree.insert('q');
//                cout<<"a,e,d,l,z,z,r,y"<<endl;
//                 cout<<endl<<"-----------------------------"<<endl;
                 //if()
//            mytree.printdebug(mytree.getroot());

//                if(mytree.balanced())
//               {
//                   cout<<"tree balancd"<<endl;
//               }
//               else
//               {
//                   mytree.rebalance();
//               }
//  cout<<endl<<"-----------------------------"<<endl;
//    //if()
//   mytree.printdebug(mytree.getroot());

}

void menu(bst<char> tree[],int &toUse)
{
  char selection;
  do
  {
     cout<<endl;
     cout<<"Menu Selections for tree operations"<<endl
         <<" E. Enter data"<<endl
         <<" D. Delete data"<<endl
         <<" B. Balanced"<<endl
         <<" S. Select print order"<<endl
         <<" P. Print the tree"<<endl
         <<" F. Find if an item is in the tree"<<endl
         <<" T. Select tree to use"<<endl
         <<" R. Read from a file"<<endl
         <<" W. Write to a file"<<endl
         <<" C. Count how many items are in the tree"<<endl
         <<" N. Empty the tree"<<endl
         <<" Q. Quit"<<endl
         <<"What is your selection: ";
     cin>>selection;
     perform(tree, selection, toUse);
  }while(toupper(selection) != 'Q');
}

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include <iostream>
#include <string>
#include "Prim.h"


using namespace std;

void display(string& anItem)
{
   cout << "Displaying item - " << anItem << endl;
}



void graphTest(Prim<string>* testGraph)
{
   string A("A");
   string B("B");
   string C("C");
   string D("D");
   string E("E");
   string F("F");
   string G("G");
   string H("H");
   string I("I");
   string J("J");
   string K("K");
   string L("L");
   string M("M");
   string N("N");
   
   testGraph->add(A, B, 2);
   testGraph->add(A, C, 4);
   testGraph->add(A, D, 1);
   testGraph->add(B, E, 5);
   testGraph->add(B, F, 3);
   testGraph->add(C, G, 4);
   testGraph->add(D, H, 1);
   testGraph->add(D, I, 2);
   testGraph->add(F, J, 5);   
   testGraph->add(G, K, 3);
   testGraph->add(G, L, 2);   
   testGraph->add(H, M, 1);
   testGraph->add(I, M, 4);
   testGraph->add(I, N, 2);
   /*
   cout << "Vertices :" << testGraph->getNumVertices() << endl;
   cout << "Edges :" << testGraph->getNumEdges() << endl;
   
  
   cout << "\nDepth-first traversal (should be A B E F J C G K L D H M I N):" << endl;
   testGraph->depthFirstTraversal(A, display);
  
   cout << "\nBreadth-first traversal (should be A B C D E F G H I J K L M N):" << endl;
   testGraph->breadthFirstTraversal(A, display);
   */
}  // end graphTest

int main()
{
   Prim<string>* myGraph = new Prim<string>();

   //cout << "Testing Graph . . . ." << endl << endl ;
   graphTest(myGraph);
   //cout << "graph filled" << endl;
   //system("pause");
   //myGraph->writeStartingEdges(cout);
   myGraph->displayMenu();

   system("pause");
   return 0;
}  // end main

/*
 Testing Graph . . . .
 
 Vertices :14
 Edges :14
 
 Depth-first traversal (should be A B E F J C G K L D H M I N):
 Displaying item - A
 Displaying item - B
 Displaying item - E
 Displaying item - F
 Displaying item - J
 Displaying item - C
 Displaying item - G
 Displaying item - K
 Displaying item - L
 Displaying item - D
 Displaying item - H
 Displaying item - M
 Displaying item - I
 Displaying item - N
 
 Breadth-first traversal (should be A B C D E F G H I J K L M N):
 Displaying item - A
 Displaying item - B
 Displaying item - C
 Displaying item - D
 Displaying item - E
 Displaying item - F
 Displaying item - G
 Displaying item - H
 Displaying item - I
 Displaying item - J
 Displaying item - K
 Displaying item - L
 Displaying item - M
 Displaying item - N
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "LinkedGraph.h"
#include "LinkedStack.h"

using namespace std;

// By C. Lee-Klawender

template <class LabelType>
class Prim : public LinkedGraph<LabelType>
{
    // NESTED CLASS: (needed because the Edge class didn't give both ends)
    template <class LabelType>
    class PrimEdge
    {
    private:
	   LabelType startLabel;
	   Edge<LabelType> edge;
	   bool checked;


    public:
	   PrimEdge(){}
	   PrimEdge(LabelType start, Edge<LabelType> ed){
		  startLabel = start; edge = ed; checked = false;
	   }

	   void setChecked(bool value){ checked = value; }
	   LabelType getStart()const { return startLabel; }
	   LabelType getEnd() const { return edge.getEndVertex(); }
	   int getWeight() const { return edge.getWeight(); }
	   bool isChecked() const { return checked; }

	   bool operator<(const PrimEdge &right)
	   {
		  return this->edge.getWeight() < right.getWeight();
	   }

    };


private:
    vector<PrimEdge<LabelType>> minSpanTree;
    vector<PrimEdge<LabelType>> startingEdges;
    LinkedStack<PrimEdge<LabelType>> removedEdges;

    void applyPrim();
    bool notConnected(LabelType &end1, LabelType &end2);
    void writeVector(ostream &os, vector<PrimEdge<LabelType>> &vect);

public:
    Prim(){}
    ~Prim(){}
    void displayMenu();
    void createMinSpanTree();
    void readGraph();
    void writeGraph();
    bool addEdge();
    bool removeEdge();
    bool undoRemove();
    void displayGraphDepth();
    void displayGraphBreadth();
    void writeMinSpanTree(ostream &os);
    void writeStartingEdges(ostream &os); // for debugging
    bool add(LabelType start, LabelType end, int edgeWeight = 0)
    {
	   if (LinkedGraph<LabelType>::add(start, end, edgeWeight))
	   {
		  Edge<LabelType> edge(end, edgeWeight);
		  PrimEdge<LabelType> newEdge(start, edge);
		  startingEdges.push_back(newEdge);
		  return true;
	   }
	   return false;
    }
    bool remove(LabelType start, LabelType end)
    {
	   vector<PrimEdge<LabelType>>::iterator iterElem;
	   for (iterElem = startingEdges.begin(); iterElem != startingEdges.end(); ++iterElem)
	   {
		  LabelType end1 = iterElem->getStart();
		  LabelType end2 = iterElem->getEnd();
		  if (start == end1 && end == end2 || start == end2 && end == end1){
			 startingEdges.erase(iterElem);
			 break;
		  }
	   }
	   return LinkedGraph<LabelType>::remove(start, end);
    }
};




template<class LabelType>
void Prim<LabelType>::displayMenu()
{
    int choice = 0;
    bool valid = true;
    while (valid)
    {
	   system("CLS");
	   cout << endl << endl << endl << endl;
	   cout << setw(20) << " " << "Prim Algorithm Demonstration" << endl;
	   cout << setw(40) << "Main Menu" << endl << endl;
	   cout << setw(20) << " " << "1.  Read Graph from file" << endl << endl;
	   cout << setw(20) << " " << "2.  add an edge to Graph" << endl << endl;
	   cout << setw(20) << " " << "3.  remove an edge from graph" << endl << endl;
	   cout << setw(20) << " " << "4.  undo removal(s)" << endl << endl;
	   cout << setw(20) << " " << "5.  display Graph with Depth-First traversal" << endl << endl;
	   cout << setw(20) << " " << "6.  display Graph with Breadth-First traversal" << endl << endl;
	   cout << setw(20) << " " << "7.  create minimum spanning tree" << endl << endl;
	   cout << setw(20) << " " << "8.  write Graph to file" << endl << endl;
	   cout << setw(20) << " " << "9.  Exit" << endl << endl;
	   cout << setw(20) << " " << "Enter Your Choice: ";
	   cin >> choice;

	   switch (choice)
	   {
	   case 1:
		 // readGraph();//Harshith
		  break;
	   case 2:
		  if(addEdge())//Trevor
			 break;
		  cout << "Could not add edge." << endl;
		  break;
	   case 3:
		  if(removeEdge())//Trevor
			 break;
		  cout << "Could not remove edge." << endl;
		  break;
	   case 4:
		  if(undoRemove())//Trevor
			 break;
		  cout << "Could not restore edge." << endl;
		  break;
	   case 5:
		 // displayGraphDepth();//Harshith
		  break;
	   case 6:
		 // displayGraphBreadth();//Harshith
		  break;
	   case 7:
		 // createMinSpanTree();//Victor
		  break;
	   case 8:
		 // writeGraph();//Harshith
		  break;
	   case 9:
		  cout << endl << "Exiting program!" << endl << endl;
		  valid = false;
		  break;
	   default:
		  cout << endl << endl;
		  cout << "\tThis is an invalid option please choose again!" << endl;
		  cout << endl << endl;
		  system("pause");
	   }
    }
}

template <class LabelType>
void Prim<LabelType>::createMinSpanTree()
{
    applyPrim();
}

template <class LabelType>
void Prim<LabelType>::writeMinSpanTree(ostream &os)
{
    writeVector(os, minSpanTree);
}

template <class LabelType>
void Prim<LabelType>::writeStartingEdges(ostream &os)
{
    writeVector(os, startingEdges);
}
// private functions:
/*
template <class LabelType>
void Prim<LabelType>::applyPrim()
{
    if (minSpanTree.size() > 0)
    {
	   minSpanTree.clear();
    }
    unvisitVertices(); // reset this graph
    int numEdges = startingEdges.size();
    int edgeCount = 0;
    for (int i = 0; i < numEdges && edgeCount < numberOfVertices - 1; ++i)
    {
	   for (int i = 0; i < minSpanTree.size(); ++i){ // reset for each edge
		  minSpanTree[i].setChecked(false);
	   }

	   PrimEdge<LabelType> *currEdge = &startingEdges[i];
	   LabelType start = currEdge->getStart(); // get name of start of edge
	   LabelType end = currEdge->getEnd(); // get name of end of edge
	   Vertex<LabelType>* startVertex = 0, *endVertex = 0;

	   startVertex = vertices.getItem(start); // get start Vertex from graph
	   endVertex = vertices.getItem(end); // get end Vertex from graph
	   if (// REMOVED //)
	   {
		  // NOT SHOWN

	   }

    }
}

// checks if end1 is already connected to end2 in the minimum spanning tree so far
template <class LabelType>
bool  Prim<LabelType>::notConnected(LabelType &end1, LabelType &end2)
{
    for (int i = 0; i < minSpanTree.size(); ++i)
    {
	   // THIS IS REALLY DIFFICULT, BUT NOT SHOWN BECAUSE YOU MAY HAVE
	   //    SIMILAR ALGORITHMS THAT NEED THIS
	   // ETC.
    }
    return true;
}
*/
template <class LabelType>
void Prim<LabelType>::writeVector(ostream &os, vector<PrimEdge<LabelType>> &vect)
{
    int size = vect.size();
    os << "vector size is " << size << " edges." << endl; //<-------------------------------------------------remove
    for (int i = 0; i < size; ++i){
	   PrimEdge<LabelType> edge = vect[i];
	   os << "From " << edge.getStart() << " to " << edge.getEnd()
		  << " with weight = " << edge.getWeight() << endl;
    }
}

template <class LabelType>
bool Prim<LabelType>::addEdge(){
    LabelType start, end;
    int weight;
    char choice;

    //Input variables
    system("CLS");
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;
    cout << "Enter 'Y' if you want to weight this edge, otherwise enter any other letter.";
	   cin >> choice;

    //In case user doesn't capitalize input
    choice = toupper(choice);

    //If user wants to weight edge, do so.  If not, the add function will default it to zero
    if (choice == 'Y')
    {
	   cout << "Enter edge weight: ";
	   cin >> weight;
    }

    //If edge is added successfully, let user know it was successful and return true
    if (add(start, end, weight))
    {
	   cout << "Edge successfully added!" << endl;
	   system("pause");
	   return true;
    }

    //Return false if unsuccessful
    return false;
}

template <class LabelType>
bool Prim<LabelType>::removeEdge()
{
    LabelType start, end;
    int weight;

    //Input variables
    system("CLS");
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;

    //Save the weight of the to be removed edge
    vector<PrimEdge<LabelType>>::iterator iterElem;
    for (iterElem = startingEdges.begin(); iterElem != startingEdges.end(); ++iterElem)
    {
	   LabelType end1 = iterElem->getStart();
	   LabelType end2 = iterElem->getEnd();
	   if (start == end1 && end == end2 || start == end2 && end == end1)
	   {
		  weight = iterElem->getWeight();
		  break;
	   }
    }

    //If edge is removed, let user know it was successful and push "removed edge" to stack. Then return true
    if (remove(start, end))
    {
	   cout << "Edge removed successfully!" << endl;
	   Edge<LabelType> ed(end, weight);
	   PrimEdge<LabelType> removed(start, ed);
	  
		  if (removedEdges.push(removed)){
		  cout << "Removal saved successfully!" << endl;
		  }
		  system("pause");
	   return true;
    }

    //Return false if unsuccessful
    return false;
}

template <class LabelType>
bool Prim<LabelType>::undoRemove()
{
    PrimEdge<LabelType> top; //will be the edge that was last removed
    LabelType start, end;
    int weight;

    //Save information from edge that was last removed in temp variables
    top = removedEdges.peek();
    start = top.getStart();
    end = top.getEnd();
    weight = top.getWeight();

    removedEdges.pop(); //pop top of stack once information is saved in temp variables

    //If successfully added, output success and info about added edge and return true
    system("CLS");
    if (add(start, end, weight))
    {
	   cout << "Undo removal of edge successful!" << endl;
	   cout << "Edge start: " << start << endl;		//Feel free to remove these cout statements if you'd prefer
	   cout << "Edge end: " << end << endl;
	   cout << "Edge weight: " << weight << endl;
	   system("pause");
	   return true;
    }

    //Return false if unsuccessful
    return false;
}

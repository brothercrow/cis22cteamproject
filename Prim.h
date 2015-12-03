#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "LinkedGraph.h"

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
    void addEdge();
    void removeEdge();
    void undoRemove();
    void displayGraphDepth();
    void displayGraphBreadth();
    void writeMinSpanTree(ostream &os);
    void writeStartingEdges(ostream &os); // for debugging
    template<class LabelType> 
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
    template<class LabelType>
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
	   cout << setw(26) << "Prim Algorithm Demonstration" << endl;
	   cout << setw(43) << "Main Menu" << endl << endl;
	   cout << setw(27) << " " << "1.  Read Graph from file" << endl;
	   cout << setw(27) << " " << "2.  add an edge to Graph" << endl;
	   cout << setw(27) << " " << "3.  remove an edge from graph" << endl;
	   cout << setw(27) << " " << "4.  undo removal(s)" << endl << endl;
	   cout << setw(27) << " " << "5.  display Graph with Depth-First traversal" << endl << endl;
	   cout << setw(27) << " " << "6.  display Graph with Breadth-First traversal" << endl << endl;
	   cout << setw(27) << " " << "7.  create minimum spanning tree" << endl << endl;
	   cout << setw(27) << " " << "8.  write Graph to file" << endl << endl;
	   cout << setw(27) << " " << "9.  Exit" << endl << endl;
	   cout << setw(27) << " " << "Enter Your Choice: ";
	   cin >> choice;

	   switch (choice)
	   {
	   case 1:
		  readGraph();//Harshith
		  break;
	   case 2:
		  addEdge();//Trevor
		  break;
	   case 3:
		  removeEdge();//Trevor
		  break;
	   case 4:
		  undoRemove();//Trevor
		  break;
	   case 5:
		  displayGraphDepth();//Harshith
		  break;
	   case 6:
		  displayGraphBreadth();//Harshith
		  break;
	   case 7:
		  createMinSpanTree();//Victor
		  break;
	   case 8:
		  writeGraph();//Harshith
		  break;
	   case 9:
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



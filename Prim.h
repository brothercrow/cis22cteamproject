#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
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
    vector<LabelType> locVertices;

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
    //Harshiths Code
    //template<class LabelType>
    void display(LabelType& anItem)
    {
	   cout << "Displaying item - " << anItem << endl;
    }
    void getVertices(LabelType& anItem)
    {
	   locVertices.push_back(anItem);
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
		  readGraph();//Harshith
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

//Harshiths Code
/**********************************************************************************************************************/
template <class LabelType>
void Prim<LabelType>::readGraph()
{
    string filename;
    ifstream ifs;
    LabelType start;
    LabelType end;
    string edgeweightcon;
    int edgeweight;
    cout << "Enter the input filename: ";
    getline(cin, filename);
    ifs.open(filename.c_str());

    //read stream line by line 
    //if line
    //concatanate the characters, seperate by start,end,edgeweight
    //then send to  testGraph->add(B, F, 3);
    if (ifs.is_open())
    {
	   while (getline(ifs, start, ','))
	   {
		  //getline(start, end, edgeweight);

		  cout << "start " << start << " ";

		  getline(ifs, end, ',');
		  cout << "End: " << end << " ";

		  getline(ifs, edgeweightcon, ',');
		  edgeweight = std::stoi(edgeweightcon, nullptr, 0);
		  cout << "edgeweight: " << edgeweight << " " << endl << endl;

		  add(start, end, edgeweight);
	   }
	   ifs.close();
    }

}
template <class LabelType>
void Prim<LabelType>::displayGraphDepth()
{
    LabelType startLabel = "A";
    cout << "\nDepth-first traversal (should be A B E F J C G K L D H M I N):" << endl;
    //LinkedGraph<LabelType>::
	//   depthFirstTraversal(startLabel, display);
	   
}

template <class LabelType>
void Prim<LabelType>::displayGraphBreadth()
{
    LabelType startLabel = "A";
    cout << "\nBreadth-first traversal (should be A B C D E F G H I J K L M N):" << endl;
    //LinkedGraph<LabelType>::
    //breadthFirstTraversal(startLabel, display);
}

template <class LabelType>
void Prim<LabelType>::writeGraph()
{
    ofstream myfile;
    LabelType startLabel = "A";
    myfile.open("output.txt");
    //writeStartingEdges(myfile);
    //traverseGraph(startLabel, myfile);
    myfile.close();

}

/***********************************************************************************************************/

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
template <class LabelType>
void Prim<LabelType>::applyPrim()
{
    if (minSpanTree.size() > 0)
    {
	   minSpanTree.clear();
    }
    unvisitVertices(); // reset this graph
    /*
    PrimEdge<LabelType>* curredge = &startingEdges[0];
    Vertex<LabelType> startVertex = vertices.getItem(curredge->getStart());
    Vertex<LabelType> minNeighbor;
    startVertex.visit();



    int k = 0;
    int weight = 0;
    int min = 600;
    while (k < numberOfVertices)
    {
	   min = 600;
	   for (int i = 0; i < numberOfVertices; i++)
	   {
		  if (startVertex.isVisited())
		  {
			 startVertex.resetNeighbor();
			 for (int j = 0; j < startVertex->getNumberOfNeighbors(); j++)
			 {
				Vertex<LabelType> neighbor = vertices.getItem(startVertex->getNextNeighbor());
				weight = startVertex->getEdgeWeight(neighbor->getLabel());
				if (weight < min)
				{
				    min = weight;
				    minNeighbor = neighbor;

				}
			 }
		  }
	   }
	   locVertices.push_back(startVertex->getLabel());
	   locVertices.push_back(minNeighbor->getLabel());
	   k++;

    }


    */

    system("CLS");
    writeVector(cout, startingEdges);
    //writeVector(cout, minSpanTree);

    system("pause");
    
}

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

// 315442236 aviad.becker@msmail.ariel.ac.il

#include <cstddef>
#include <iterator>
#include <list>
#include <vector>
#include <array>
#include "Graph.hpp"

class Node{
    public:
    int data;
    Node *next;

    Node(int d){
        data = d;
        next = NULL;
    }
};
//returns 1 if graph is connected
int isConnected(Graph g);


//returns shortes path, or -1
vector<int> shortestPath(Graph g, int start, int end);


// returns cycle path if contains cycle, 0 otherwise
vector<int> isContainsCycle( Graph g);


// return partition if Bipartite, 0 otherwise
vector<int> isBipartite( Graph g);


//return cycle if negative, otherwise NULL
int negativeCycle(Graph g);    


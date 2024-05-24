// 315442236 aviad.becker@msmail.ariel.ac.il


#include "Algorithms.hpp"
#include "Graph.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <limits>
#include <array>


using namespace std;
//returns 1 if graph is connected
int isConnected(Graph g){
    if(g.type == 1 || g.type == 3){
        return isConnectedUndirected(g.adjL, g.numOfVertices);
    }
    // turn graph into "undirected" and use same function
    Graph newGraph = turnGraph(g);
    return isConnectedUndirected(newGraph.adjL, newGraph.numOfVertices);
}


Graph turnGraph(Graph g){
    vector<vector<int>> newGraph = g.turnSymmetrical(g.mData);
    Graph* mine = new Graph(newGraph);
    return *mine;
}



int isConnectedUndirected(vector<vector<int>>adjL, int numOfV){
    if(dfs(numOfV, adjL, 0).size() <numOfV){
            return 0;
    }
    return 1;
}



//////////////////////////////////////////////////////////////////////////////////////////



vector<int> shortestPath(Graph g, int start, int end){
    if(g.type == 3 || g.type == 4){//regular BFS for unweighted
        return shortestPath3or4(g.numOfVertices, g.adjL, start, end);
    }
    if(!(g.negative)){
        // non negative weigths.  We'll use dijkstra algorithm
        return dijkstra(g, start, end);
    }
    
    //negative weights. We'll use Bellman-Ford
    return bellmanFord(g, start, end);
}


vector<int> bellmanFord(Graph g, int start, int end){
    vector<int> weights = updateWeights(g, start);
    vector<int> parents;
    for(int i=0; i< g.numOfVertices; i++){
        // v is the number of iterations
        for(int j=0; j< g.gData.size(); j++){
            vector<int> oldWeights = weights;
            weights = relax(g, weights, g.gData[j][0], g.gData[j][1]);
            if(oldWeights == weights){
                // change has been made
                parents[g.gData[j][1]] = g.gData[j][0];
            }
        }
    }

    vector<int> ans;
    ans.insert(ans.begin(), end);
    for(int i=0; i< parents.size(); i++){
        ans.insert(ans.begin(), parents[end]);
        end = parents[end];
    }
    return ans;
}



vector<int> dijkstra(Graph g, int start, int end){
    //update weights
    vector<int> weights = updateWeights(g, start);
    vector<int> visitedAndDone = updateVisited(g, start);
    vector<int> parents;
    int counter =0;
    while(visitedAndDone[end] == 0 || counter > g.numOfVertices){
        start = minWeights(weights);
        for(int i=0; i<g.adjL[start].size(); i++){
           // if neighbor visited and done already
           if(visitedAndDone[g.adjL[start][i]] == 1){
               continue;
            }
            weights = relax(g, weights, start, g.adjL[start][i]);
            parents[g.adjL[start][i]] = start;
         }
         visitedAndDone[start] = 1;
    }
    if (visitedAndDone[end] ==0){// must not be connected
        return {-1};
    }
    vector<int> ans;
    ans.insert(ans.begin(), end);
    for(int i=0; i< parents.size(); i++){
        ans.insert(ans.begin(), parents[end]);
        end = parents[end];
    }
    return ans;
}


vector<int> shortestPath3or4(const int v, vector<vector<int>> adjList, int start, int end){

    int visited[v];
    visited[start] = 1;

    queue<int> data;
    queue <int> empty;
    data.push(start);

    vector<int> ans;

    vector<int> parents = {-1};
    int almostLast = -1;

    while(!data.empty()){
        start = data.front();
        for(int i=0; i<adjList[start].size(); i++){
            if(adjList[start][i] == end){
                //got what we were looking for, get out
                almostLast = start;
                data.swap(empty);
                break;
            }
            if(visited[adjList[start][i]] == 0){   //haven't visited there yet
                parents[adjList[start][i]] = start;
                visited[adjList[start][i]] = 1;
                data.push(adjList[start][i]);
            }
            ans.push_back(data.front());
            data.pop();
        }
    
    if(almostLast = -1){
        return {-1};
    }
    int parent = -1;
    vector<int> toReturn;
    while(parent != start){
        toReturn.insert(toReturn.begin(), almostLast);
        parent = parents[almostLast];
    }
    return toReturn;
}
}







int minWeights(vector<int> weights){
    int ans = weights[0];
    for(int i=1; i< weights.size(); i++){
        if (weights[i] < ans){
            ans = weights[i];
        }
    }
    return ans;
}


vector<int> updateWeights(Graph g, int start){
    vector<int> ans = {-1};
    for(int i=0; i< g.numOfVertices; i++){
        if(i == start){
            ans.push_back(0);
        }
        ans.push_back(numeric_limits<int>::max());
    }
    return ans;
}


vector<int> updateVisited(Graph g, int start){
    vector<int> ans;
    for(int i=0; i< g.numOfVertices; i++){
        if(i == start){
            ans.push_back(1);
        }
        ans.push_back(0);
    }
    return ans;
}


vector<int> relax(Graph g, vector<int> weights, int start, int neighbor){
    int Edge = 1;
    Edge = updateEdge(g, start, neighbor);
    vector <int> ans;
    if(weights[neighbor] > weights[start] + Edge){
        weights[neighbor] = weights[start] + Edge;
    }
    return weights;
}


int updateEdge(Graph g, int start, int neighbor){
    int ans= 1;
    for(int i=0; i<g.gData.size(); i++){
        if(g.gData[i][0] == start && g.gData[i][1] == neighbor){
            return g.gData[i][2];
        }
    }
    return ans;
}


////////////////////////////////////////+++/////////////////////////////////////////////////////////


vector<int> isContainsCycle( Graph g){
    if( g.type == 1 || g.type == 3){
        // undirected graphs
        return isContainsCycleUndirected(g);
    }

    return isContainsCycledirected(g);
}



vector<int> isContainsCycleUndirected(Graph g){
    //we'll find using BFS
    queue<int> data;
    vector<int> parents;
    int start, last =-1;
    for(int i=0; i< g.adjL.size(); i++){
        if (!(g.adjL[i].empty())){
            data.push(i);
        }
    }
    while(!(data.empty())){
        start = data.front();
        data.pop();
        for(int i=0; i<g.adjL[start].size(); i++){
            if(parents[g.adjL[start][i]] != 0 && parents[g.adjL[start][i] != start]){
                //cycle detected
                last = g.adjL[start][i];
                break;
            }
            parents[g.adjL[start][i]] = start;
            data.push(g.adjL[start][i]);
        }
    }

    if(last = -1){ //couldn't find a cycle
        return {0};
    }
    int parent = -1;
    vector<int> toReturn;
    while(parent != last){
        toReturn.insert(toReturn.begin(), last);
        parent = parents[last];
    }

    return toReturn;
}






vector<int> isContainsCycledirected(Graph g){
    vector<int> visited;
    vector<int> inStack;
    vector<int> parents;
    int start, end = 0;
    visited[start] = 1;
    inStack[start] = 1;
    vector<int> ans;
    ans.push_back(start);

    ans = dfsHelperiii(0, g.adjL, ans, visited, inStack, parents);

}



vector<int> dfsHelperiii(int start, vector<vector<int>> adjList, vector<int> ans, vector<int> visited, vector<int> inStack, vector<int> parents){
    // stops at the end of it all
    int end = -1;
    for( auto it: adjList[start]){
        if(inStack[adjList[start][it]] == 1){
            //found cycle!
            end = adjList[start][it];
            break;
        }
        if(visited[adjList[start][it]] != 1){ //hasn't been visited -- update vectors
            inStack[adjList[start][it]] = 1;
            visited[adjList[start][it]]= 1;
            parents[adjList[start][it]] = start;
            dfsHelperiii(adjList[start][it], adjList, ans, visited, inStack, parents);
        }
    }

    int parent = -1;
    vector<int> toReturn;
    while(parent != end){
        toReturn.insert(toReturn.begin(), end);
        parent = parents[end];
    }

    if(parent == -1){
        // didn't find cycle
        return {-1};
    }
    return toReturn;
}





vector<int> dfs(const int v, vector<vector<int>> adjList, int start){
    // input graph as adj list , and returns all visited v's by order of visited
    vector<int> visited;
    visited[start] = 1;
    
    vector<int> ans;
    ans.push_back(start);
    ans = dfsHelper(start, adjList, ans, visited);

    return ans;
}


vector<int> dfsHelper(int start, vector<vector<int>> adjList, vector<int> ans, vector<int> visited){
    // stops at the end of it all
    visited[start] = 1;
    ans.push_back(start);
    for( auto it: adjList[start]){
        if(visited[adjList[start][it]] != 1){ //hasn't been visited
            dfsHelper(adjList[start][it], adjList, ans, visited);
        }
    }
    return ans;
}


vector<int> dfsHelper2(int start, vector<vector<int>> adjList, vector<int> ans, vector<int> visited){
    // stops when has been visited before
    visited[start] = 1;
    ans.push_back(start);
    for( auto it: adjList[start]){
        if(visited[adjList[it][start]] == 1){ //has been visited! cycle
            return ans;
        }
        dfsHelper2(adjList[it][start], adjList, ans, visited);
    }
    return ans;
}








///////////////////////////////////////////////////////
// will return red team if there is Bipartite (last number will be number total of v's), else returns -1.  help using https://www.geeksforgeeks.org/bipartite-graph/
vector<int> isBipartite(Graph g){
    vector<int> ans = bfsColor(g.numOfVertices, g.adjL);
    ans.push_back(g.numOfVertices);
    return ans;
}





vector<int> bfsColor(const int v, vector<vector<int>> adjList){

    int visited[v];
    visited[0] = 1;


    vector<int> red;
    vector<int> blue;


    queue<int> data;
    data.push(0);
    red.push_back(0);
    int flag =1; // flag 1 - red, flag 0- blue

    vector<int> ans;
    int start;
    while(!data.empty()){
        flag = 1 - flag;
        start = data.front();
        for(int i=0; i<adjList[start].size(); i++){
            if(visited[adjList[start][i]] == 0){  
                 //haven't visited there yet
                if(flag == 1){
                    red[adjList[start][i]] = 1;
                }
                else{
                    blue[adjList[start][i]] = 1;
                }
                // check if violation
                if((red[adjList[start][i]] = 1 ) && (blue[adjList[start][i]]= 1)){
                    return {-1};
                }
                visited[adjList[start][i]] = 1;
                data.push(adjList[start][i]);
            }
            ans.push_back(data.front());
            data.pop();
        }
        for(int i=0; i< sizeof(visited)/ sizeof(int); i++){
            // check if visited them all
            if(visited[i] != 0){
                    start = i;
                    data.push(i);
                    break;
            }
       }
    }

    return red;
}





































/////////////////////////////////////////////////////////////////////////////////////////////////////
//return cycle if negative, otherwise NULL (using Bellman-Ford)
int negativeCycle(Graph g){
    if(!g.negative){
        return 0;
    }
    vector<int> oldWeights = bellmanFordii(g);
    vector<int> newerWeights = oldWeights;
    // one lase iteration
    for(int j=0; j< g.gData.size(); j++){
        newerWeights = relax(g, newerWeights, g.gData[j][0], g.gData[j][1]);
        }
    if(newerWeights != oldWeights){
        //hence there was an update, and there is a negative cycle
        return 1;
    }
    return 0;
}

vector<int> bellmanFordii(Graph g){
    vector<int> weights = updateWeights(g, 0);
    for(int i=0; i< g.numOfVertices; i++){
        // v is the number of iterations
        for(int j=0; j< g.gData.size(); j++){
            vector<int> oldWeights = weights;
            weights = relax(g, weights, g.gData[j][0], g.gData[j][1]);
        }
    }
    return weights;
}



vector<int> bfs(const int v, vector<vector<int>> adjList, int start){

    int visited[v];
    visited[start] = 1;

    queue<int> data;
    data.push(start);

    vector<int> ans;

    while(!data.empty()){
        start = data.front();
        for(int i=0; i<adjList[start].size(); i++){
            if(visited[adjList[start][i]] == 0){   //haven't visited there yet
                visited[adjList[start][i]] = 1;
                data.push(adjList[start][i]);
            }
            ans.push_back(data.front());
            data.pop();
        }
    
    return ans;
}
}



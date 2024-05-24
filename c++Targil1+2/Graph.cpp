// 315442236 aviad.becker@msmail.ariel.ac.il

#include "Graph.hpp"

#include <vector>
#include <array>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

bool Graph::printGraph(vector<vector<int>> matrix){
        if(matrix.size() != matrix[0].size()){
            cout << "Graph not compatible from size perspective"<< endl;
            return false;
        }
        int numOfEdges = 0;
        int numOfVertices = matrix[0].size();
        for (int i=0; i< matrix.size(); i++){
            for (int j=0; j< matrix[0].size(); j++){
                if(matrix[i][j] != 0){
                    numOfEdges += 1;
                };
            };
        };
        cout << "Graph with "<< numOfVertices << "vertices and " << numOfEdges <<" edges."<< endl;
        return true;    
    };

vector<array<int, 3>> Graph::loadGraph(vector<vector<int>> matrix){
    vector<array<int, 3>> ans;
    for(int i=0; i< matrix.size(); i++){
        for (int j=0; j< matrix.size(); j++){
            if(matrix[i][j] != 0){
                ans.push_back({i, j, matrix[i][j]});
            }
        }
    }
    return ans;
}


pair<int, int> Graph:: numOfVerticesAndEdges(vector<vector<int>> matrix){
    int numOfEdges = 0;
    int numOfVertices = matrix[0].size();
    for (int i=0; i< matrix.size(); i++){
        for (int j=0; j< matrix[0].size(); j++){
            if(matrix[i][j] != 0){
                numOfEdges += 1;
                };
            };
        };
    pair<int, int> ans = {numOfVertices, numOfEdges};
    return ans;
}



vector<vector<int>> Graph::adjList(vector<array<int, 3>> gData){
    vector<vector<int>> ans;
    vector<int> data;
    int numOfRow = 0;
    for(int i=0; gData.size(); i++){
        if(gData[i][0] != numOfRow){
            ans.push_back(data);
            numOfRow +=1;
            data.clear();
            data.push_back(gData[i][1]);
            continue;
        }
        // add neighbor
        data.push_back(gData[i][1]);
    }
    return ans;
    // vector[0] holds all neighbors of V0
}


int Graph::typeOfGraph(vector<vector<int>> matrix){
    // types:   1 - weigthed but undirected,  2- weighted and directed, 3- not weighed and undirected, 4- not weighted and directed
    if(weighted(matrix)){
        if(symmetrical(matrix)){
            return 1;
        }
        return 2;
    }
    if(symmetrical(matrix)){
        return 3;
    }
    return 4;
}



bool weighted(vector<vector<int>> matrix){
     for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            if(matrix[i][j] !=0 && matrix[i][j] != 1){
                return false;
            }
        }
    }
    return true;
}


bool symmetrical(vector<vector<int>> matrix){
     for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            if(matrix[i][j] != matrix[j][i]){
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> Graph::turnSymmetrical(vector<vector<int>> matrix){
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            if( i> j){
                // change to the higher one that isn't equal to zero
                if(matrix[i][j] != matrix[j][i]){
                    if(matrix[i][j] != 0){
                        matrix[j][i] = matrix[i][j];
                    }
                    matrix[i][j] = matrix[j][i];
                }
            }
        }
    }
    return matrix;
}



bool Graph::hasNegative(vector<vector<int>> matrix){
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            if(matrix[i][j] < 0){
                return true;
            }
        }
    return false;
}
}
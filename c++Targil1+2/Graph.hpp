// 315442236 aviad.becker@msmail.ariel.ac.il

#include <cstddef>
#include <iterator>
#include <list>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

#pragma once

// declare class

// we will look at a graph as a vector of vectors. every inner vector of size 3. Where vertice (start, end, weight)
// we will keep matrix to use in some cases
class Graph{
    public:
    vector<vector<int>> mData;
    vector<array<int, 3>> gData;
    vector<vector<int>> adjL;
    int numOfVertices;
    int numOfEdges;
    bool negative;// true if there is a negative weight
    int type; // 1- undirected graph, 2- only positive weights, 3 - negative weights allowed  //גרף מכוון ולא מכוון וגם גרף ממושקל 


    bool operator==(Graph g2){


        if(!(*this < g2) && !(*this>g2)){
            return true;
        }

        for(int i=0; i< g2.mData.size(); i++){
            for(int j=0; j<g2.mData[0].size();j++){
                if(this->mData[i][j] != g2.mData[i][j]){
                    return false;
                }
            }
        }
        return true;
    }


    bool operator>(Graph g2){
        int flag=0;
        for(int i=0; i<g2.mData.size(); i++){
            for(int j=0; j<g2.mData[0].size(); j++){
                if(this->mData[i][j] != g2.mData[i][j]){
                    // אין הכלה
                    i = g2.mData.size();
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0 && this->numOfEdges < g2.numOfEdges){
            // מוכל ממש 
            return true;
        }

        if(this->numOfEdges > g2.numOfEdges){
            // לא מוכל ממש אבל קטן מ
            return true;
        }

         if(this->numOfVertices > g2.numOfVertices){
            // לפי סדר גודל
            return true;
        }
        return false;
    }

    bool operator<(Graph g2){
        int flag = 0;
        for(int i=0; i<this->mData.size(); i++){
            for(int j=0; j<this->mData[0].size(); j++){
                if(this->mData[i][j] != g2.mData[i][j]){
                    // אין הכלה
                    i = this->mData.size();
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0 && this->numOfEdges < g2.numOfEdges){
            // מוכל ממש 
            return true;
        }

        if(this->numOfEdges < g2.numOfEdges){
            // לא מוכל ממש אבל גדול מ
            return true;
        }
        if(this->numOfVertices < g2.numOfVertices){
            // לפי סדר גודל
            return true;
        }
        return false;
    }


    bool operator>=(Graph g2){
        if((*this == g2) || (*this > g2)){
            return true;
        }
        return false;
    }


    bool operator<=(Graph g2){
        if((*this == g2) || (*this < g2)){
            return true;
        }
        return false;
    }


    

    Graph operator++(){
        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(this->mData[0].size());
        }

        for(int i=0; i<this->mData.size(); i++){
            for (int j=0; j< this->mData[0].size(); j++){
                if(this->mData[i][j] != 0){
                    mat[i][j] = this->mData[i][j] + 1;
                }
            }
        }
        
        Graph newGraph = Graph(mat);
        return newGraph;
    }

    
    Graph operator--(){
        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(this->mData[0].size());
        }

        for(int i=0; i<this->mData.size(); i++){
            for (int j=0; j< this->mData[0].size(); j++){
                if(this->mData[i][j] != 0){
                    mat[i][j] = this->mData[i][j] - 1;
                }
            }
        }
        
        Graph newGraph = Graph(mat);
        return newGraph;
    }

    
    Graph operator*=(int num){
        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(this->mData[0].size());
        }

        for(int i=0; i<this->mData.size(); i++){
            for (int j=0; j< this->mData[0].size(); j++){
                if(this->mData[i][j] != 0){
                    mat[i][j] = this->mData[i][j] * num;
                }
            }
        }
        
        Graph newGraph = Graph(mat);
        return newGraph;
    }


    Graph operator+(Graph g2){
        if((this->mData.size() != g2.mData.size()) ||  (this->mData[0].size() != g2.mData[0].size())){
            perror("unsuitable matrices \n");
            return;
        }
        Graph newGraph = Graph(g2.mData);
        for(int i=0; i<g2.gData.size(); i++){
            for(int j=0; j<g2.gData[0].size(); j++){
                newGraph.mData[i][j] = this->mData[i][j] + g2.mData[i][j];
            }
        }
        return newGraph;
    }


    Graph operator+(){

        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(this->mData[0].size());
        }


        for(int i=0; i<this->mData.size(); i++){
            for(int j=0; j< this->mData[0].size(); j++){
                +mat[i][j];
            }
        }

        Graph newGraph = Graph(mat);
        return newGraph;
    }


    Graph operator-(Graph g2){
        if((this->mData.size() != g2.mData.size()) ||  (this->mData[0].size() != g2.mData[0].size())){
            perror("unsuitable matrices \n");
            return;
        }
        Graph newGraph = Graph(g2.mData);
        for(int i=0; i<g2.gData.size(); i++){
            for(int j=0; j<g2.gData[0].size(); j++){
                newGraph.mData[i][j] = this->mData[i][j] - g2.mData[i][j];
            }
        }
        return newGraph;
    }


      Graph operator-(){

        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(this->mData[0].size());
        }


        for(int i=0; i<this->mData.size(); i++){
            for(int j=0; j< this->mData[0].size(); j++){
                -mat[i][j];
            }
        }

        Graph newGraph = Graph(mat);
        return newGraph;
    }


    Graph operator*(Graph g2){
        if(this->mData[0].size() != g2.mData.size()){
            perror("unsuitable matrices \n");
            return;
        }
        vector<vector<int>> mat(this->mData.size());
        for(int i=0; i< this->mData.size(); i++){
            mat[i].resize(g2.mData[0].size());
        }

        for(int i=0; i< this->mData.size(); i++){
            for (int j=0; j<g2.mData.size(); j++){
                for(int k=0; i<g2.mData[0].size(); k++){
                    mat[i][j] += this->mData[i][k] * g2.mData[k][j];
                }
            }
        }

        Graph newGraph = Graph(mat);
        return g2;
    }

    friend ostream& operator<<(ostream& os, Graph const& obj){
        return os << obj.printGraph(obj.mData) <<endl;
    } 
    
   
   
    Graph(vector<vector<int>> mData){
        mData = mData;
        gData = loadGraph(mData);
        numOfVertices, numOfEdges= numOfVerticesAndEdges(mData).first, numOfVerticesAndEdges(mData).second;
        type = typeOfGraph(mData);
        adjL = adjList(gData);
        negative = hasNegative(mData);
    }


    // returns true if loaded
    static bool printGraph(vector<vector<int>> matrix);

    static vector<array<int,3>> loadGraph(vector<vector<int>> matrix);

    static pair<int, int> numOfVerticesAndEdges(vector<vector<int>> matrix);

    vector<vector<int>> adjList(vector<array<int, 3>> gData);

    static int typeOfGraph(vector<vector<int>> matrix);
    
    vector<vector<int>> turnSymmetrical(vector<vector<int>> matrix);

    bool hasNegative(vector<vector<int>> matrix);

};
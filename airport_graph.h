#pragma once 

#include <vector>
#include <string> 
#include <unordered_map>
#include "Airport.h"
// #include "PageRank.h"

using namespace std; 

class Graph {
    public:
        Graph();
        //constructor that accepts the airport and routes.dat files
        Graph(string & airportFile, string & routesFile);
        
        //functions to insert vertices
        void insertVertex(int v, Airport ap);
        void insertAllVertices(std::string & fileName);
        
        //functions to create and insert edges
        vector<string> _createEdge(string & line);
        Flight createEdge(vector<string> flightVector);     
        void insertEdge(Flight f);
        void insertAllEdge(std::string & fileName);
        
        //functions that return private maps for debugging
        unordered_map<int, Airport> getVertices();
        unordered_map<int, Flight> adjVertWithWeight(int airportID);
        string getAPName(int ID);
        
        //function to harvest adjmatrix from a graph obj
        void adjMatrix(PageRank* pr_obj);

    private: 
        unordered_map<int, Airport> vertices; 

        //functions that calculate the weight of an edge
        double calcWeight(int fromID, int toID);
        double radianConvert(double degree);

}
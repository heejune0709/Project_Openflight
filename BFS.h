#pragma once

#include "airport_graph.h"
#include <string> 
#include <queue>
#include <stack> 


using namespace std; 

class BFS {
    public: 
        BFS(const string &airportFile, const string &routerFile); 
        vector<string> traverseAllAirports(int sourceAirport);
        vector<string> traverseAirportsWithMoves(int sourceAirport, int moves); 
        vector<string> traverseAirportsToDestination(int sourceAirport, int destinationAirport);

    private: 
        Graph airport_graph;        
};
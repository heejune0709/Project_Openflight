#include "BFS.h"
#include <climits> 

// Constructor for BFS class
BFS::BFS(const string &airportFile, const string &routeFile) {
    string a = airportFile; 
    string r = routeFile; 
    airport_graph = Graph (a, r);
}

// Returns a vector of strings containing airport names visited in BFS order
// This function traverses all aiports that contains the source airport 
vector<string> BFS::traverseAllAirports(int sourceAirport) {
    vector<string> traversalResult;
    
    // Initialize all to 'not visited' and declare a vector to track visited airports. 
    vector<bool> isVisited(14111, false);
    
    
    // Initialize BFS queue and mark the source airport as visited
    queue<int> airportQueue;
    airportQueue.push(sourceAirport);
    int currentAirport = sourceAirport;
    isVisited[currentAirport] = true;
    
    // Performing BFS with queue
    while (!airportQueue.empty()) {
        currentAirport = airportQueue.front();
        traversalResult.push_back(airport_graph.getAPName(currentAirport));
        
        // Iterate through all adjacent airports of the current airport
        for (const auto& adjacentAirport : airport_graph.adjVertWithWeight(currentAirport)) {
            if (!isVisited[adjacentAirport.first]) {
                airportQueue.push(adjacentAirport.first);
                isVisited[adjacentAirport.first] = true;
            }
        }
        airportQueue.pop();
    }
    return traversalResult;
}

// Returns a vector of strings with airport names visited in BFS order up to the given number of moves
vector<string> BFS::traverseAirportsWithMoves(int sourceAirport, int moves) {
    vector<string> traversalResult;
    
    // Initialize all to 'not visited' and declare a vector to track visited airports. 
    vector<bool> isVisited(14111, false);
    
    // Initialize BFS queue and mark the source airport as visited 
    queue<int> airportQueue;
    airportQueue.push(sourceAirport);
    int currentAirport = sourceAirport;
    isVisited[currentAirport] = true;
    
    // Performing BFS using a queue
    while (!airportQueue.empty()) {
        // If the number of moves is reached, stop
        if (traversalResult.size() == static_cast<unsigned>(moves) + 1) {
            return traversalResult;
        }

        currentAirport = airportQueue.front();
        traversalResult.push_back(airport_graph.getAPName(currentAirport));
        
        // Iterate through all adjacent airports of the current airport
        for (const auto& adjacentAirport : airport_graph.adjVertWithWeight(currentAirport)) {
            if (!isVisited[adjacentAirport.first]) {
                airportQueue.push(adjacentAirport.first);
                isVisited[adjacentAirport.first] = true;
            }
        }
        airportQueue.pop();
    }

    return traversalResult;
}

// Returns a vector of strings with airport names visited in BFS order up to the destination airport
// If there is no traversal between the source and destination, returns an empty vector
vector<string> BFS::traverseAirportsToDestination(int sourceAirport, int destinationAirport) {
    vector<string> traversalResult;
    
    // Initialize all to 'not visited' and declare a vector to track visited airports. 
    vector<bool> isVisited(14111, false);
    
    queue<int> airportQueue;
    airportQueue.push(sourceAirport);
    int currentAirport = sourceAirport;
    isVisited[currentAirport] = true;
    
    // Performing BFS using a queue
    while (!airportQueue.empty()) {
        currentAirport = airportQueue.front();
        
        if (currentAirport == destinationAirport) {
            traversalResult.push_back(airport_graph.getAPName(currentAirport));
            break;
        }
        
        traversalResult.push_back(airport_graph.getAPName(currentAirport));
        
        // Iterate through all adjacent airports of the current airport
        for (const auto& adjacentAirport : airport_graph.adjVertWithWeight(currentAirport)) {
            if (!isVisited[adjacentAirport.first]) {
                airportQueue.push(adjacentAirport.first);
                isVisited[adjacentAirport.first] = true;
            }
        }
        airportQueue.pop();
    }
    
    // Return an empty vector, if the destination airport is not reached. 
    if (currentAirport != destinationAirport) {
        return vector<string>();
    }
    
    return traversalResult;
}


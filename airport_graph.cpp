//Graphs Class

#include "airport_graph.h"
#include <math.h> 
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;


// Default
Graph::Graph() {}


// Constructor with airport.dat and routes.dat
Graph::Graph(std::string & airportFile, std::string & routesFile) {
    insertAllVertices(airportFile);
    insertAllEdge(routesFile);
}


// Construct the vertices so eeach airport object is connected with its ID
void Graph::insertVertex(int v, Airport ap) {
    vertices[v] = ap;
}


// Insert each airport into the class line by line
void Graph::insertAllVertices(std::string & fileName) {
    std::fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;
        while(getline(file, currLine)){ 
            int comma = 0;
            for(unsigned i = 0; i < currLine.size(); ++i){
                char current = currLine[i];
                if(current == ',')
                    comma++;
            }
            if(comma == 13){
                Airport ap(currLine);
                insertVertex(ap.getAirportID(), ap);
            }
        }
        file.close(); 
    }
}


// Helper function that converts a line of flight data to a vector
std::vector<std::string> Graph::_createEdge(string & line){
    std::string currString = "";
    std::vector<std::string> flightVector;

    int comma = 0;
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];
        if(current == '\\')
            return flightVector;
        if(current == ',')
            comma++;
    }
    if(comma != 8)
        return flightVector;
    
    // Iterate through all characters in the line
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];
        //if a comma is detected, push the current string to the vector
        if(current == ',') {
            flightVector.push_back(currString);
            currString = "";
        }
        //else if it's just a regular char, append it to the current string
        else
            currString += current;
    }

    return flightVector;
}


// Creates an edge from a vector generated from above function
   /*
        Prior to calculating the weight, ensure that both source and destination airports have been added.
        This prevents inadvertently inserting an element into the map using the [] operator.
        If an edge to the same destination is not found in the list of adjacent airports,
        the find function returns the key of the desired element or the end iterator if the element is not found.
        Insertion occurs only when the flight does not exist in the airport's adjacency list.
    */
Flight Graph::createEdge(std::vector<std::string> flightVector){
    int source = stoi(flightVector[3], nullptr);
    int dest = stoi(flightVector[5], nullptr);
    auto it = vertices.find(source);
    auto it2 = vertices.find(dest);
    if(it != vertices.end() && it2 != vertices.end()){
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    // If either airport is not inserted, return default constructed flight
    return Flight();
}


/*
    Inserts a single edge by invoking the two helper functions mentioned above.
    Before inserting, the function verifies if the flight already exists.
    If an edge to the same destination is absent in the list of adjacent airports,
    the find function returns either the key of the desired element or the end iterator if the element is not found.
    Insertion takes place only when the flight is not present in the airport's adjacency list.
*/
void Graph::insertEdge(Flight f){       
    int source = f.getSourceId();
    int dest = f.getDestId();

    if (vertices[source].destAPs.find(dest) == vertices[source].destAPs.end())   
        (vertices[source].destAPs)[dest] = f;
}

// Iterates through routes.dat and insert flight for each line 
void Graph::insertAllEdge(std::string & fileName){
    std::fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;
                    
        while(getline(file, currLine)){ 
            std::vector<std::string> currVect = _createEdge(currLine);
            if(currVect != std::vector<std::string>()){
                Flight f = createEdge(currVect);
                Flight defaultF = Flight();
                if(!(f == defaultF))
                    insertEdge(f);
            }
        }
        file.close(); 
    }
}

// Returns the unordered_map containing airports
// For testing purposes: iterate through the unordered_map to view all added airports
unordered_map<int, Airport> Graph::getVertices(){
    return vertices;
}


// Returns the flights departing from the given airport
// For testing purposes: iterate through the unordered_map to view added flights
unordered_map<int, Flight> Graph::adjVertWithWeight(int airportID) {
    auto it = vertices.find(airportID);
    if(it != vertices.end()){
        Airport& ap = vertices[airportID];
        return ap.destAPs;
    }
    return unordered_map<int, Flight> ();
}

string Graph::getAPName(int ID){
    auto it = vertices.find(ID);
    if(it != vertices.end()){
        return vertices[ID].getAirportName();
    }
    return string();
}


// Citation: https://www.geeksforgeeks.org/program-distance-two-points-earth/
double Graph::calcWeight(int fromID, int toID) {
    // Converting the latitude and longitude to radian
    double lat1 = radianConvert(vertices[fromID].getAirportLatitude());
    double lon1 = radianConvert(vertices[fromID].getAirportLongitude());
    double lat2 = radianConvert(vertices[toID].getAirportLatitude());
    double lon2 = radianConvert(vertices[toID].getAirportLongitude());

    double lonDiff = lon2 - lon1;
    double latDiff = lat2 - lat1;
    
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    double R = 6371;
    ans *= R;
    return ans; 
}


// Helper function to calculate weight 
double Graph::radianConvert(double degree) {
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
 

// Traversal graph to populate adj matrix for pagerank
void Graph::adjMatrix(PageRank *pr_obj) {
    // Determine and set the dimention
    int size = vertices.size();
    pr_obj->matrix_.resize(size,vector<double>(size));
    pr_obj->title.resize(size);
    pr_obj->num = size;

    // Initialize obj matrix
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            pr_obj->matrix_[i][j] = 0.0;
        }        
    }

    // Populate the namelist of pagerank obj
    int x = 0;
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        if(it->second.getAirportID() == 0){
            continue;
        }
        pr_obj->title[x] = (it->second.getAirportID());
        x++;     
    }
    
    // Examine each flight for every airport
    // Insert the weight into the adjacency matrix based on the order specified in the name list
    x = 0;
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        if(x == size) break;
        if(it->second.getAirportID() == 0){
            continue;
        }
        
        // Inspect flights for the current vertex/airport
        // Determine the appropriate position for the weight of the current flight based on the name list
        for(auto flight = it->second.destAPs.begin(); flight != it->second.destAPs.end(); ++flight){
            int y = 0;
            for (auto temp = pr_obj->title.begin(); temp != pr_obj->title.end(); ++temp) {
                if (*temp == flight->second.getDestId()) break;
                y++;
            } 
            if(y == size) break;
            pr_obj->matrix_[y][x] = flight->second.getWeight();
        }
        x++;
    }
}


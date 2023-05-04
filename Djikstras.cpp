#include "Djikstras.h"

using namespace std;


// `Djikstras::Djikstras(Graph airports, string OgAirport, string DtAirport)

// This is the implementation of the constructor for the Djikstras class. 
// It initializes various data structures such as 
// `zip_dist`, `prev_node`, `visited`, `adj`, and `Qu` 
// It runs Dijkstra's algorithm to find the shortest path between the two airports. 
// The result is stored in `zip_path` and `path` member variables!

Djikstras::Djikstras(Graph airports, string OgAirport, string DtAirport) {
    zip_path.clear();
    vector<string> vert;  
    unordered_map<int, Airport> mapAirport = airports.getVertices();

    // Initializing data structures for each airport
    for (auto it = mapAirport.begin(); it != mapAirport.end(); ++it) {
        vert.push_back(it->second.getAirportName());
        if(it->second.getAirportName() == OgAirport) {
            zip_dist.insert(make_pair(it->second.getAirportName(), 0.0));
            prev_node.insert(make_pair(it->second.getAirportName(), ""));
            visited.insert(make_pair(it->second.getAirportName(), false));
        }
        else {
            zip_dist.insert(make_pair(it->second.getAirportName(), INT_MAX));
            prev_node.insert(make_pair(it->second.getAirportName(), ""));
            visited.insert(make_pair(it->second.getAirportName(), false));
        }
    }

    pair<double,string> init = make_pair(0.0, OgAirport);
    Qu.push(init);

    // Storing adjacency lists for each airport
    for (auto it = mapAirport.begin(); it != mapAirport.end(); ++it) {
        adj.insert(make_pair(it->second.getAirportName(), it->second.destAPs));
    }

    // Dijkstra's algorithm
    while (Qu.top().second != DtAirport) {
        pair<double, string> curr = Qu.top();
        Qu.pop();
        vector<pair<int , double>> near = getAdj(curr.second);
        vector<pair<string, double>> nearBy;
        
        // Converting neighboring airport IDs to airport names
        for (auto n : near) {
            for (auto it = mapAirport.begin(); it != mapAirport.end(); ++it) {
                if (n.first == it->first) {
                    nearBy.push_back(make_pair(it->second.getAirportName(), n.second));
                }
            }
        }

        // Updating shortest distances to neighboring airports
        for (auto b : nearBy) {
            if (visited[b.first] == false && visited[curr.second] == false) {
                double weight = b.second;
                if(weight + zip_dist[curr.second] < zip_dist[b.first]) {
                    zip_dist[b.first] = weight + zip_dist[curr.second];
                    prev_node[b.first] = curr.second;
                    Qu.push(make_pair(zip_dist[b.first], b.first)); 
                }
            }
        }
        visited[curr.second] = true;
    }

    // Storing shortest path and distance
    path = zip_dist[DtAirport];
    string air = DtAirport;
    zip_path.push_back(DtAirport);

    while (air != OgAirport) {
        zip_path.push_back(prev_node[air]);
        air = prev_node[air];
    }
    reverse(zip_path.begin(), zip_path.end());
}

// double Djikstras::getShortDist() const

// This function is a getter function that returns 
// the shortest distance between the starting and destination airports.

double Djikstras::getShortDist() const {
  return path;
}

// `vector<string> Djikstras::getPathVert() const`

// This function is a getter function that returns a vector of strings representing the names of all the airports 
// along the shortest path from the starting airport to the destination airport.

vector<string> Djikstras::getPathVert() const {
  return zip_path;
}

// `vector<pair<int, double>> Djikstras::getAdj(string Name)`

// This function takes in a string `Name` representing the name of an airport and returns a vector of pairs, 
// where each pair represents a neighboring airport and its flight distance from the input airport.

vector<pair<int, double>> Djikstras::getAdj(string Name) {
    auto check = adj.find(Name);

    if (check == adj.end())
        return vector<pair<int,double>>();

    else {
        vector<pair<int,double>> vert_list;
        unordered_map<int, Flight> &map = adj.at(Name);
        for (auto it = map.begin(); it != map.end(); it++) {
            vert_list.push_back(make_pair(it->first, it->second.getWeight()));
        }
        return vert_list;
    }
}

// `bool Djikstras::checkVertex(string name)`

// This is a helper function that takes in a string `name` representing the name of an airport 
// and checks whether it exists in the adjacency list. 
// It returns a boolean value indicating whether the vertex exists or not.

bool Djikstras::checkVertex(string name) {
    if (adj.find(name) == adj.end()) {
        return false;
    }
    return true;
}

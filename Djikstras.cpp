#include "Djikstras.h"

using namespace std;


/* 
*	Djikstras(Graph airports, string OgAirport, string DtAirport)
*	Description: Implementation of Djikstra's algorithm for finding the shortest path between airports.
*	input: airports -- Graph of the connecting airports
*	       OgAirport -- the starting airport
*	       DtAirport -- the destination airport
*	return: N/A
*/
Djikstras::Djikstras(Graph airports, string OgAirport, string DtAirport) {
    zip_path.clear();

    vector<string> vert;  

    unordered_map<int, Airport> mapAirport = airports.getVertices();

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

    for(auto it = mapAirport.begin(); it != mapAirport.end(); ++it) {
        adj.insert(make_pair(it->second.getAirportName(), it->second.destAPs));
    }

    while(Qu.top().second != DtAirport) {
        pair<double, string> curr = Qu.top();
        Qu.pop();
        vector<pair<int , double>> near = getAdj(curr.second);
        vector<pair<string, double>> nearBy;
        for (auto n : near) {
            for (auto it = mapAirport.begin(); it != mapAirport.end(); ++it) {
                if (n.first == it->first) {
                    nearBy.push_back(make_pair(it->second.getAirportName(), n.second));
                }
            }
        }
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
 
    path = zip_dist[DtAirport];
    string air = DtAirport;
    zip_path.push_back(DtAirport);

    while(air != OgAirport) {
        zip_path.push_back(prev_node[air]);
        air = prev_node[air];
    }

    reverse(zip_path.begin(), zip_path.end());
}

/* 
*	getShortDist()
*	Description: getter function
*	return: gets the path distance from the starting airport to the destination airport
*/
double Djikstras::getShortDist() const {
  return path;
}

/* 
*	getPathVert()
*	Description: getter function
*	return: gets all of the airports along the path
*/
vector<string> Djikstras::getPathVert() const {
  return zip_path;
}

/* 
*	getAdjacent(string Name)
*	Description: This function finds all of the neighboring airports to the input airport 
    and returns a vector of the neighboring airport and its flight distance from the input airport.
*	input: Name -- the name of the airport as a string
*	return: a vector of pairs of neighboring airports and their respective distances from the input airport
*/
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

/* 
*	vertexExists(string name)
*	Description: This function ensures that an airport exists in the adjacency list.
*	input: name -- the name of the airport as a string
*	return: boolean that indicate whether the vertex exist or not
*/
bool Djikstras::checkVertex(string name) {
    if (adj.find(name) == adj.end()) {
        return false;
    }
    return true;
}

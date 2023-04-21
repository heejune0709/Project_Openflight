#pragma once
#include "airport_graph.h"
#include "Flight.h"
#include "Airport.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
#include <climits>
#include <stack>

using namespace std;

class Djikstras {

    public:
        Djikstras (Graph airports, string OgAirport, string DtAirport);

        //getters
        double getShortDist() const;
        vector<string> getPathVert() const;
        vector<pair<int, double>> getAdj(string Name);

        //helper function that checks whether the vertex exist
        bool checkVertex(string node);

    private:
        map<string, double> zip_dist;
        unordered_map<string, string> prev_node;
        priority_queue<pair<double, string>, vector<pair<double, string>>,greater<pair<double, string>>> Qu;
        unordered_map <string, bool> visited; 
        unordered_map<string, unordered_map<int, Flight>> adj;
        vector<string> zip_path;
        double path;

};

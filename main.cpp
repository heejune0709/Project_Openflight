#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "Airport.h"
#include "PageRank.h"
#include "airport_graph.h"
#include "Djikstras.h"
#include "BFS.h"

using namespace std;


int main() {
    cout << ""<< endl;
    cout << "CS225 Final Project: OpenFlights" << endl;
    
    while(true) {
        string airportFile;
        string routesFile;
        string StartingAirport;
        string DestinationAirport;
        
        bool validDataset = false;
        
        while(validDataset == false){
            // For using selected datasets Enter the data file 
            cout << "Enter \"default\" to construct graph using datasets from OpenFlights.org \nor enter name of airports dataset" << endl;
            string airportIn;
            cin >> airportIn;
            if(airportIn != "default"){
                airportFile = airportIn;
                cout << "Enter name of routes dataset" << endl;
                string routesIn;
                cin >> routesIn;
                string routesFile = routesIn;
                Graph airportGraph(airportFile, routesFile);
                
                if(airportGraph.getVertices().size() == 0){
                    cout << "Empty graph constructed. Rewrite input again:" << endl;
                }else
                    validDataset = true;
            }
            else{
                validDataset = true;
                airportFile = "airports.dat";
                routesFile = "routes.dat";
            }
        }

        Graph airportGraph(airportFile, routesFile);
        unordered_map<int, Airport> verticesInGraph = airportGraph.getVertices();

        
        cout << "Enter a number to select an operation:" << endl;
        cout << "(0) Using BFS, traverse all of the graph from a given airport " << endl;
        cout << "(1) Using BFS, traverse a given number of moves of the graph from a given airport" << endl;
        cout << "(2) Using BFS, traverse the graph until a destination airport from a given airport" << endl;
        cout << "(3) Calculate the shortest path between two airports" << endl;
        cout << "(4) PageRank" << endl;

        int mode; 
        cin >> mode;
         
        bool validSource = false;

        switch (mode)
        {
            case 0:{
                validSource = false;
                while(validSource == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        validSource = true;
                        BFS myBFS(airportFile, routesFile);
                        vector<string> result_all = myBFS.traverseAllAirports(sourceAP);
                        string sourceAPName = it->second.getAirportName();
                        cout << "Printing out traversal from " << sourceAPName << ": " << endl;
                        for(unsigned i = 0; i < result_all.size(); i++){
                            cout << result_all[i] << " -> ";
                            if(i%4 == 0 && i != 0)
                                cout << "" << endl;
                        }
                        break;
                    }else{
                        cout << "Source airport ID not found in graph." << endl;
                    }
                }
                break;
            }


            case 1:{
                validSource = false;
                while(validSource == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        validSource = true;
                        cout << "Enter moves to traverse:" << endl;
                        int moves;
                        cin >> moves;
                        BFS myBFS(airportFile, routesFile);
                        vector<string> result_moves = myBFS.traverseAirportsWithMoves(sourceAP, moves);
                        string sourceAPName = it->second.getAirportName();
                        cout << "Printing out first " << moves << " moves from " << sourceAPName << ": " << endl;
                        for(unsigned i = 0; i < result_moves.size(); i++){
                            cout << result_moves[i];
                            if(i != result_moves.size()-1)
                                cout << " -> ";
                            if(i%4 == 0 && i != 0)
                                cout << "" <<endl;
                        }
                        break;
                    }else{
                        cout << "Source airport ID not found in graph." << endl;
                    }
                }
                break;
            }


            case 2:{
                bool validAP = false;
                while(validAP == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        string sourceAPName = it->second.getAirportName();
                        cout << "Enter a destination airport ID:" << endl;
                        int destAP; 
                        cin >> destAP;
                        auto it2 = verticesInGraph.find(destAP);
                        if(it2 != verticesInGraph.end()){
                            validAP = true;
                            BFS myBFS(airportFile, routesFile);
                            vector<string> result_dest = myBFS.traverseAirportsToDestination(sourceAP, destAP);
                            string destAPName = it2->second.getAirportName();
                            cout << "Printing out traversal from " << sourceAPName << " to " << destAPName<< ": " << endl;
                            for(unsigned i = 0; i < result_dest.size(); i++){
                                cout << result_dest[i];
                                if(i != result_dest.size()-1)
                                    cout<< " -> ";
                                if(i%4 == 0 && i != 0)
                                    cout << "" << endl;
                            }
                        }
                    }else{
                        cout << "Invalid airport input" << endl;
                    }
                } 
                break;
            }


            case 3:{
                string start; 

                cout << "Enter the name of source airport name, \nor enter 'default' to use 'Newark Liberty International Airport' as start and 'Gold Coast Airport' as end:\n";
                
                cin.ignore();
                getline(std::cin, start);

                if(start == "default"){
                    Djikstras shortestpath = Djikstras(airportGraph, "Newark Liberty International Airport", "Gold Coast Airport");
                    vector<string> path = shortestpath.getPathVert();
                    double distance = shortestpath.getShortDist();

                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if(i != path.size()-1)
                            cout<< " --> ";
                        if(i%4 == 0 && i != 0)
                            cout << "" << endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                } else {
                    cout << "Enter the end location:\n";
                    string end; 
                    getline(std::cin, end);
                    Djikstras shortestpath = Djikstras(airportGraph, start, end);
                    vector<string> path = shortestpath.getPathVert();
                    double distance = shortestpath.getShortDist();
                    if(distance == 0.0){
                        cout<< "One or more airport not found!"<<endl;
                        break;
                    }
                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if(i != path.size()-1)
                            cout<< " --> ";
                        if(i%4 == 0 && i != 0)
                            cout << "" << endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                }
                break;
            }

            case 4:{
                string airportFile = "airports.dat";
                string routesFile = "routes.dat";
                Graph airportGraph(airportFile, routesFile);
                unordered_map<int, Airport> airportMap = airportGraph.getVertices();
                if(true){
                    PageRank *test = new PageRank();                       // create page rank object
                    airportGraph.adjMatrix(test);                          // generate initial adjmatrix from graph
                    test->adjust(test->num, 0.85);                         // finalize adjmatrix
                    vector<double> initial = test->setup();                // generate initial vector 
                    vector<double> re = test->rank(initial, 100, false);   // perform pagerank alg, 100 iteration                        
                    cout << "\nenter the number of the most important airport to be printed: \n";
                    int top;
                    cin >> top; 
                    vector<int> id_rank = test->importance(top);           
                }
                break;
            }
        }
        cout << "" << endl;
        cout << "" << endl;
        cout << "Computation finished. Now restarting the program. "<< endl;
        cout << "" << endl;
    }
    return 0;
}
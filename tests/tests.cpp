#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>


#include "../Airport.h"
#include "../PageRank.h"
#include "../airport_graph.h"
#include "../Djikstras.h"
#include "../BFS.h"


#include "../catch/catch.hpp"


using namespace std;

TEST_CASE("Test Airport constructor with vector") { 
    // "3714","Washington Dulles International Airport","Washington","United States","IAD","KIAD",38.94449997,-77.45580292,312,-5,"A","America/New_York","airport","OurAirports"
    unordered_map<string, Airport> vertices;
    cout<<"Testing Airport::Airport(string &line) for [Washington Dulles International Airport]!: \n"<<endl;
    vector<string> airport_data = {"3714","Washington Dulles International Airport","Washington","United States", "", "", "38.94449997", "-77.45580292"};
    vertices["Washington Dulles International Airport"] = Airport(airport_data);
    int ID = vertices["Washington Dulles International Airport"].getAirportID();
    string Name = vertices["Washington Dulles International Airport"].getAirportName();
    string City = vertices["Washington Dulles International Airport"].getAirportCity();
    string Country = vertices["Washington Dulles International Airport"].getAirportCountry();
    int Latitude = (int)vertices["Washington Dulles International Airport"].getAirportLatitude();
    int Longitude = (int)vertices["Washington Dulles International Airport"].getAirportLongitude();

    REQUIRE(3714 == ID);
    REQUIRE("Washington Dulles International Airport" == Name);
    REQUIRE("Washington" == City);
    REQUIRE("United States" == Country);
    REQUIRE(38 == Latitude);
    REQUIRE(-77 == Longitude);
}

TEST_CASE("Test Pagerank with high priority airport") {
    cout << "\n\n > Testing Pagerank with high priority airport!: \n" << endl;
    PageRank *test = new PageRank();
    test->title.resize(5);
    test->result_.resize(5);

    test->title[0] = 0;
    test->title[1] = 1;
    test->title[2] = 2;
    test->title[3] = 3;
    test->title[4] = 4;

    test->result_[0] = 1.824;
    test->result_[1] = 256.78;
    test->result_[2] = 65.98;
    test->result_[3] = 89.12;
    test->result_[4] = 6;

    vector<int> rank = test->importance(3);
    REQUIRE(1 == rank[0]);
    REQUIRE(3 == rank[1]);
    REQUIRE(2 == rank[2]);
}

TEST_CASE("Test Pagerank rank functionality") { 
    cout << "\n\n > Testing Pagerank rank functionality!: \n" << endl;
    PageRank *test = new PageRank();
    int size = 8;
    test->matrix_.resize(size, vector<double>(size));
    test->title.resize(size);
    test->num = size;
    for (int i = 0; i < size; i++) {
        test->title[i] = i;
        for (int j = 0; j < size; j++) {
            test->matrix_[i][j] = 0.0;
        }
    }
    test->matrix_[0][2] = 15;
    test->PageRank::adjust(size, 0.80);
    vector<double> initial = test->PageRank::setup();
    vector<double> temp = test->PageRank::rank(initial, 40, true);
    vector<int> rank = test->importance(1);
    REQUIRE(0 == rank[0]);
}

// ICN 3930 ORD 3830 JFK 3797
TEST_CASE("Test graph build") {
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";
    Graph airportGraph(airportFile, routesFile);
    unordered_map<int, Airport> airportMap = airportGraph.getVertices();
    cout << "Airport Count: " << airportMap.size() <<endl;
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        if(it->first == 3930 || it->first == 3830 || it->first ==3797){
            cout << "Airport ID: " <<it->second.getAirportID() << " ";
            cout << "Airport Name: " <<it->second.getAirportName() << endl;
            unordered_map<int, Flight> adjList = it->second.destAPs;
            for(auto it = adjList.begin(); it != adjList.end(); ++it){
                cout << "First Airport ID: " << it->second.getSourceId() << " ";
                cout << "Dest Airport ID: " << it->second.getDestId() << " ";
                cout << "Weight: " << it->second.getWeight() << endl;
            }
        }
    }
    REQUIRE(0 <= airportMap.size());
}

// ICN 3930
TEST_CASE("Test airport traversals") {
    cout << "Testing airport traversals!: \n" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> movements = myBFS.traverseAirportsWithMoves(3930, 30);
    cout << "These are the first 30 movements with the origin ICN (Incheon, Republic of Korea)" << endl;
    for(unsigned i = 0; i < movements.size(); i++){
        cout << movements[i] ;
        if(i != movements.size() - 1)
            cout << " ===> ";
        if(i != 0 && i % 5 == 0)
            cout << endl;
    }
    cout << endl;
    REQUIRE("Incheon International Airport" == movements[0]);
    REQUIRE(31 == movements.size());
}

// ICN 3930 JFK 3797
TEST_CASE("Test airport traversals to destination") {
    cout << "Testing airport traversals to destination! [ICN to JFK]: \n" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> result_dest = myBFS.traverseAirportsToDestination(3930, 3797);
    cout << "Traversals [ICN to JFK]" << endl;
    for(unsigned i = 0; i < result_dest.size(); i++){
        cout << result_dest[i] ;
        if(i != result_dest.size() - 1)
            cout << " ===> ";
        if(i != 0 && i % 5 == 0)
            cout << endl;
    }
    cout << endl;
    REQUIRE("Incheon International Airport" == result_dest[0]);
}
// ICN 3930 JFK 3797
TEST_CASE("Test Djikstra via BFS [ICN to JFK]") { 
    cout << "Testing Djikstravia BFS!: \n" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";
    string StartingAirport;
    string DestinationAirport;
    Graph airportGraph(airportFile, routesFile);
    Djikstras shortestpath = Djikstras(airportGraph, "Incheon International Airport", "John F Kennedy International Airport");
    vector<string> path = shortestpath.getPathVert();
    double distance = shortestpath.getShortDist();
    cout<<"Visited Airports: \n"<<endl;
    for (unsigned long i = 0; i < path.size(); i++) {
        cout << path[i] ;
        if(i != path.size() - 1)
            cout << " ===> ";
        if(i != 0 && i % 5 == 0)
            cout << endl;
    }
    cout<<endl;
    cout<<"Total Distance: "<<distance<<endl;
    BFS myBFS(airportFile, routesFile);
    vector<string> result_dest = myBFS.traverseAirportsToDestination(3930, 3797);
    REQUIRE("Incheon International Airport" == path[0]);
    unsigned length = path.size();
    REQUIRE("John F Kennedy International Airport" == path[length - 1]);
    REQUIRE(result_dest.size() >= path.size());
}

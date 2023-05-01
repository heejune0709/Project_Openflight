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
//#include "../Landmark.h"

#include "../catch/catch.hpp"


using namespace std;



TEST_CASE("Testing Airport constructor with vector") { 

    //507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"

    unordered_map<string, Airport> vertices;
    cout<<"Testing vector constructor with London Heathrow airport"<<endl;
    vector<string> airport_data = {"507","London Heathrow Airport","London","United Kingdom", "", "", "51.4706", "-0.461941"};
    vertices["London Heathrow Airport"] = Airport(airport_data);
    int ID = vertices["London Heathrow Airport"].getAirportID();
    string Name = vertices["London Heathrow Airport"].getAirportName();
    string City = vertices["London Heathrow Airport"].getAirportCity();
    string Country = vertices["London Heathrow Airport"].getAirportCountry();
    int Latitude = (int)vertices["London Heathrow Airport"].getAirportLatitude();
    int Longitude = (int)vertices["London Heathrow Airport"].getAirportLongitude();

    REQUIRE(507 == ID);
    REQUIRE("London Heathrow Airport" == Name);
    REQUIRE("London" == City);
    REQUIRE("United Kingdom" == Country);
    REQUIRE(51 == Latitude);
    REQUIRE(0 == Longitude);


}


TEST_CASE("Testing Airport constructor with string") { 

    cout<<"Testing string constructor with goroka airport"<<endl;
    unordered_map<string, Airport> vertices;
    string goroka = "1,\"Goroka Airport\",\"Goroka\",\"Papua New Guinea\",\"GKA\",\"AYGA\",-6.081689834590001,145.391998291,5282,10,\"U\",\"Pacific/Port_Moresby\",\"airport\",\"OurAirports\"";
    vertices["Goroka Airport"] = Airport(goroka);
    int ID = (vertices["Goroka Airport"].getAirportID());
    string Name = (vertices["Goroka Airport"].getAirportName());
    string City = (vertices["Goroka Airport"].getAirportCity());
    string Country = (vertices["Goroka Airport"].getAirportCountry());
    int Latitude = (int)vertices["Goroka Airport"].getAirportLatitude();
    int Longitude = (int)vertices["Goroka Airport"].getAirportLongitude();
    
    REQUIRE(1 == ID);
    REQUIRE("Goroka Airport" == Name);
    REQUIRE("Goroka" == City);
    REQUIRE("Papua New Guinea" == Country);
    REQUIRE(-6 == Latitude);
    REQUIRE(145 == Longitude);
}

	
TEST_CASE("Testing Pagerank function top_airport()") { 
    cout << "\n\n\n\n >>>>>>>>Testing Pagerank function top_airport()\n" << endl;
    //construct a pagerank obj, manually setup the name_list and pr_result
    PageRank *test = new PageRank(); 
    test->title.resize(5);
    test->result_.resize(5);

    test->title[0] = 0;
    test->title[1] = 1;
    test->title[2] = 2;
    test->title[3] = 3;
    test->title[4] = 4;

    test->result_[0] = 0.245;
    test->result_[1] = 324.15;
    test->result_[2] = 23.21;
    test->result_[3] = 56.33;
    test->result_[4] = 4;

    //pick out the top 3 airport's id
    vector<int> rank = test->importance(3); 
    REQUIRE(1 == rank[0]);
    REQUIRE(3 == rank[1]);
    REQUIRE(2 == rank[2]);
}


TEST_CASE("Testing Pagerank function makeA()") {
    PageRank *test = new PageRank();

    int size = 2;
    test->matrix_.resize(size,vector<double>(size));

    //to test normalize(column sum == 1)
    test->matrix_[0][0] = 0.0;
    test->matrix_[1][0] = 0.0;

    //to test normalize and dampling factor
    test->matrix_[0][1] = 4.0;   
    test->matrix_[1][1] = 6.0;  

    test->title.resize(size);
    test->num = size;

    test->PageRank::adjust(size, 0.85);
    REQUIRE(0.5 == test->matrix_[0][0]);
    REQUIRE(0.5 == test->matrix_[1][0]);
    REQUIRE(1 == test->matrix_[0][1] + test->matrix_[1][1]);
}


TEST_CASE("Testing Pagerank function rank()") { 
    cout << "\n\n\n\n >>>>>>>>Testing Pagerank function rank()\n" << endl;
    PageRank *test = new PageRank();

    int size = 10;
    test->matrix_.resize(size,vector<double>(size));

    test->title.resize(size);
    test->num = size;

    //set only one edge from id:1 to id:0. Thus the id:0 should be the most important
    for(int i = 0; i < size; i++){
        test->title[i] = i;
        for(int j = 0; j < size; j++){
            test->matrix_[i][j] = 0.0;
        }        
    }
    test->matrix_[0][1] = 10;

    test->PageRank::adjust(size, 0.85);
    vector<double> initial = test->PageRank::setup();
    vector<double> temp = test->PageRank::rank(initial, 50, true);
    vector<int> rank = test->importance(1); 
    REQUIRE(0 == rank[0]);
}


TEST_CASE("Testing Pagerank implementation on a subset of the whole data set") { 
    //adjust the precision of the weight of edge to be shown
    cout << setprecision(10);
    cout << "\n\n\n\n >>>>>>>>Testing constructing graph from a subset of data and pagerank on the data set\n" << endl;
    string airportFile = "tests/airport_sample.dat";
    string routesFile = "tests/routes_sample.dat";
    Graph airportGraph(airportFile, routesFile);
    unordered_map<int, Airport> airportMap = airportGraph.getVertices();

    //printing out all flights departing from O'Hare, Newark and Beijing airport
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        cout << "Airport ID: " << it->first <<endl;
        if(it->first == 3830 || it->first == 3494 || it->first == 3364){
            cout << "Airport ID: " <<it->second.getAirportID() << " ";
            cout << "Airport Name: " <<it->second.getAirportName() << endl;

            unordered_map<int, Flight> adjList = it->second.destAPs;
            for(auto it = adjList.begin(); it != adjList.end(); ++it){
                cout << "Source ID: " << it->second.getSourceId() << " ";
                cout << "Destination ID: " << it->second.getDestId() << " ";
                cout << "Flight weight: " << it->second.getWeight() << endl;
            }
        }
    }
    cout << "\n";
    PageRank *test = new PageRank();                      //create pagerank obj
    airportGraph.adjMatrix(test);                         //generate initial adjmatrix from graph
    test->adjust(test->num, 0.85);                         //finalize adjmatrix
    test->print_adjmatrix();                              //print adj_m
    vector<double> initial = test->setup();      //generate initial vector 
    vector<double> re = test->rank(initial, 100, true);           //perform pagerank alg, 5 iteration
    test->print_result();                                 //print result
    vector<int> id_rank = test->importance(5);           //pickout the top 5 important airport

    REQUIRE(3364 == id_rank[0]);
    REQUIRE(3728 == id_rank[1]);
}


TEST_CASE("Testing constructing whole graph") {
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";
    Graph airportGraph(airportFile, routesFile);
    unordered_map<int, Airport> airportMap = airportGraph.getVertices();
    cout << "Number of airports: " << airportMap.size() <<endl;

    //printing out all flights departing from O'Hare, Newark and Beijing airport
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        //cout << "Airport ID: " << it->first <<endl;
        if(it->first == 3830 || it->first == 3494 || it->first ==3364){
            cout << "Airport ID: " <<it->second.getAirportID() << " ";
            cout << "Airport Name: " <<it->second.getAirportName() << endl;

            unordered_map<int, Flight> adjList = it->second.destAPs;
            for(auto it = adjList.begin(); it != adjList.end(); ++it){
                cout << "Source ID: " << it->second.getSourceId() << " ";
                cout << "Destination ID: " << it->second.getDestId() << " ";
                cout << "Flight weight: " << it->second.getWeight() << endl;
            }
        }
    }
    REQUIRE(7000 <= airportMap.size());
}


TEST_CASE("Testing traverse airports with moves") {
    
    cout << "testing traverse airports with moves" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> result_moves = myBFS.traverseAirportsWithMoves(3830, 50);
    cout << "Printing out first 50 moves from O'Hare airport" << endl;
    for(unsigned i = 0; i < result_moves.size(); i++){
        cout << result_moves[i] ;
        if(i != result_moves.size()-1)
            cout << " --> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout << endl;

    REQUIRE(51 == result_moves.size());
    REQUIRE("Chicago O'Hare International Airport" == result_moves[0]);
}

TEST_CASE("Testing traverse airports to destination") {
    cout << "testing traverse airports to destination" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> result_dest = myBFS.traverseAirportsToDestination(3830, 3494);
    cout << "Printing out traversal from O'Hare to Newark" << endl;
    for(unsigned i = 0; i < result_dest.size(); i++){
        cout << result_dest[i] ;
        if(i != result_dest.size()-1)
            cout << " --> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout << endl;

    
    REQUIRE("Chicago O'Hare International Airport" == result_dest[0]);
}



TEST_CASE("Testing Djikstra's algorithm with BFS") { 

    cout << "Testing Djikstra's algorithm with BFS" << endl;
    string airportFile = "airports.dat";
    string routesFile = "routes.dat";
    string StartingAirport;
    string DestinationAirport;
    Graph airportGraph(airportFile, routesFile);
    Djikstras shortestpath = Djikstras(airportGraph, "Chicago O'Hare International Airport", "Newark Liberty International Airport");

    vector<string> path = shortestpath.getPathVert();
    double distance = shortestpath.getShortDist();

    cout<<"Airports Visited: \n"<<endl;
    for (unsigned long i = 0; i < path.size(); i++) {
        cout << path[i] ;
        if(i != path.size()-1)
            cout << " —> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout<<endl;
    cout<<"Total Distance: "<<distance<<endl;

    BFS myBFS(airportFile, routesFile);
    vector<string> result_dest = myBFS.traverseAirportsToDestination(3830, 3494);

    REQUIRE("Chicago O'Hare International Airport" == path[0]);
    unsigned length = path.size();
    REQUIRE("Newark Liberty International Airport" == path[length-1]);
    REQUIRE(result_dest.size() >= path.size());

}



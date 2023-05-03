//Airport Class
#include "Airport.h"
#include <string>

using namespace std;

// Default constructor
Airport::Airport(){
    airport_id = 0;
    airport_name = "";
    airport_city = "";
    airport_country = "";
    airport_latitude = 0.0;
    airport_longitude = 0.0;
}


// Constructor with matching variables
Airport::Airport(int id, string name, string city, string country, double latitude, double longitude)
: airport_id(id), airport_name(name), airport_city(city), airport_country(country), airport_latitude(latitude), airport_longitude(longitude) {  }


// Constructor with a single line from airport.dat
Airport::Airport(string &line){
    // Build a vector of strings containing airport information separated by commas
    // Exclude quotation marks
    // If the input line lacks all 13 columns, call the default constructor
    bool quoteFlag = false;
    std::string currString = "";
    std::vector<std::string> airportVector;

    // Iterate through all characters in the line
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];

        // If a quotation mark hasn't occurred before
        if (!quoteFlag) {
            // When encountering a ",", push the current string to the vector and reset the current string
            if(current == ',') {
                airportVector.push_back(currString);
                currString = "";
            }
            // If the current char is a quotation mark, set the quote flag to true
            else if(current == '"') {
                quoteFlag = true;
            }
            //  If it's just a regular char, append it to the current string
            else {
                currString += current;
            }
        }
        
        // If there is a quotation mark from before
        else{
            // If we are at the second quotation mark
            if(current == '"' && i+1 < line.size()) {
                if(line[i+1] == '"') {
                    currString += '"';
                    i++;
                }
                // Don't add this quotation and turn off the flag
                else {
                    quoteFlag = false;
                }
            }
            // If just a regular char, append it to the current string
            else {
                currString += current;
            }
        }
    }
    
    // Update Private variables
    airport_id = stoi(airportVector[0], nullptr);
    airport_name = airportVector[1];
    airport_city = airportVector[2];
    airport_country = airportVector[3];
    airport_latitude = stod(airportVector[6], nullptr);
    airport_longitude = stod(airportVector[7], nullptr);
}


// Vector constructor
Airport::Airport(vector<string> airportVector){
    airport_id = stoi(airportVector[0], nullptr);
    airport_name = airportVector[1];
    airport_city = airportVector[2];
    airport_country = airportVector[3];
    // Latitude and longitude must be vector[6] and vector[7]
    airport_latitude = stod(airportVector[6], nullptr);
    airport_longitude = stod(airportVector[7], nullptr);
}


// Getters: 
int Airport::getAirportID() {
    return airport_id;
}
string Airport::getAirportName() {
    return airport_name;
}
string Airport::getAirportCity() {
    return airport_city;
}
string Airport::getAirportCountry() {
    return airport_country;
}
double Airport::getAirportLatitude() {
    return airport_latitude;
}
double Airport::getAirportLongitude() {
    return airport_longitude;
}
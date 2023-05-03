#include "Flight.h"
#include <limits.h>

// Default constructor
Flight::Flight(){
    sourceAP = -1;
    destinationAP = -1; 
    weight = INT_MAX;
};


// Constructor without given weight(infinity)
Flight::Flight(int s, int d){
    sourceAP = s;
    destinationAP = d; 
    weight = INT_MAX;
};

// Constructor with all private variables
Flight::Flight(int s, int d, double w){
    sourceAP = s;
    destinationAP = d; 
    weight = w;
};

// Getters
int Flight::getSourceId() {
    return sourceAP;
}
int Flight::getDestId() {
    return destinationAP;
}
double Flight::getWeight() {
    return weight;
}

// Setters
void Flight::setWeight(double w) {
    weight = w;
}
void Flight::setSource(double s) {
    sourceAP = s;
}
void Flight::setDestination(double d) {
    destinationAP = d; 
}

// If the weight comparison holds, returns true
bool Flight::operator<(const Flight& other) const {
    return weight < other.weight;
}

// If two flights are from and to the same airports, return true
bool Flight::operator==(Flight& other) const {
    if (sourceAP != other.sourceAP)
        return false;
    if (destinationAP != other.destinationAP)
        return false;
    return true;
}
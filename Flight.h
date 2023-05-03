#pragma once

class Flight {
    public:
        // Constructors
        Flight();
        Flight(int s, int d);
        Flight(int s, int d, double w);

        //getters
        int getSourceId();       
        int getDestId();         
        double getWeight();
       
        //setters
        void setWeight(double w);
        void setSource(double s);
        void setDestination(double d); 

        //operator overloading
        bool operator<(const Flight& other) const;
        bool operator==(Flight& other) const;
    
    private:
        int sourceAP;
        int destinationAP;
        double weight;
};
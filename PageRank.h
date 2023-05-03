#pragma once

#include <algorithm>
#include <vector>
using namespace std;


//pagerank class
class PageRank
{
  public:
    //adjust adj matrix
    void adjust(int num, double value);

    //perform pagerank
    vector<double> rank(vector<double> initial, int time, bool normalize);

    //pick out the most important airport
    vector<int> importance(int num);

    //generate starting vector for pagerank
    vector<double> setup();

    //the adj matrix variable, for pagerank
    vector<vector<double>> matrix_; 

    //the namelist of the airport. contains the airport id
    vector<int> title; 

    //the pagerank result
    vector<double> result_; 

    //dimension of the adj matrix, namelist, initial vector and result vector
    int num;

    //print adjmatrix
    void print_adjmatrix();

    //print the result vector
    void print_result();
};
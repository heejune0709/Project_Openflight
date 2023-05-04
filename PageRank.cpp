#include "PageRank.h"
#include <numeric>
#include <iostream>

void PageRank::adjust(int num, double value) {
    //set the current object's "num" value to the given "num"
    this->num = num;

    //for each column of the adjacency matrix
    for(int i = 0; i < num; i++){
        double temp = 0;

        //sum all the elements in the column
        for(int j = 0; j < num; j++){
            temp += matrix_[j][i];
        }     

        //if the sum is zero, set each element in the column to a uniform probability
        if(temp == 0){
            for(int k = 0; k < num; k++){
                matrix_[k][i] = 1/(double)num;
            }              
        } else {
            //else, adjust each element in the column based on the sum of the column
            for(int a = 0; a < num; a++){
                matrix_[a][i] = (matrix_[a][i] / temp) * value + (1 - value) / num;
            }             
        }
    }
}

vector<double> PageRank::rank(vector<double> initial, int time, bool normalize) {
    //create two vectors to hold the intermediate results
    vector<double> temp = initial;
    vector<double> newtemp = initial;

    //iterate "time" number of times
    for(int t = 0; t < time; t++){
        //for each element in the vector
        for(int i = 0; i < num; i++){
            //initialize the value of the new vector element to 0
            newtemp[i] = 0;

            //calculate the dot product of the adjacency matrix row and the vector
            for(int j = 0; j < num; j++){
                newtemp[i] += matrix_[i][j] * temp[j];

                //if "normalize" flag is set to true, perform normalization on the vector
                if(normalize) {
                    double sum = 0;
                    //calculate the norm-2 of the vector
                    for(std::vector<double>::iterator it = newtemp.begin(); it != newtemp.end(); ++it)
                        sum += (*it)*(*it);
                    double normalize = sqrt(sum);

                    //normalize the vector by dividing each element by its norm
                    for(int n = 0; n < num; n++){
                        newtemp[n] = newtemp[n] / normalize;
                    }
                }
            }     
        }
        //update the "temp" vector with the new values
        temp = newtemp;
    }

    //store the final result in the "result_" member variable and return it
    result_ = temp;
    return temp;
}


// Compute the importance of the top 'num' airports based on their PageRank score
vector<int> PageRank::importance(int num) {
    vector<int> airport(num);
    vector<double> check(num);
    int position = 0;
    // Find the index of the top 'num' important airports in the pagerank result vector
    for(int i = 0; i < num; i++) {
        double max = 0;
        for(auto it : result_) {
            if(it > max) {
                bool flag = true;
                // Check if the current airport is already on the list of important airports
                if(std::find(check.begin(), check.end(), it) != check.end()) {
                    flag = false;
                }
                if(flag) {
                    max = it;
                }
            }
        }
        check[position] = max;
        position++;
    }
    position = 0;
    // Use the index and the airport names list to find out the related airport IDs
    for(int i = 0; i < num; i++) {
        int count = 0;
        for(auto it : result_) {
            if(check[i] == it) {
                airport[position] = title[count];
                position++;
            }
            count++;
        }
    }
    // Print the IDs of the top 'num' important airports
    std::cout << "Top " << num << " important airports:\n";
    for(int i = 0; i < num; i++) {
        std::cout << airport[i] << "\n";
    }
    return airport;
}

// Initialize the PageRank algorithm with a random initial vector
vector<double> PageRank::setup(){
    vector<double> initial;
    initial.resize(this->num);
    for(int i = 0; i < this->num; i++){
        initial[i] = rand();
    }
    return initial;
}

// Print the adjacency matrix of the graph
void PageRank::print_adjmatrix(){
    cout<<"Adjacency matrix:"<<endl;
    cout<<"      ";
    for(int i = 0; i < this->num; i++){
        cout<<this->title[i];
        cout<<"           ";
    }
    cout<<"\n";
    for(int i = 0; i < this->num; i++){
        cout<<this->title[i];
        cout<<"  ";
        for(int j = 0; j < this->num; j++){
            cout<<this->matrix_[i][j];
            cout<<"  ";
        } 
        cout<<"\n";
    }
    cout<<"\n";
}

// Print the PageRank scores of the airports
void PageRank::print_result(){
    cout<<"PageRank scores:\n"; 
    cout<<" Airport ID      Score\n"; 
    for(int i = 0; i < this->num; i++){
        cout<<this->title[i];
        cout<<" ";
        cout<<this->result_[i];
        cout<<"\n";
    }
    cout<<"\n";
}

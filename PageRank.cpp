#include "PageRank.h"
#include <numeric>
#include <iostream>

void PageRank::adjust(int num, double value) {
    this->num = num;
    for(int i = 0; i < num; i++){
        double temp = 0;
        for(int j = 0; j < num; j++){
            temp += matrix_[j][i];
        }     
        if(temp == 0){
            for(int k = 0; k < num; k++){
                matrix_[k][i] = 1/(double)num;
            }              
        } else {
            for(int a = 0; a < num; a++){
                matrix_[a][i] = (matrix_[a][i] / temp) * value + (1 - value) / num;
            }             
        }
    }
}

vector<double> PageRank::rank(vector<double> initial, int time, bool normalize) {
    //vectors which stores the intermediate result
    vector<double> temp = initial;
    vector<double> newtemp = initial;
    for(int t = 0; t < time; t++){
        for(int i = 0; i < num; i++){
            //initialize the vector
            newtemp[i] = 0;
            //calculate product of adjmatrix and vector 
            for(int j = 0; j < num; j++){
                newtemp[i] += matrix_[i][j] * temp[j];

                if(normalize) {
                    double sum = 0;
                    //perform norm 2 normalize
                    for(std::vector<double>::iterator it = newtemp.begin(); it != newtemp.end(); ++it)
                        sum += (*it)*(*it);
                    double normalize = sqrt(sum);

                    for(int n = 0; n < num; n++){
                        newtemp[n] = newtemp[n] / normalize;
                    }
                }
            }     
        }
        temp = newtemp;
    }
    //store result in the pagerank obj
    result_ = temp;
    return temp;
}
vector<int> PageRank::importance(int num) {
    vector<int> airport(num);
    vector<double> check(num);
    int position = 0;
    // find the index of the important airport in the pagerank result vector
    for(int i = 0; i < num; i++) {
        double max = 0;
        for(auto it : result_) {
            if(it > max) {
                bool flag = true;
                // check if the current airport is already on the list of the important airport
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
    // using the index and the name_list to find out the related airport id
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
    // print the id
    std::cout << "top " << num << " important airport\n";
    for(int i = 0; i < num; i++) {
        std::cout << airport[i] << "\n";
    }
    return airport;
}
vector<double> PageRank::setup(){
    vector<double> initial;
    initial.resize(this->num);
    for(int i = 0; i < this->num; i++){
        initial[i] = rand();
    }
    return initial;
}
void PageRank::print_adjmatrix(){
    cout<<"adj matrix"<<endl;
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


void PageRank::print_result(){
    cout<<"page rank result\n"; 
    cout<<" ID      value\n"; 
    for(int i = 0; i < this->num; i++){
        cout<<this->title[i];
        cout<<" ";
        cout<<this->result_[i];
        cout<<"\n";
    }
    cout<<"\n";
}
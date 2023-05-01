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
    vector<double> check(initial);
    vector<double> check2(initial.size());
    for(int t = 0; t < time; t++) {
        std::transform(matrix_.begin(), matrix_.end(), check.begin(), check2.begin(),
            [](const auto& row, const auto& col) {
                double sum = 0;
                std::transform(row.begin(), row.end(), col.begin(), sum,
                    [](const auto& a, const auto& b) { return a * b; });
                return sum;
            });

        if (normalize) {
            double sum = std::accumulate(check2.begin(), check2.end(), 0.0,
                [](const auto& a, const auto& b) { return a + b * b; });
            double normalize_factor = sqrt(sum);
            std::transform(check2.begin(), check2.end(), check2.begin(),
                [normalize_factor](const auto& x) { return x / normalize_factor; });
        }
        check = check2;
    }
    result_ = check;
    return check;
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
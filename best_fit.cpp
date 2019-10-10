//
// Created by Chenlin on 5/18/2019.
//
#include "bin_packing.h"
int tight(std::vector<double> free,double item){
    int bin = 0;
    int result = 0;
    if(free.size() > 0) {
        double tigst_free = 1;
        for (int i = 0; i < free.size(); i++) {
            if (free[i] >= item) {
                double temp = free[i] - item;
                //std::cout<<temp<<std::endl;
                if(temp < tigst_free && temp >= 0){
                    bin = i;
                    tigst_free = temp;
                    result++;
                }
            }
        }
    }
    if(result == 0){
        bin = -1;
    }
    return bin;
}
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    int bin =0;
    for(int i = 0; i< items.size(); i++){
        int new_bin = 0;
        int bin = tight(free_space,items[i]);
        if(bin == -1){
            free_space.push_back(1-items[i]);
            assignment[i] = free_space.size()-1;
        }
        else{
            free_space[bin] -= items[i];
            assignment[i] = bin;
        }
    }
}
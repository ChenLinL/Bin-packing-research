//
// Created by Chenlin on 5/8/2019.
//
#include "bin_packing.h"
//typedef std::vector<item_t> bin_t;

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    double bin = 0;
    int bin_num = 0;
    int i = 0;
    int end = 0;
    for(i = 0; i<items.size(); i++ ){
        if(bin+items[i]<=1){
            bin+=items[i];
            assignment[i] = bin_num;
            end = i;
        }
        else{
            double waste = 1-bin;
            free_space.push_back(waste);
            bin = items[i];
            bin_num++;
            assignment[i] = bin_num;
        }
    }
    if(end == items.size()-1){
        double waste = 1-bin;
        free_space.push_back(waste);
    }
//    if(bin!=0){
//        double waste = 1-bin;
//        free_space.push_back(waste);
//        bin_num++;
//        assignment[i] = bin_num;
//    }
}


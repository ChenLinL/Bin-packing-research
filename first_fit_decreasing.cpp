//
// Created by Chenlin on 5/18/2019.
//
#include "bin_packing.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
bool greater(double i, double j) {return (i>j);}
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    std::map<double,int> map;
    std::vector<double> temp = items;
    for(int i = 0; i<temp.size();i++){
        map[temp[i]] = i;
    }
    std::sort(temp.begin(),temp.end(),greater);

    for(int i = 0; i< temp.size(); i++){
        int new_bin = 0;
        for(int j = 0; j<free_space.size(); j++){
            if(temp[i] <= free_space[j]){
                //std::cout<<"free: "<<free_space[j]<<std::endl;
                free_space[j] = fabs(free_space[j]-temp[i]);
                //std::cout<<"after free: "<<free_space[j]<<std::endl;
                //std::cout<<"item: "<<items[i]<<std::endl;
                int pos = map[temp[i]];
                assignment[pos] = j;
                new_bin = 1;
                break;
            }
        }
        if(new_bin != 1){
            //std::cout<<i<<std::endl;
            free_space.push_back(1-temp[i]);
            //std::cout<<free_space[0]<<std::endl;
            int pos = map[temp[i]];
            assignment[pos] = free_space.size()-1;
        }
    }
}

//
// Created by Chenlin on 5/19/2019.
//
#include "bin_packing.h"
#include <map>
#include <algorithm>
#include <cmath>
bool greater1(double i, double j) {return (i>j);}
int tight1(std::vector<double> free,double item){
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
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    std::map<double,int> map;
    std::vector<double> temp = items;
    for(int i = 0; i<temp.size();i++){
        map[temp[i]] = i;
    }
    std::sort(temp.begin(),temp.end(),greater1);
    int bin =0;
    for(int i = 0; i< temp.size(); i++){
        int new_bin = 0;
        int bin = tight1(free_space,temp[i]);
        if(bin == -1){
            free_space.push_back(1-temp[i]);
            assignment[map[temp[i]]] = free_space.size()-1;
        }
        else{
            free_space[bin] -= temp[i];
            assignment[map[temp[i]]] = bin;
        }
    }
}

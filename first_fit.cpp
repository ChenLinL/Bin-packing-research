#include "bin_packing.h"



void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    std::vector<double> temp = items;
    int bin =0;
    for(int i = 0; i< temp.size(); i++){
        int new_bin = 0;
        for(int j = 0; j<free_space.size(); j++){
            if(items[i] <= free_space[j]){
                //std::cout<<"free: "<<free_space[j]<<std::endl;
                free_space[j] = free_space[j]-items[i];
                //std::cout<<"after free: "<<free_space[j]<<std::endl;
                //std::cout<<"item: "<<items[i]<<std::endl;
                assignment[i] = j;
                new_bin = 1;
                break;
            }
        }
        if(new_bin != 1){
            //std::cout<<i<<std::endl;
            free_space.push_back(1-items[i]);
            //std::cout<<free_space[0]<<std::endl;
            assignment[i] = free_space.size()-1;
        }
    }
}
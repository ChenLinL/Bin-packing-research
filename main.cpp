#include <iostream>
#include "next_fit.cpp"
#include "first_fit.cpp"
#include "best_fit.cpp"
#include "first_fit_decreasing.cpp"
#include "best_fit_decreasing.cpp"
#include <fstream>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>
#include <math.h>
using namespace std;
struct timing{
    int n;
    double seconds;
};
void create_empty_file(string filename){
    ofstream f;
    f.open(filename, ios::trunc);
    f << "test_size,waste\n";
    f.close();
}
void add_test_to_file(int testCase, double waste, string filename){
    ofstream f;
    f.open(filename,ios::app);
    f<< testCase <<","<<waste<<"\n";
    f.close();
}


mt19937 get_mersenne_twister_genreator_with_current_time_seed(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
uniform_int_distribution<int> get_uniform_int_generator(int lb, int ub){
    return uniform_int_distribution<int>(lb,ub);
}
uniform_real_distribution<double> get_uniform_double_generator(){
    return uniform_real_distribution<double>(0.0,1.0);
}
int randint(mt19937 mt, int lb, int ub){
    return uniform_int_distribution<int>(lb,ub)(mt);
}
double randdouble(mt19937 mt){
    return uniform_real_distribution<double>(0.0,1.0)(mt);
}
void shuffle_vector(vector<double>& nums){
    for(int i = nums.size(); i >= 0; i--){
        mt19937 mt = get_mersenne_twister_genreator_with_current_time_seed();
        int j = randint(mt,0,i);
        double temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
std::vector<double> create_vector(int n){
    vector<double> nums;
    for(int i = 0; i<n; i++){
        mt19937 mt = get_mersenne_twister_genreator_with_current_time_seed();
        double d = randdouble(mt);
        nums.push_back(d);
    }
    shuffle_vector(nums);
    return nums;
}

double sum(std::vector<double> nums){
    double total = 0.0;
    for(double & n: nums){
        total += n;
    }
    return total;
}

int bins_num (std::vector<int> nums){
    int max = nums[0];
    for(int & n:nums){
        if(n > max){
            max = n;
        }
    }
    max += 1;
    return max;
}
int main() {
//    std::cout << "best_fit" << std::endl;
//    //std::cout << "Hello, World!" << std::endl;
//    std::vector<double> items = {0.12,0.83,0.61,0.42,0.71,0.21,0.53,0.72,0.99,0.81,0.25,0.57,0.32,0.76,0.11};
//    std::cout<<"items:       ";
//    for(int i = 0; i<items.size();i++){
//        std::cout<<i<<": "<<items[i]<<" | ";
//    }
//    std::cout<<std::endl;
//    //std::cout<<items.at(0.13)<<std::endl;
//    std::vector<int> nums = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//    std::vector<double> free;
//    next_fit(items,nums,free);
//    //first_fit(items,nums,free);
//    //best_fit(items,nums,free);
//    //first_fit_decreasing(items,nums,free);
//    //best_fit_decreasing(items,nums,free);
//    std::cout<<"bins remain: ";
//    for(int i = 0; i<free.size(); ++i){
//        std::cout<<i<<": "<<free[i]<<" | ";
//    }
//    std::cout<<std::endl;
//    std::cout<<"assigments:  ";
//    for(int i = 0; i<nums.size(); ++i){
//        std::cout<<i<<": "<<nums[i]<<" | ";
//    }
//    std::cout<<std::endl;
    create_empty_file("next_fit.csv");
    create_empty_file("first_fit.csv");
    create_empty_file("best_fit.csv");
    create_empty_file("first_fit_decreasing.csv");
    create_empty_file("best_fit_decreasing.csv");
    for(int n = 2; n <= 524288; n *= 2){
        std::vector<double> nums = create_vector(n);
        //the test case for the next fit.
        vector<double> next_nums = nums;
        vector<int> next_assigment(n,0);
        vector<double> next_free;
        next_fit(next_nums,next_assigment,next_free);
        double next_waste = bins_num(next_assigment) - sum(next_nums);
        //cout<<"wast: "<<next_waste<<endl;
        add_test_to_file(n,next_waste,"next_fit.csv");
        //--------------------------------------------------------------------//

        //the test case for the first fit.
        vector<double> first_nums = nums;
        vector<int> first_assigment(n,0);
        vector<double> first_free;
        first_fit(first_nums,first_assigment,first_free);
        double first_waste = bins_num(first_assigment) - sum(first_nums);
        //cout<<"wast: "<<first_waste<<endl;
        add_test_to_file(n,first_waste,"first_fit.csv");
        //------------------------------------------------------------------------//

        //the test case fot the best fit.
        vector<double> best_nums = nums;
        vector<int> best_assigment(n,0);
        vector<double> best_free;
        best_fit(best_nums,best_assigment,best_free);
        double best_waste = bins_num(best_assigment) - sum(best_nums);

        add_test_to_file(n,best_waste,"best_fit.csv");
        //-------------------------------------------------------------------------//

        //the test case for the first_fit_decreasing.
        vector<double> first_d_nums = nums;
        vector<int> first_d_assigment(n,0);
        vector<double> first_d_free;
        first_fit_decreasing(first_d_nums,first_d_assigment,first_d_free);
        double first_d_waste = bins_num(first_d_assigment) - sum(first_d_nums);

        add_test_to_file(n,first_d_waste,"first_fit_decreasing.csv");
        //----------------------------------------------------------------------------//

        //the test case for the best_fit_decreasing.
        vector<double> best_d_nums = nums;
        vector<int> best_d_assigment(n,0);
        vector<double> best_d_free;
        best_fit_decreasing(best_d_nums,best_d_assigment,best_d_free);
        double best_d_waste = bins_num(best_d_assigment) - sum(best_d_nums);
        //cout<<"wast: "<<best_d_waste<<endl;
        add_test_to_file(n,best_d_waste,"best_fit_decreasing.csv");
        //-----------------------------------------------------------------------------//
        //std::cout<<"l"<<endl;

    }

    return 0;
}

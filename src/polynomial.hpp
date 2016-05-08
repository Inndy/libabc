#ifndef polynomial_hpp
#define polynomial_hpp
#include "util.hpp"
#include "queue.hpp"
#include <cmath>
#include <sstream>
class Polynomial
{
private:
    int * coefficient;
    int size;
    //the min bound and max bound of the interval inwhich we find root
    double root_interval_min;
    double root_interval_max;
    double step_size = 0.001;
public:
    Polynomial(int size){
        this->size = size;
        coefficient = new int[this->size];
        root_interval_min = -100.0;
        root_interval_max = 100.0;
    }
    ~Polynomial(){
        delete coefficient;
    }
    //accessor
    int& operator[](int index){
        if(index >= this->size)
            fatal("Polynominal: accessor index overflow");
        return coefficient[index];
    }
    int& cell(int index){
        if(index >= this->size)
            fatal("Polynominal: accessor index overflow");
        return coefficient[index];
    }
    //get the value of current polynomial
    double operator()(double independent_variable){
        double result = 0;
        for (int currentPow = 0; currentPow < size; currentPow++){
            result += coefficient[currentPow]*pow(independent_variable,currentPow);
        }
        return result;
    }
    double val(double independent_variable){
        return (*this)(independent_variable);
    }
    //set and get method for the interval of root finding
    void get_interval(int& lower_bound, int& upper_bound){
        lower_bound = root_interval_min;
        upper_bound = root_interval_max;
    }
    void set_interval(int lower_bound, int upper_bound){
        this->root_interval_min = lower_bound;
        this->root_interval_max = upper_bound;
    }
    //set and get method for step size for finding root
    void get_step_size(int& step_size){
        step_size = this->step_size;
    }
    void set_step_size(int step_size){
        this->step_size = step_size;
    }
    //method for finding root
    //brute force method for finding root
    double * root_finding(int & root_count){
        root_count = 0;
        Queue<double> queue;
        for (double var = root_interval_min; var <= root_interval_max; var += step_size) {
            if(approximately_equals(this->val(var),0.0))
            {
                queue.enQueue(var);
                root_count++;
            }
        }
        double * result = new double[root_count];
        for (int index = 0; index < root_count; index++) {
            result[index] = queue.deQueue();
        }
        return result;
    }

    string str(){
        stringstream buffer;
        buffer << "Polynomial: " << this->size << endl;
        for (int currentPow = this->size-1; currentPow >=0; currentPow --) {
            if (currentPow >=1) {
                buffer << coefficient[currentPow] << "*x^" << currentPow;
                buffer << " + ";
            }else if(currentPow == 0){
                buffer << coefficient[currentPow];
            }
        }
        buffer << endl;
        return buffer.str();
    }
};

#endif
#include "calculator.h"

Calculator::Calculator() {}

double Calculator::sum(double a, double b){
    return a+b;
}

double Calculator::dif(double a, double b){
    return a-b;
}

double Calculator::mul(double a, double b){
    return a*b;
}

double Calculator::div(double a, double b){
    return a/b;
}

Calculator::~Calculator() {}

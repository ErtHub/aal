#pragma once
#include <random>
#include <vector>
#include <iostream>

class PIGenerator
{
    private:
    int sensitivity, multiplier;

    public:
    PIGenerator() : sensitivity(1), multiplier(1) {};
    PIGenerator(int sensitivity_, int multiplier_=1) : sensitivity(sensitivity_), multiplier(multiplier_) {};
    int calcDestiny(std::vector<int> past);
    std::vector<int> generatePI(bool solution, int length);
};

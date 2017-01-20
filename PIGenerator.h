#ifndef PIGENERATOR_H
#define PIGENERATOR_H

#include <random>
#include <vector>
#include <iostream>
#include <climits>

typedef enum AlgSearchingDirection_
{
    lesser_to_greater = 1,
    greater_to_lesser = 2
} AlgSearchingDirection;

class PIGenerator
{
    private:
    int distribution_broadness, multiplier;

    int calcDestiny(std::vector<int>& past);

    public:
    PIGenerator() : distribution_broadness(1), multiplier(1) {};
    PIGenerator(int distribution_broadness_, int multiplier_=1) : distribution_broadness(distribution_broadness_), multiplier(multiplier_) {};
    std::vector<int> generatePI(bool solution, int length);
    std::vector<int> createExtremeCase(int length, AlgSearchingDirection direction);
};

#endif

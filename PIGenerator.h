#ifndef PIGENERATOR_H
#define PIGENERATOR_H

#include <random>
#include <vector>
#include <iostream>
#include <climits>

class PIGenerator
{
    typedef enum AlgSearchingDirection_
    {
        lesser_to_greater = 1,
        greater_to_lesser = 2
    } AlgSearchingDirection;

    private:
    int sensitivity, multiplier;

    int calcDestiny(std::vector<int> past);

    public:
    PIGenerator() : sensitivity(1), multiplier(1) {};
    PIGenerator(int sensitivity_, int multiplier_=1) : sensitivity(sensitivity_), multiplier(multiplier_) {};
    std::vector<int> generatePI(bool solution, int length);
    std::vector<int> createExtremeCase(int length, AlgSearchingDirection direction);
};

#endif

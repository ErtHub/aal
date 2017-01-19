#ifndef TIMERSOLVER_H
#define TIMERSOLVER_H

#include "Solver.h"
#include <utility>
#include <chrono>
#include <iostream>
#include <list>

 class TimerSolver : public Solver
 {
    private:
    std::list<double> timeRecords;

    public:
    TimerSolver() = delete;
    TimerSolver(bool (*a)(std::vector<int>&));
    virtual ~TimerSolver() {};
    virtual bool solve(std::vector<int>& arg);
    virtual std::list<double> extractTimeRecords();
 };

#endif

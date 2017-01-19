#include "TimerSolver.h"

using namespace std;
using namespace std::chrono;

TimerSolver::TimerSolver(bool (*a)(std::vector<int>&)) : Solver(a) {}

bool TimerSolver::solve(vector<int>& arg)
{
    bool to_return;
    high_resolution_clock::time_point executionStart = high_resolution_clock::now();
    to_return = Solver::solve(arg);
    high_resolution_clock::time_point executionEnd = high_resolution_clock::now();

    duration<double, ratio<1, 1000>> executionTime = executionEnd - executionStart;
    timeRecords.push_back(executionTime.count());
    return to_return;
}

list<double> TimerSolver::extractTimeRecords()
{
    list<double> to_return = timeRecords;
    timeRecords.clear();
    return to_return;
}

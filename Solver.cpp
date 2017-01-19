#include "Solver.h"

using namespace std;

Solver::Solver(bool (*a)(vector<int>&)): alg(a) {}

bool Solver::solve(vector<int>& arg)
{
    return (*alg)(arg);
}

void Solver::setAlg(bool (*a)(vector<int>&))
{
    this->alg=a;
}

list<double> Solver::extractTimeRecords() {}

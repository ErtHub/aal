#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <list>

class Solver
{
    private:
    bool (*alg)(std::vector<int>&);

    public:
    Solver() = delete;
    Solver(bool (*a)(std::vector<int>&));
    virtual ~Solver() {};
    virtual bool solve(std::vector<int>& arg);
    virtual std::list<double> extractTimeRecords();
    void setAlg(bool (*a)(std::vector<int>&));
};

#endif

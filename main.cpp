#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <map>
#include "Solver.h"
#include "TimerSolver.h"
#include "ArgGetter.h"
#include "algorithms.hpp"

#define INVALID_PARAM -1

using namespace std;

namespace
{
    const int TABLE_WIDTH = 20;

    void printTable(ostream& os, map<int, double>& data, long double c_factor, char algKey)
    {
        os << setw(TABLE_WIDTH) << setfill(' ') << "n" << setw(TABLE_WIDTH) << setfill(' ') << "t(n)[ms]" << setw(TABLE_WIDTH) << setfill(' ') << "q(n)" << endl;
        for(auto i = data.begin(); i!=data.end(); ++i)
        {
            os << setw(TABLE_WIDTH) << setfill(' ');
            os << i->first;
            os << setw(TABLE_WIDTH) << setfill(' ');
            os << i->second;
            os << setw(TABLE_WIDTH) << setfill(' ');
            os << i->second/(c_factor*((AlgHolder::asymptotics[algKey])(i->first)));
            os << endl;
        }
    }

    map<int, double> calcMeanTimes(list<vector<int>>& problems, list<double>& solveTimes)
    {
        map<int, double> to_return;
        map<int, int> counts;
        auto problemsItr = problems.begin();
        auto timesItr = solveTimes.begin();
        while(problemsItr!=problems.end() && timesItr!=solveTimes.end())
        {
            if(to_return.find(problemsItr->size())==to_return.end())
            {
                to_return[problemsItr->size()]=(*timesItr);
                counts[problemsItr->size()]=1;
            }
            else
                to_return[problemsItr->size()]+=(*timesItr);
                ++counts[problemsItr->size()];
            ++problemsItr;
            ++timesItr;
        }
        auto retItr=to_return.begin();
        auto countsItr=counts.begin();
        while(retItr!=to_return.end() && countsItr!=counts.end())
        {
            retItr->second/=countsItr->second;
            ++retItr;
            ++countsItr;
        }
        return to_return;
    }

    map<int, double> calcMaxTimes(list<vector<int>>& problems, list<double>& solveTimes)
    {
        map<int, double> to_return;
        auto problemsItr = problems.begin();
        auto timesItr = solveTimes.begin();
        while(problemsItr!=problems.end() && timesItr!=solveTimes.end())
        {
            if(to_return.find(problemsItr->size())==to_return.end() || to_return[problemsItr->size()]<(*timesItr))
                to_return[problemsItr->size()]=(*timesItr);
            ++problemsItr;
            ++timesItr;
        }
        return to_return;
    }

    int findMed(int ending, int beginning, int step)
    {
        int distanceScaledByStep = (ending - beginning)/step;
        return beginning + (distanceScaledByStep / 2) * step;
    }
}

int main(int argc, char* argv[])
{
    vector<int> pigArg = {100, 1, 1, 1};
    list<vector<int>> inputs;
    Solver *solver;
    list<bool> answers;
    list<bool> shouldBes;
    list<double> timeMeasurements;
    bool timerIsOn = false;
    bool pigIsOn = false;
    bool casesAreExtreme = false;
    char algKey = 'D';

    for (int i=1; i<argc; ++i)
    {
        if(string(argv[i])=="-t" || string(argv[i])=="--timer")
            timerIsOn = true;
        else if(string(argv[i])=="-g" || string(argv[i])=="--generate-args" || string(argv[i])=="-gX" || string(argv[i])=="--generate-extreme")
        {
            pigIsOn = true;
            if(string(argv[i])=="-gX" || string(argv[i])=="--generate-extreme")
                casesAreExtreme = true;
            int j = 0;
            int to_put = 0;
            for(; j<(casesAreExtreme ? 3 : 4) && i+1+j<argc; ++j)
            {
                if((to_put=atoi(argv[i+1+j]))==0)
                    break;
                pigArg[j]=to_put;
            }
            i+=j;
            if(pigArg[0]<pigArg[1])
            {
                cout << "Error: Problem Instance Generation arguments are inconsistent." << endl;
                return INVALID_PARAM;
            }
        }
        else if(argv[i][0]=='-' && argv[i][1]=='a')
            algKey=argv[i][2];
        else
        {
            cout << "Unknown argument \"" << argv[i] << "\"" << endl;
            return INVALID_PARAM;
        }

    }

    auto algItr = AlgHolder::algs.find(algKey);
    if(algItr==AlgHolder::algs.end())
    {
        cout << "Unknown algorithm \"" << algKey << "\"." << endl;
        return INVALID_PARAM;
    }

    if(timerIsOn)
        solver = new TimerSolver(algItr->second);
    else
        solver = new Solver(algItr->second);

    if(pigIsOn && !casesAreExtreme)
    {
        PIGenerator pig;
        for(int i=pigArg[1]; i<=pigArg[0]; i+=pigArg[2])
        {
            for(int j=0; j<pigArg[3]; ++j)
            {
                shouldBes.push_back(true);
                inputs.push_back(pig.generatePI(true, i));
                shouldBes.push_back(false);
                inputs.push_back(pig.generatePI(false, i));
            }
        }
    }
    else if(pigIsOn && casesAreExtreme)
    {
        PIGenerator pig;

        for(int i=pigArg[1]; i<=pigArg[0]; i+=pigArg[2])
        {
            shouldBes.push_back(false);
            inputs.push_back(pig.createExtremeCase(i, AlgHolder::directions[algKey]));
        }
    }
    else
        inputs = ArgGetter::getArgs(cin);

        for (auto i:inputs)
            answers.push_back(solver->solve(i));

    if(timerIsOn)
        timeMeasurements = solver->extractTimeRecords();

    auto inputItr = inputs.begin();
    auto answerItr = answers.begin();
    auto shouldBeItr = shouldBes.begin();
    auto timeRecordItr = timeMeasurements.begin();

    while(inputItr!=inputs.end() && answerItr!=answers.end() && (shouldBeItr!=shouldBes.end() || !pigIsOn) && (timeRecordItr!=timeMeasurements.end() || !timerIsOn))
    {
        cout << "Case:" <<endl;
        for(int i=0; i<inputItr->size(); ++i)
            cout << (*inputItr)[i] << " ";
        cout << endl;
        ++inputItr;
        cout << "Answer: " << *(answerItr++);
        if(pigIsOn)
            cout << ", Should be: " << *(shouldBeItr++);
        if(timerIsOn)
            cout << ", Execution time: " << *(timeRecordItr++) << " ms";
        cout << "\n" << endl;
    }

    if(timerIsOn && pigIsOn)
    {
        map<int, double> meanSolveTimes = calcMeanTimes(inputs, timeMeasurements);
        map<int, double> maxSolveTimes = calcMaxTimes(inputs, timeMeasurements);
        int med = findMed(pigArg[0], pigArg[1], pigArg[2]);
        long double c_factor_mean = meanSolveTimes[med]/(AlgHolder::asymptotics[algKey])(med);
        long double c_factor_max = maxSolveTimes[med]/(AlgHolder::asymptotics[algKey])(med);

        cout << "Mean execution times for " << algKey << " algorithm:" << endl;
        printTable(cout, meanSolveTimes, c_factor_mean, algKey);
        cout << endl;
        cout << "Max execution times for " << algKey << " algorithm:" << endl;
        printTable(cout, maxSolveTimes, c_factor_max, algKey);
    }

    delete solver;
    return 0;
}

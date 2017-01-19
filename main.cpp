#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <map>
#include "Solver.h"
#include "TimerSolver.h"
#include "ArgGetter.h"
#include "PIGenerator.h"
#include "algorithms.hpp"

#define INVALID_PARAM -1

using namespace std;

namespace
{
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

    int findMed(ending, beginning, step)
    {
        int distanceScaledByStep = (ending - beginning)/step;
        return beginning + (distanceScaledByStep / 2) * step;
    }
}

int main(int argc, char* argv[])
{
    vector<int> pigArg = {20, 1, 1, 3};
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
        if(/*argv[i][0]=='-' && argv[i][1]=='m'*/string(argv[i])=="-t" || string(argv[i])=="--timer")
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
                if((to_put=atoi(argv[i+1+j])==0)
                    break;
                pigArg[j]=to_put;
            }
            i+=j;
            if(pigArg[0]<pigArg[1])
            {
                cout << "Error: Proble Instance Generation arguments are inconsistent." << endl;
                return INVALID_PARAM;
            }
        }
        else if(argv[i][0]=='-' && argv[i][1]=='a')
            algKey=argv[i][2];
        /*{
            switch(argv[i][2])
            {
                case 'S':
                cout << "Hi, I'm the stdin execution!" << endl;
                break;

                case 'G':
                cout << "Hi, I'm the PIG execution!" << endl;
                break;

                case 'T':
                cout << "Hi, I'm the timer experiment execution!" << endl;
                break;

                default:
                cout << "Nieznany argument \"" << argv[i] << "\"" << endl;
            }
        }*/
        else
        {
            cout << "Unknown argument \"" << argv[i] << "\"" << endl;
            return INVALID_PARAM;
        }

    }

    auto algItr = algs.find(algKey);
    if(algItr==algs.end())
    {
        cout << "Unknown algorithm \"" << algKey << "\"." << endl;
        return INVALID_PARAM;
    }

    if(timerIsOn)
        solver = new TimerSolver(algItr->second);
    else
        solver = new Solver(algItr->second);

    if(pigIsOn)
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
    else
        inputs = ArgGetter::getArgs(cin);

        for (auto i:inputs)
            answers.push_back(solver->solve(i));

    if(timerIsOn)
        timeMeasurements = solver->extractTimeRecords();

    /*for(auto i:answers)
    {
        cout << i.first << ": ";
        for(auto j:i.second)
            cout << j << " ";
        cout << endl;
    }*/

    auto inputItr = inputs.begin();
    auto answerItr = answers.begin();
    auto shouldBeItr = shouldBes.begin();
    auto timeRecordItr = timeMeasurements.begin();

    while(inputItr!=inputs.end() && answerItr!=answers.end() && shouldBeItr!=shouldBes.end() && timeRecordItr!=timeMeasurements.end())
    {
        cout << "Case:" <<endl;
        for(int i=0; i<inputItr->size(); ++i)
            cout << (*inputItr)[i] << " ";
        cout << endl;
        ++inputItr;
        cout << "Answer: " << *(answerItr++) << ", Should be: " << *(shouldBeItr++) << ", Execution time: " << *(timeRecordItr++) << " ms \n" << endl;
    }

    int med = findMed(pigArg[0], pigArg[1], pigArg[2]);
    double c_factor =

    delete solver;
    return 0;
}

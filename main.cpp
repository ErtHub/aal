#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
//#include <map>
#include "Solver.h"
#include "TimerSolver.h"
#include "ArgGetter.h"
#include "PIGenerator.h"
#include "algorithms.hpp"

#define INVALID_PARAM -1

using namespace std;

int main(int argc, char* argv[])
{
    int piLenMin = 1;
    int piLenMax = 20;
    int piLenGrad = 1;
    int timesGenerate = 3;
    list<vector<int>> inputs;
    Solver *solver;
    list<bool> answers;
    list<bool> shouldBes;
    list<double> timeMeasurements;
    bool timerIsOn = false;
    bool pigIsOn = false;
    char algKey = 'D';

    for (int i=1; i<argc; ++i)
    {
        if(/*argv[i][0]=='-' && argv[i][1]=='m'*/string(argv[i])=="-t" || string(argv[i])=="--timer")
            timerIsOn = true;
        else if(string(argv[i])=="-g" || string(argv[i])=="--generate-args")
            pigIsOn = true;
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
        for(int i=piLenMin; i<=piLenMax; i+=piLenGrad)
        {
            for(int j=0; j<timesGenerate; ++j)
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
        cout << "Przypadek:" <<endl;
        for(int i=0; i<inputItr->size(); ++i)
            cout << (*inputItr)[i] << " ";
        cout << endl;
        ++inputItr;
        cout << "Odpowiedz: " << *(answerItr++) << ", Powinno byc: " << *(shouldBeItr++) << ", Czas wykonania: " << *(timeRecordItr++) << "\n" << endl;
    }

    delete solver;
    return 0;
}

#include "PIGenerator.h"

using namespace std;

int PIGenerator::calcDestiny(vector<int>& past)
{
    vector<bool> visited(past.size(), false);
    vector<int> leap_counters(past.size(), 0);
    int last_recorded = 1;

    if(past.size()==0)
        return 1;
    if(past.size()==1)
        return past[0]+2;
    visited[0]=visited[1]=true;
    leap_counters[0]=0;
    leap_counters[1]=1;
    for(int i=1; i<past.size(); ++i)
    {
        if(!visited[i])
            continue;
        for(int j=i+1; j<past.size() && past[j]<=past[i]+leap_counters[i]+1; ++j)
        {
            if(past[j]<past[i]+leap_counters[i]-1 || visited[j])
                continue;
            visited[j]=true;
            leap_counters[j]=past[j]-past[i];
            if(j==past.size()-1)
                return past[j]+leap_counters[j]+2;
            last_recorded = j;
        }
    }
    return past[past.size()-1]+leap_counters[last_recorded]+2+(past[past.size()-1]-past[last_recorded]);
}

vector<int> PIGenerator::generatePI(bool solution, int length)
{
    vector<int> to_return(0, 0);
    if(length<1)
        return to_return;

    if(length==1)
    {
        if(solution)
            to_return.push_back(0);
        else
            to_return.push_back(1);
        return to_return;
    }

    random_device rd;
    mt19937 rng(rd());

    int destiny;

    if(!solution)
    {
        uniform_int_distribution<int> uni(1, length-1);
        destiny=uni(rng);
    }

    int last_leap=0;
    int last_pos=0;
    to_return.push_back(0);
    vector<int> dist_table(0, 0);

    for(int i=1; i<length; ++i)
    {
        if(!solution && i==destiny)
        {
            to_return.push_back(calcDestiny(to_return));
            last_pos=i;
            ++last_leap;
            continue;
        }
        for(int j=dist_table.size(); j<last_leap+1; ++j)
            dist_table.push_back(distribution_broadness+(multiplier*j));
        int border = ((i==length-1) ? (last_leap - 2) : (to_return[i-1]-to_return[last_pos]));
        if(border<0)
            border=0;

        discrete_distribution<int> discr(dist_table.begin()+border, dist_table.begin()+last_leap+1);
        int leap = discr(rng) + border + 1;
        to_return.push_back(to_return[last_pos]+leap);
        if(leap>=last_leap-1 && leap<=last_leap+1)
        {
            last_leap=leap;
            last_pos=i;
        }
    }
    return to_return;
}

vector<int> PIGenerator::createExtremeCase(int length, AlgSearchingDirection direction)
{
    if(length<=1)
        return vector<int>();
    vector<int> to_return(length, 0);
    int item, iteration_start, iteration_step, iteration_finish;
    if(direction==lesser_to_greater)
    {
        item = 0;
        iteration_start = 0;
        iteration_step = 1;
        iteration_finish = length - 1;
        to_return[length - 1] = INT_MAX;
    }
    else if(direction==greater_to_lesser)
    {
        item = INT_MAX;
        iteration_start = length - 1;
        iteration_step = -1;
        iteration_finish = 1;
        to_return[0] = 0;
        to_return[1] = 1;
    }
    else
        return vector<int>();
    for(int i = iteration_start; i != iteration_finish; i+=iteration_step)
    {
        to_return[i] = item;
        item += iteration_step;
    }
    return to_return;
}

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "PIGenerator.h"

namespace
{
unsigned long long intPow(int base, int exp)
{
    int result = 1;
    for(int i=0; i<exp; ++i)
    {
        result*=base;
    }
    return result;
}
//--------------------------------------------------------------------------------------------------------------------------------
bool recursiveCheck (std::vector<int>& stones, int target, int step_to_target, unsigned long long& range)
{
	if(target<0 || step_to_target<0) return false;
	if(stones[target]==1 && stones[step_to_target]==0) return true;
	int two_steps_to_target=step_to_target-1;
	unsigned long long step;
	while(stones[step_to_target]-stones[two_steps_to_target] < range-1)
		--two_steps_to_target;
	while((step=stones[step_to_target]-stones[two_steps_to_target]) <= range+1)
	{
		if((0.5*((step*step)+step))>stones[step_to_target]) return false;
		if(recursiveCheck(stones, step_to_target, two_steps_to_target, step)) return true;
		--two_steps_to_target;
	}
	return false;
}

bool revSearch(std::vector<int>& stones)
{
	if(stones.size()<1)
	return false;
	if(stones.size()==1)
	{
        if(stones[0]==0)
            return true;
        else
            return false;
	}
	int target=stones.size()-1;
	int step_to_target=stones.size()-2;
	unsigned long long step;
	for(; step_to_target>=0; --step_to_target)
	{
		step=stones[target]-stones[step_to_target];
		if((0.5*((step*step)+step))>stones[target]) return false;
		if(recursiveCheck(stones, target, step_to_target, step)) return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------------

bool iterMemSearch(std::vector<int>& stones)
{
	int n=stones.size();
	if(n<1)
        return false;
	if(n==1)

	{
        if(stones[0]==0)
            return true;
        else
            return false;
	}

	bool* matrix=new bool[n*n];

	for(int i=0; i<n*n; ++i)
		matrix[i]=false;

	matrix[1]=true;
	int target=stones[n-1];
	for(int i=1; i<n; ++i)
	{
		for(int j=i-1; j>=0; --j)
		{
			if(stones[i]-stones[j]>=n) break;
			if(matrix[j*n+stones[i]-stones[j]])
			{
				if(target>=stones[i]+stones[i]-stones[j]-1 && target<=stones[i]+stones[i]-stones[j]+1)
				{
					delete[] matrix;
					return true;
				}
				if(stones[i]-stones[j]>1)
					matrix[i*n+stones[i]-stones[j]-1]=true;
				matrix[i*n+stones[i]-stones[j]]=true;
				if(stones[i]-stones[j]+1<n)
					matrix[i*n+stones[i]-stones[j]+1]=true;
			}
		}
	}
	delete[] matrix;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

bool recurMemSearch(std::vector<int>& stones, int pos, int k, std::unordered_map<int, bool>& memory)
{
    int key = pos | k << 11;

    if (memory.count(key) > 0)
        return memory[key];

    for (int i = pos + 1; i < stones.size(); i++)
    {
        int gap = stones[i] - stones[pos];
        if (gap < k - 1)
            continue;
        if (gap > k + 1)
            return memory[key] = false;
        if (recurMemSearch(stones, i, gap, memory))
            return memory[key] = true;
    }

    return memory[key] = (pos == stones.size() - 1);
}
bool recurMemSearch(std::vector<int>& stones)
{
    std::unordered_map<int, bool> memory;
    return recurMemSearch(stones, 0, 0, memory);
}
}//end of namespace

class AlgHolder
{
    public:
    static std::map<char, bool(*)(std::vector<int>&)> algs;
    static std::map<char, unsigned long long(*)(int)> asymptotics;
    static std::map<char, AlgSearchingDirection> directions;
};
std::map<char, bool(*)(std::vector<int>&)> AlgHolder::algs={{'D', &revSearch}, {'I', &iterMemSearch}, {'R', &recurMemSearch}};
std::map<char, unsigned long long(*)(int)> AlgHolder::asymptotics={{'D', [](int n){return intPow(3, n);}}, {'I', [](int n){return intPow(n, 2);}}, {'R', [](int n){return intPow(n, 2);}}};
std::map<char, AlgSearchingDirection> AlgHolder::directions={{'D', greater_to_lesser}, {'I', lesser_to_greater}, {'R', lesser_to_greater}};

#endif

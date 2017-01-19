#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

namespace ArgGetter
{
    std::list<std::vector<int>> getArgs(std::istream& is);
}

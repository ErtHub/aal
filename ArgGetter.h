#ifndef ARGGETTER_H
#define ARGGETTER_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

namespace ArgGetter
{
    std::list<std::vector<int>> getArgs(std::istream& is);
}

#endif

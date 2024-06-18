#ifndef IPC_H
#define IPC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "utem.h"

namespace cpi {

    std::map<int, double> calculate(std::vector<int> months, std::map<int, double> amountSums);
    
    std::map<int, double> makeCpi(std::vector<int> codes);
};

#endif /* IPC_H */


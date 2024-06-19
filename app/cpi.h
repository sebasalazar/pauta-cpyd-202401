#ifndef IPC_H
#define IPC_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "xlsxio/xlsxio_read.h"
#include "product.h"
#include "utem.h"
#include "summary.h"

namespace cpi {

    std::map<int, double> getForeignExchange(std::string filePath);

    std::map<int, double> calculate(std::vector<int> months, std::map<int, double> amountSums);

    std::map<int, double> getCpi(std::vector<int> codes, std::set<Product> products);

    std::map<int, Summary> makeCpi(std::map<int, double> exchange, std::vector<int> codes);
};

#endif /* IPC_H */


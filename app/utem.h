#ifndef UTEM_H
#define UTEM_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include "year_month.h"
#include "contenedor.h"
#include "producto.h"

namespace utem {

    /**
     * 
     * @param str Texto a procesar
     * @return El objeto YearMonth del parseo
     */
    YearMonth parseYearMonth(const std::string& str);

    std::string removeQuotes(const std::string &text);
    
    std::vector<std::string> split(const std::string &line, char delimiter);

    Contenedor parseCsvLine(const std::string& str);
};

#endif /* UTEM_H */


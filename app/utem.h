#ifndef UTEM_H
#define UTEM_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include "year_month.h"

namespace utem {

    /**
     * 
     * @param str Texto a procesar
     * @return El objeto YearMonth del parseo
     */
    YearMonth parse(const std::string& str);

};

#endif /* UTEM_H */


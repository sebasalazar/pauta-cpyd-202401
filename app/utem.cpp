#include "utem.h"

YearMonth utem::parse(const std::string& str) {
    std::istringstream iss(str);
    int year, month;
    char dash;

    if (!(iss >> year >> dash >> month) || dash != '-' || !iss.eof()) {
        throw std::invalid_argument("Formato inválido se espera inicio YYYY-MM");
    }

    return YearMonth(year, month);
}

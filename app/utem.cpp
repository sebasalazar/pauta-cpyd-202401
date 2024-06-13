#include "utem.h"

YearMonth utem::parseYearMonth(const std::string& str) {
    std::istringstream iss(str);
    int year, month;
    char dash;

    if (!(iss >> year >> dash >> month) || dash != '-' || !iss.eof()) {
        throw std::invalid_argument("Formato inválido se espera inicio YYYY-MM");
    }

    return YearMonth(year, month);
}

std::vector<std::string> utem::split(const std::string &line, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

Contenedor utem::parseCsvLine(const std::string& line) {
    Contenedor contenedor;
    std::vector<std::string> fields = split(line, ';');
    if (fields.size() == 10) {
        std::string created = fields[0];
        std::string sku = fields[6];
        int quantity = std::atoi(fields[7].c_str());
        double amount = std::atof(fields[9].c_str());

        YearMonth ym = parseYearMonth(created);
        Producto producto = Producto(sku, (amount / quantity));
        contenedor = Contenedor(ym, producto);
    }
    return contenedor;
}
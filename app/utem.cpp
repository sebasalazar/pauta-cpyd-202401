#include "utem.h"

YearMonth utem::parseYearMonth(const std::string& str) {
    int year = std::stoi(str.substr(0, 4));
    int month = std::stoi(str.substr(5, 2));

    return YearMonth(year, month);
}

std::string utem::removeQuotes(const std::string &text) {
    std::string result = text;
    result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
    return result;
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
    std::vector<std::string> fields = split(removeQuotes(line), ';');
    if (fields.size() == 10) {
        std::string created = fields[0];
        std::string sku = fields[6];
        int quantity = std::stoi(fields[7]);
        double amount = std::stod(fields[9]);

        YearMonth ym = parseYearMonth(created);
        Producto producto = Producto(sku, (amount / quantity));
        contenedor = Contenedor(ym, producto);
    }
    return contenedor;
}
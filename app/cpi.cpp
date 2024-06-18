#include "cpi.h"

std::map<int, double> cpi::calculate(std::vector<int> months, std::map<int, double> amountSums) {
    std::map<int, double> cpi;

    int index = 0;
    double current = 0;
    std::sort(months.begin(), months.end());
    for (int ym : months) {
        double last = amountSums[ym];
        if (index > 0) {
            cpi[ym] = ((last - current) / current) * 100;
        } else {
            cpi[ym] = 0;
        }
        index += 1;
        current = last;
    }
    return cpi;
}

std::map<int, double> cpi::makeCpi(std::vector<int> codes) {
    std::map<int, double> cpi;
    if (!codes.empty()) {
        std::map<int, double> amountSums;
        std::set<Product> canasta = utem::obtenerCanastaBasica(codes);
        std::map<int, double> currentMap = utem::obtenerIpc(codes, canasta);
        for (std::map<int, double>::iterator it = currentMap.begin(); it != currentMap.end(); ++it) {
            amountSums[it->first] = it->second;
        }

        cpi = calculate(codes, amountSums);
    }
    return cpi;
}

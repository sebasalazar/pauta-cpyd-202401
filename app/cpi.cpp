#include "cpi.h"

std::map<int, double> cpi::getForeignExchange(std::string filePath) {
    std::map<int, double> result;

    xlsxioreader xlsxioread;

    if (!filePath.empty() && (xlsxioread = xlsxioread_open(filePath.c_str())) != NULL) {
        std::map<int, std::vector<double>> current;
        //read values from first sheet
        xlsxioreadersheet sheet;
        const char* sheetname = NULL;
        if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
            // leemos todas las filas
            while (xlsxioread_sheet_next_row(sheet)) {
                // Primera celda
                std::time_t ts = {};
                int resultTime = xlsxioread_sheet_next_cell_datetime(sheet, &ts);

                // Segunda celda
                double clp = 0;
                int resultValue = xlsxioread_sheet_next_cell_float(sheet, &clp);

                if (resultTime > 0 && resultValue > 0) {
                    std::string localTime = utem::getLocalTime(ts);
                    YearMonth ym = utem::parseYearMonth(localTime);
                    current[ym.GetYearMonth()].push_back(clp);
                }
            }
            xlsxioread_sheet_close(sheet);
        }

        if (!current.empty()) {
            for (std::map<int, std::vector<double>>::iterator it = current.begin(); it != current.end(); ++it) {
                int ym = it->first;
                std::vector<double> values = it->second;
                result[ym] = utem::calculateMedian(values);
            }
        }

        // liberar memoria
        xlsxioread_close(xlsxioread);
    } else {
        std::cerr << "Error con archivo Excel " << filePath << std::endl;
    }
    return result;
}

std::map<int, double> cpi::getCpi(std::vector<int> codes, std::set<Product> products) {
    std::map<int, double> map;
    if (!codes.empty() && !products.empty()) {
        std::sort(codes.begin(), codes.end());
        for (int code : codes) {
            double sum = 0;
            std::ifstream file(utem::tempPath + "/" + std::to_string(code) + ".csv");
            if (file.is_open()) {
                std::string linea;
                while (std::getline(file, linea)) {
                    std::vector<std::string> splited = utem::split(linea, ';');
                    if (!splited.empty()) {
                        Product p(splited[0], std::stod(splited[1]));
                        if (std::find(products.begin(), products.end(), p) != products.end()) {
                            sum += p.GetAmount();
                        }
                    }
                }
                file.close();
            }
            map[code] = sum;
        }
    }
    return map;
}

std::map<int, double> cpi::getParallelCpi(std::vector<int> codes, std::set<Product> products) {
    std::map<int, double> map;
    if (!codes.empty() && !products.empty()) {
        std::sort(codes.begin(), codes.end());

        // Define un map local para cada thread y fusiona después
        std::vector<std::map<int, double>> local_maps(omp_get_max_threads());

#pragma omp parallel for
        for (std::vector<int>::size_type i = 0; i < codes.size(); ++i) {
            int code = codes[i];
            double sum = 0;
            std::ifstream file(utem::tempPath + "/" + std::to_string(code) + ".csv");
            if (file.is_open()) {
                std::string linea;
                while (std::getline(file, linea)) {
                    std::vector<std::string> splited = utem::split(linea, ';');
                    if (!splited.empty()) {
                        Product p(splited[0], std::stod(splited[1]));
                        if (products.find(p) != products.end()) {
                            sum += p.GetAmount();
                        }
                    }
                }
                file.close();
            }

            // Almacena el resultado en el map local del thread
            int thread_id = omp_get_thread_num();
            local_maps[thread_id][code] = sum;
        }

        // Fusiona los resultados de los maps locales en el map global
        for (std::vector<std::map<int, double>>::const_iterator local_map_it = local_maps.begin(); local_map_it != local_maps.end(); ++local_map_it) {
            for (std::map<int, double>::const_iterator entry_it = local_map_it->begin(); entry_it != local_map_it->end(); ++entry_it) {
                map[entry_it->first] = entry_it->second;
            }
        }
    }
    return map;
}

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

std::map<int, Summary> cpi::makeCpi(std::map<int, double> exchange, std::vector<int> codes) {
    std::map<int, Summary> result;
    if (!codes.empty()) {
        std::map<int, double> clpSum;
        std::map<int, double> penSum;
        std::set<Product> basket = utem::getBasicBasket(codes);

        std::map<int, double> currentMap = getParallelCpi(codes, basket);
        for (std::map<int, double>::iterator it = currentMap.begin(); it != currentMap.end(); ++it) {
            int ym = it->first;
            double pen = it->second;
            double clp = pen * exchange[ym];
            penSum[ym] = pen;
            clpSum[ym] = clp;
        }

        std::map<int, double> penCpi = calculate(codes, penSum);
        std::map<int, double> clpCpi = calculate(codes, clpSum);

        for (int ym : codes) {
            double cpiPen = penCpi[ym];
            double sumPen = penSum[ym];
            double cpiClp = clpCpi[ym];
            long sumClp = (long) clpSum[ym];
            Summary summary(cpiPen, sumPen, cpiClp, sumClp);
            result[ym] = summary;
        }
    }
    return result;
}

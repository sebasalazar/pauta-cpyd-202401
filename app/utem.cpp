#include "utem.h"

std::string utem::getLocalTime() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm current = *std::localtime(&now);
    // Formatear la fecha y hora
    std::stringstream ss;
    ss << std::put_time(&current, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string utem::getLocalTime(std::time_t ts) {
    std::tm current = *std::localtime(&ts);
    // Formatear la fecha y hora
    std::stringstream ss;
    ss << std::put_time(&current, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

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

std::map<int, std::vector<int>> utem::getMonthsInYears(std::set<int> codes) {
    std::map<int, std::vector<int>> map;
    for (int code : codes) {
        YearMonth ym(code);
        map[ym.GetYear()].push_back(ym.GetYearMonth());
    }
    return map;
}

void utem::unify(int code) {
    // Leemos el archivo año-mes
    std::string inFilePath = tempPath + "/" + std::to_string(code);
    std::ifstream inFile(inFilePath);
    if (inFile.is_open()) {
        std::map<std::string, std::vector<double>> map;

        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<std::string> fields = split(line, ';');
            if (fields.size() == 2) {
                std::string sku = fields[0];
                double amount = std::stod(fields[1]);
                map[sku].push_back(amount);
            }
        }
        inFile.close();

        std::string outFilePath = tempPath + "/" + std::to_string(code) + ".csv";
        std::ofstream outFile(outFilePath, std::ios_base::app); // Abre el archivo en modo append
        if (outFile.is_open()) {
            for (std::map<std::string, std::vector<double>>::iterator it = map.begin(); it != map.end(); ++it) {
                std::string sku = it->first;
                std::vector<double> amounts = it->second;
                double amount = calculateMedian(amounts);
                outFile << sku << ";" << amount << std::endl;
            }
            outFile.close(); // Cerrar el archivo después de escribir
        } else {
            std::cerr << "Error al abrir el archivo para escritura: " << outFilePath << std::endl;
        }

        // Eliminamos el archivo temporal
        if (std::remove(inFilePath.c_str()) != 0) {
            std::cerr << "Error al eliminar el archivo temporal: " << outFilePath << std::endl;
        }
    } else {
        std::cerr << "Error al abrir el archivo de entrada: " << inFilePath << std::endl;
    }
}

double utem::calculateMedian(std::vector<double> list) {
    // Obtener el iterador al elemento mediano
    std::vector<double>::const_iterator first = list.begin();
    std::advance(first, list.size() / 2);

    // Calcular la mediana
    if (list.size() % 2 == 0) {
        // Tamaño par: mediana es el promedio de los dos valores centrales
        std::vector<double>::const_iterator second = first;
        --second; // Retroceder un paso para el segundo valor central
        return (*first + *second) / 2.0;
    } else {
        // Tamaño impar: mediana es el valor central
        return *first;
    }
}

std::set<Product> utem::getBasicBasket(std::vector<int> codes) {
    std::set<Product> basket;
    if (!codes.empty()) {
        if (codes.size() > 1) {
            std::set<Product> list;
            int base = codes[0];
            std::ifstream file(tempPath + "/" + std::to_string(base) + ".csv");
            if (file.is_open()) {
                std::string linea;
                while (std::getline(file, linea)) {
                    std::vector<std::string> splited = split(linea, ';');
                    if (!splited.empty()) {
                        Product p(splited[0], std::stod(splited[1]));
                        list.insert(p);
                    }
                }
                file.close();
            }

            // Paraleliza este bloque con OpenMP
#pragma omp parallel for
            for (std::vector<int>::size_type i = 1; i < codes.size(); ++i) {
                int code = codes[i];
                if (code != base) {
                    std::set<Product> current;
                    std::ifstream file(tempPath + "/" + std::to_string(code) + ".csv");
                    if (file.is_open()) {
                        std::string linea;
                        while (std::getline(file, linea)) {
                            std::vector<std::string> splited = split(linea, ';');
                            if (!splited.empty()) {
                                Product p(splited[0], std::stod(splited[1]));
                                current.insert(p);
                            }
                        }
                        file.close();
                    }

                    // Sección crítica para actualizar 'list' de manera segura
#pragma omp critical
                    {
                        if (!current.empty()) {
                            std::set<Product> repited;
                            std::set_intersection(list.begin(), list.end(), current.begin(), current.end(),
                                    std::inserter(repited, repited.begin()));
                            list = std::move(repited);
                        }
                    }
                }
            }

            basket = std::move(list);
        } else {
            int base = codes[0];
            std::ifstream file(tempPath + "/" + std::to_string(base) + ".csv");
            if (file.is_open()) {
                std::string linea;
                while (std::getline(file, linea)) {
                    std::vector<std::string> splited = split(linea, ';');
                    if (!splited.empty()) {
                        Product p(splited[0], std::stod(splited[1]));
                        basket.insert(p);
                    }
                }
                file.close();
            }
        }
    }
    return basket;
}



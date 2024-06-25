#ifndef UTEM_H
#define UTEM_H

#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <limits.h>
#include "cpi.h"
#include "product.h"
#include "year_month.h"

namespace utem {

    static const std::string zeroStr("0");
    static const std::string tempPath("tmp");


    /**
     * @brief Texto con la hora local
     * @return La hora local como texto en formato ISO
     */
    std::string getLocalTime();

    /**
     * @brief Texto con la hora local
     * @return La hora local como texto en formato ISO
     */
    std::string getLocalTime(std::time_t ts);

    /**
     * @brief Parsea una cadena y devuelve un objeto YearMonth.
     * 
     * @param str Texto a procesar.
     * @return El objeto YearMonth del parseo.
     */
    YearMonth parseYearMonth(const std::string& str);

    /**
     * @brief Remueve las comillas dobles de un texto.
     * 
     * @param text Texto a procesar.
     * @return Texto sin comillas dobles.
     */
    std::string removeQuotes(const std::string &text);

    /**
     * @brief Divide una línea de texto en partes, utilizando un delimitador.
     * 
     * @param line Línea de texto a dividir.
     * @param delimiter Delimitador utilizado para dividir la línea.
     * @return Vector de partes resultantes.
     */
    std::vector<std::string> split(const std::string &line, char delimiter);

    /**
     * @brief Transforma los años meses en un mapa separado por años
     * @param codes listado de información
     * @return Mapa
     */
    std::map<int, std::vector<int>> getMonthsInYears(std::set<int> codes);
    
    std::vector<int> getYears(std::set<int> codes);

    /**
     * @brief Esta función reduce las ocurrencias dentro de los archivos
     * @param code código a revisar
     */
    void unify(int code);

    /**
     * @brief Calcula la mediana.
     * 
     * @param list Listado de datos a procesar
     */
    double calculateMedian(std::vector<double> list);

    std::set<Product> getBasicBasket(std::vector<int> codes);


};

#endif /* UTEM_H */

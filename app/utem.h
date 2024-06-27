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

/**
 * Utilitario para algunas tareas comunes para el manejo del programa.
 */
namespace utem {

    /**
     * Variable final que se usará para comparar los elementos 0 del archivo.
     */
    static const std::string zeroStr("0");

    /**
     * Carpeta temporal dentro del directorio actual de trabajo.
     */
    static const std::string tempPath("tmp");

    /**
     * @brief Obtiene la hora local actual como una cadena de texto en formato ISO.
     * 
     * @return La hora local actual en formato ISO (YYYY-MM-DD HH:MM:SS).
     */
    std::string getLocalTime();

    /**
     * @brief Convierte un timestamp dado a una cadena de texto en formato ISO.
     * 
     * @param ts Timestamp a convertir.
     * @return La hora correspondiente al timestamp en formato ISO (YYYY-MM-DD HH:MM:SS).
     */
    std::string getLocalTime(std::time_t ts);

    /**
     * @brief Parsea una cadena y devuelve un objeto YearMonth.
     * 
     * @param str Cadena de texto a procesar.
     * @return El objeto YearMonth resultante del parseo.
     */
    YearMonth parseYearMonth(const std::string& str);

    /**
     * @brief Remueve las comillas dobles de una cadena de texto.
     * 
     * @param text Cadena de texto a procesar.
     * @return La cadena de texto sin comillas dobles.
     */
    std::string removeQuotes(const std::string &text);

    /**
     * @brief Divide una cadena de texto en partes utilizando un delimitador.
     * 
     * @param line Cadena de texto a dividir.
     * @param delimiter Carácter delimitador utilizado para dividir la cadena.
     * @return Un vector con las partes resultantes de la división.
     */
    std::vector<std::string> split(const std::string &line, char delimiter);

    /**
     * @brief Organiza un conjunto de códigos de año y mes en un mapa separado por años.
     * 
     * @param codes Conjunto de códigos de año y mes en formato AAMM.
     * @return Un mapa donde la clave es el año y el valor es un vector de meses correspondientes a ese año.
     */
    std::map<int, std::vector<int>> getMonthsInYears(std::set<int> codes);

    /**
     * @brief Obtiene un vector de años a partir de un conjunto de códigos de año y mes.
     * 
     * @param codes Conjunto de códigos de año y mes en formato AAMM.
     * @return Un vector con los años presentes en los códigos.
     */
    std::vector<int> getYears(std::set<int> codes);

    /**
     * @brief Reduce las ocurrencias dentro de los archivos para un código dado.
     * 
     * @param code Código a revisar y unificar.
     */
    void unify(int code);

    /**
     * @brief Calcula la mediana de una lista de valores.
     * 
     * @param list Lista de valores a procesar.
     * @return La mediana de la lista de valores.
     */
    double calculateMedian(std::vector<double> list);

    /**
     * @brief Obtiene la canasta básica de productos a partir de un vector de códigos Año-Mes.
     * 
     * @param codes Vector de códigos a procesar.
     * @return Un conjunto de productos que forman la canasta básica.
     */
    std::set<Product> getBasicBasket(std::vector<int> codes);

};

#endif /* UTEM_H */

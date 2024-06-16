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
#include "contenedor.h"
#include "producto.h"
#include "year_month.h"

namespace utem {

    const std::string zeroStr("0");
    const std::string tempPath("tmp");

    /**
     * @brief Texto con la hora local
     * @return La hora local como texto en formato ISO
     */
    std::string getLocalTime();

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
     * @brief Elimina un directorio en la ruta especificada.
     * 
     * @param dirPath Ruta del directorio a eliminar.
     */
    void removeDirectory(const std::string& dirPath);

    /**
     * @brief Crea un directorio en la ruta especificada.
     * 
     * @param dirPath Ruta del directorio a crear.
     */
    std::string createDirectory(const std::string& dirPath);

    /**
     * @brief Crea un directorio temporal.
     */
    std::string createTempDirectory();

    /**
     * @brief Escribe los datos de YearMonth y Producto.
     * 
     * @param ym Objeto YearMonth.
     * @param producto Objeto Producto.
     */
    void escribir(YearMonth ym, Producto producto);

    /**
     * @brief Parsea una línea CSV y devuelve un objeto Contenedor.
     * 
     * @param str Línea CSV a parsear.
     * @return Código del año-mes procesado
     */
    int parseCsvLine(const std::string& str);

    /**
     * @brief Transforma los años meses en un mapa separado por años
     * @param codes listado de información
     * @return Mapa
     */
    std::map<int, std::vector<int>> mapear(std::set<int> codes);

    /**
     * @brief Esta función reduce las ocurrencias dentro de los archivos
     * @param code código a revisar
     */
    void unificar(int code);

    /**
     * @brief Calcula la mediana.
     * 
     * @param list Listado de datos a procesar
     */
    double calculateMedian(std::set<double> list);
};

#endif /* UTEM_H */

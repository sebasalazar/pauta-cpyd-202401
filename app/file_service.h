#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <chrono>
#include <unordered_map>
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
#include "utem.h"

class FileService {
public:
    FileService();
    virtual ~FileService();

    std::vector<std::string> parseLine(const std::string& line);

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
     * @return std::string Ruta del directorio creado.
     */
    std::string createDirectory(const std::string& dirPath);

    /**
     * @brief Crea un directorio temporal.
     * 
     * @return std::string Ruta del directorio temporal creado.
     */
    std::string createTempDirectory();

    /**
     * @brief Parsea una línea CSV y devuelve un código de año-mes procesado.
     * 
     * @param str Línea CSV a parsear.
     * @return int Código del año-mes procesado.
     */
    int parseCsvLine(const std::string& str);

private:

    std::unordered_map<std::string, std::ofstream> fileMap;

    /**
     * @brief Escribe los datos de YearMonth y Producto.
     * 
     * @param ym Código Año-Mes.
     * @param sku Código del producto.
     * @param amount Monto.
     */
    void write(int ym, std::string& sku, double amount);
};

#endif /* FILE_SERVICE_H */

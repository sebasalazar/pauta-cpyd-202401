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

/**
 * @class FileService
 * @brief Clase para manejar operaciones de archivo y directorio, incluyendo parsing de CSV.
 */
class FileService {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un objeto FileService.
     */
    FileService();

    /**
     * @brief Destructor.
     *
     * Libera los recursos utilizados por el objeto FileService.
     */
    virtual ~FileService();

    /**
     * @brief Parsea una línea de texto y la divide en componentes.
     * 
     * @param line Línea de texto a parsear.
     * @return std::vector<std::string> Vector con los componentes de la línea.
     */
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
    /**
     * Mapa para manejar archivos abiertos.
     * A medida que se necesitan abrir archivos, estos manejadores se agregan a 
     * este mapa, de tal manera de sólo gastar tiempo en i/o una vez por 
     * instancia de esta clase.
     */
    std::unordered_map<std::string, std::ofstream> fileMap;

    /**
     * @brief Escribe los datos de YearMonth y Producto en un archivo.
     * 
     * @param ym Código Año-Mes.
     * @param sku Código del producto.
     * @param amount Monto.
     */
    void write(int ym, std::string& sku, double amount);
};

#endif /* FILE_SERVICE_H */

#ifndef CPI_H
#define CPI_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <omp.h>
#include "xlsxio/xlsxio_read.h"
#include "product.h"
#include "utem.h"
#include "summary.h"

/**
 * @namespace cpi
 * @brief Espacio de nombres para las funciones relacionadas con el cálculo del IPC.
 */
namespace cpi {

    /**
     * @brief Obtiene el tipo de cambio extranjero desde un archivo.
     * 
     * @param filePath Ruta del archivo que contiene los datos de tipo de cambio.
     * @return std::map<int, double> Mapa con los tipos de cambio por año-mes.
     */
    std::map<int, double> getForeignExchange(std::string filePath);

    /**
     * @brief Calcula el IPC utilizando los meses y las sumas de cantidades.
     * 
     * @param months Vector de códigos de año-mes.
     * @param amountSums Mapa de sumas de cantidades por año-mes.
     * @return std::map<int, double> Mapa del IPC calculado por año-mes.
     */
    std::map<int, double> calculate(std::vector<int> months, std::map<int, double> amountSums);

    /**
     * @brief Obtiene el IPC basado en los códigos y productos proporcionados.
     * 
     * @param codes Vector de códigos de año-mes.
     * @param products Conjunto de productos.
     * @return std::map<int, double> Mapa del IPC por año-mes.
     */
    std::map<int, double> getCpi(std::vector<int> codes, std::set<Product> products);

    /**
     * @brief Obtiene el IPC de forma paralela basado en los códigos y productos proporcionados.
     * 
     * @param codes Vector de códigos de año-mes.
     * @param products Conjunto de productos.
     * @return std::map<int, double> Mapa del IPC por año-mes.
     */
    std::map<int, double> getParallelCpi(std::vector<int> codes, std::set<Product> products);

    /**
     * @brief Genera un mapa de resumen del IPC utilizando el tipo de cambio y los códigos proporcionados.
     * 
     * @param exchange Mapa de tipos de cambio por año-mes.
     * @param codes Vector de códigos de año-mes.
     * @return std::map<int, Summary> Mapa de resúmenes de IPC por año-mes.
     */
    std::map<int, Summary> makeCpi(std::map<int, double> exchange, std::vector<int> codes);
};

#endif /* CPI_H */

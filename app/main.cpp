#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cstdlib>
#include <future>
#include <mutex>
#include <omp.h>
#include "utem.h"


/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa);

std::set<int> carga_inicial(std::string rutaArchivo);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {

    /**
     * Incluir acá la lógica del programa
     * 
     */
    const std::string tmpDirectory = utem::createTempDirectory();
    std::cout << "Carpeta temporal " << tmpDirectory << std::endl;

    if (argc > 1) {
        // Separamos los datos en archivos más pequeños dentro de la carpeta temporal, el original tiene 56916429 filas
        std::cout << utem::getLocalTime() << " Paso 1 - Clasifico los datos" << std::endl;
        std::set<int> codes = carga_inicial(argv[1]);

        // El contendor de vector está preparado para trabajar en parallel for
        std::cout << utem::getLocalTime() << " Paso 2 - Reduzco los SKU en base a la mediana" << std::endl;
        std::vector<int> list(codes.begin(), codes.end());

#pragma omp parallel for
        for (size_t index = 0; index < list.size(); ++index) {
            int code = list[index];
            utem::unificar(code);

            // Esto es opcional, sólo para mostrar datos
#pragma omp critical
            std::cout << utem::getLocalTime() << " Paso 2.1 Hilo " << omp_get_thread_num() << " el código " << code << std::endl;
        }

        std::cout << utem::getLocalTime() << " Paso 3 - Comparo por año" << std::endl;
        std::map<int, std::set<int> > map = utem::mapear(codes);
    } else {
        // Mostrar los integrantes
        participantes(argv[0]);
    }
    return EXIT_SUCCESS;
}

void participantes(std::string programa) {
    std::cout << std::endl << "=== Pauta del programa " << programa << " ===" << std::endl;
    std::cout << std::endl << "Profesor: Sebastián Salazar Molina" << std::endl;
}

std::set<int> carga_inicial(std::string rutaArchivo) {
    std::set<int> codes;

    std::ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        // Omitir la primera línea si contiene encabezados
        std::string encabezado;
        std::getline(archivo, encabezado);

        std::string linea;
        /*
         * Leemos el archivo para clasificar los datos por mes.
         */
        while (std::getline(archivo, linea)) {
            int code = utem::parseCsvLine(linea);
            if (code > 0) {
                codes.insert(code);
            }
        }
        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo" << std::endl;
    }

    return codes;
}

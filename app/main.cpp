#include <iostream>
#include <future>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>
#include "utem.h"

/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(const std::string& programa);

std::set<int> carga_inicial(const std::string& rutaArchivo);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {

    const std::string tmpDirectory = utem::createTempDirectory();
    std::cout << "Carpeta temporal " << tmpDirectory << std::endl;

    if (argc > 1) {
        std::cout << utem::getLocalTime() << " Paso 1 - Clasifico los datos" << std::endl;
        std::set<int> codes = carga_inicial(argv[1]);

        std::cout << utem::getLocalTime() << " Paso 2 - Reduzco los SKU en base a la mediana" << std::endl;
        std::vector<int> list(codes.begin(), codes.end());

#pragma omp parallel for
        for (size_t index = 0; index < list.size(); ++index) {
            int code = list[index];
            utem::unificar(code);

#pragma omp critical
            std::cout << utem::getLocalTime() << " Paso 2.1 Hilo " << omp_get_thread_num() << " el código " << code << std::endl;
        }

        std::cout << utem::getLocalTime() << " Paso 3 - Preparo los datos de todos los años" << std::endl;
        std::future<std::map<int, double>> future = std::async(std::launch::async, cpi::makeCpi, list);

        std::cout << utem::getLocalTime() << " Paso 4 - Preparo los datos por año" << std::endl;
        std::map<int, std::vector<int>> map = utem::mapear(codes);
        std::map<int, double> cpi;

#pragma omp parallel
        {
#pragma omp single nowait
            {
                for (std::map<int, std::vector<int>>::iterator it = map.begin(); it != map.end(); ++it) {
                    int year = it->first;
                    std::vector<int> months = it->second;

#pragma omp task firstprivate(year, months)
                    {
                        std::map<int, double> currentMap = cpi::makeCpi(months);
#pragma omp critical
                        {
                            cpi.insert(currentMap.begin(), currentMap.end());
                            std::cout << utem::getLocalTime() << " Paso 4.1 - Terminando proceso del año " << year << std::endl;
                        }
                    }
                }
            }
        }

        for (std::map<int, double>::iterator it = cpi.begin(); it != cpi.end(); ++it) {
            std::cout << it->first << " IPC: " << it->second << std::endl;
        }

        std::cout << "IPC de todos los meses" << std::endl;
        std::map<int, double> all = future.get();
        for (std::map<int, double>::iterator it = all.begin(); it != all.end(); ++it) {
            std::cout << it->first << " IPC: " << it->second << std::endl;
        }
    } else {
        participantes(argv[0]);
    }

    return EXIT_SUCCESS;
}

void participantes(const std::string& programa) {
    std::cout << std::endl << "=== Pauta del programa " << programa << " ===" << std::endl;
    std::cout << std::endl << "Profesor: Sebastián Salazar Molina" << std::endl;
}

std::set<int> carga_inicial(const std::string& rutaArchivo) {
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

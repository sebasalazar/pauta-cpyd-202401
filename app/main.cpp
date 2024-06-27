#include <iostream>
#include <iomanip>
#include <future>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>
#include "summary.h"
#include "utem.h"
#include "file_service.h"

/**
 * @brief Función que muestra los participantes del programa
 * 
 * @param program nombre del ejecutable
 */
void about(const std::string& program);

/**
 * @brief Operación que separa en archivos año-mes los datos del archivo inicial
 * 
 * @param csv Ruta donde se encuentra el archivo CSV
 * @return un lista única con los año-mes que existen en el archivo
 */
std::set<int> load(const std::string& csv);

/**
 * @brief Pauta del proyecto del curso, sólo es una referencia al mecanismo usado para la evaluación.
 * 
 * @param argc cantidad de argumentos
 * @param argv arreglo de argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {

    // Configurar std::cout para usar 2 decimales
    std::cout << std::fixed << std::setprecision(2);

    if (argc > 2) {
        /*
         * El programa está segmentado en etapas.
         * 
         */
        // Obtenemos la ruta del archivo CSV que será el primer argumento
        const std::string csvFile(argv[1]);

        // Obtenemos la ruta del archivo XLSX que será el segundo argumento
        const std::string excelFile(argv[2]);

        /*
         * PASO 1.
         * 
         * Clasificación de DATOS
         * Esta etapa tiene un paralelismo sencillo, 
         * se puede optimizar bastante si se trabaja en 
         * la lectura en paralelo del archivo.
         * 
         * Para cada año-mes tendrá un archivo con los productos que fueron comprados 
         * en esa unidad de tiempo.
         */
        std::cout << utem::getLocalTime() << " Paso 1 - Clasifico los datos" << std::endl;

        // En un hilo asíncrono la aplicación cargará las divisas en un mapa que se llama exchange
        std::future<std::map<int, double>> futureExchange = std::async(std::launch::async, cpi::getForeignExchange, excelFile);

        // El hilo principal (lento) clasifica los datos que se procesan en el archivo 
        // y nos devuelve una lista única de año-mes YYYYMM (ej: 202101,202102,...,202404)
        const std::set<int> yearsMonth = load(csvFile);

        // Obtenemos la respuesta del procesamiento asíncrono.
        const std::map<int, double> exchange = futureExchange.get();

        /*
         * PASE 2.
         * 
         * Reducción de SKU, para obtener el monto se utilizará la MEDIANA como 
         * mecanismo de cálculo y comparación.
         * 
         */
        std::cout << utem::getLocalTime() << " Paso 2 - Reduzco los SKU" << std::endl;

        // En la implementación OpenMP de GCC el contenedor vector está preparado para el paralelismo.
        // copiamos un vector para mejorar el procesamiento
        const std::vector<int> list(yearsMonth.begin(), yearsMonth.end());

        // Para cada archivo generado en el paso anterior, se calcula la mediana de los precios
#pragma omp parallel for
        for (size_t index = 0; index < list.size(); ++index) {
            // Año-mes (YYYYMM) a procesar
            int code = list[index];

            // Este mecanismo es mejorable, se calculan sku que después se descartarán
            // Pero en la estrategia es válido, porque evita calcularlo después
            utem::unify(code);

            // Mostramos una línea para evidenciar el hilo que procesó el archivo (no es necesario).
#pragma omp critical
            std::cout << utem::getLocalTime() << " Paso 2.1 Hilo " << omp_get_thread_num() << " el código " << code << std::endl;
        }

        /*
         * PASO 3.
         * 
         * Ejecuto un hilo asíncrono para procesar el IPC de todos los meses.
         * Este proceso requiere revisar todos los archivos y es lento.
         */
        std::cout << utem::getLocalTime() << " Paso 3 - Preparo los datos de todos los años" << std::endl;

        // Envío la tarea asíncrona
        std::future<std::map<int, Summary>> future = std::async(std::launch::async, cpi::makeCpi, exchange, list);

        /*
         * PASO 4.
         * 
         * Procesamos los valores para cada año.
         * La idea es enviar lo años se procesen en paralelo.
         */
        std::cout << utem::getLocalTime() << " Paso 4 - Preparo los datos por año" << std::endl;
        // Obtenemos un mapa en donde la llave es el año y los valores son los meses
        const std::map<int, std::vector<int>> monthsInYear = utem::getMonthsInYears(yearsMonth);
        std::vector<int> years = utem::getYears(yearsMonth);

        // Estructura donde almacenaremos el IPC, la llave es el año y los valores el resumen de los datos
        std::map<int, Summary> cpi;

#pragma omp parallel for
        for (size_t index = 0; index < years.size(); index++) {
            int year = years[index];
            std::vector<int> months = monthsInYear.at(year);

            // Mapa con el resultado actual del año en curso
            std::map<int, Summary> currentMap = cpi::makeCpi(exchange, months);
#pragma omp critical
            {
                // se agrega al mapa de resultados
                cpi.insert(currentMap.begin(), currentMap.end());
                std::cout << utem::getLocalTime() << " Paso 4.1 - Terminando proceso del año " << year << std::endl;
            }
        }

        // Se muestras los resultados año-mes
        for (std::map<int, Summary>::iterator it = cpi.begin(); it != cpi.end(); ++it) {
            std::cout << it->first
                    << " IPC Perú:  " << it->second.GetCpiPen() << " (S/" << it->second.GetSumPen() << ")\t\t"
                    << " IPC Chile: " << it->second.GetCpiClp() << " ($ " << it->second.GetSumClp() << ") "
                    << std::endl;
        }

        // Se muestran los resutlados para todos los meses
        std::cout << "IPC de todos los meses" << std::endl;
        std::map<int, Summary> all = future.get();
        for (std::map<int, Summary>::iterator it = all.begin(); it != all.end(); ++it) {
            std::cout << it->first
                    << " IPC Perú:  " << it->second.GetCpiPen() << " (S/" << it->second.GetSumPen() << ")\t\t"
                    << " IPC Chile: " << it->second.GetCpiClp() << " ($ " << it->second.GetSumClp() << ") "
                    << std::endl;
        }
    } else {
        about(argv[0]);
    }

    return EXIT_SUCCESS;
}

void about(const std::string& program) {
    std::cout << std::endl << "=== Pauta del Proyecto ===" << std::endl;
    std::cout << std::endl << "Profesor: Sebastián Salazar Molina" << std::endl;
    std::cout << std::endl << "Modo de uso" << std::endl;
    std::cout << std::endl << program << " \"ruta/a/pd.csv\" \"ruta/a/Datos históricos PEN_CLP.xlsx\"" << std::endl;
}

std::set<int> load(const std::string& rutaArchivo) {
    std::set<int> codes;

    std::ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        FileService fileService;

        // Omitir la primera línea si contiene encabezados
        std::string encabezado;
        std::getline(archivo, encabezado);

        std::string linea;
        /*
         * Leemos el archivo para clasificar los datos por mes.
         */
        while (std::getline(archivo, linea)) {
            int code = fileService.parseCsvLine(linea);
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

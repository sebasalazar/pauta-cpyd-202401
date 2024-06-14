#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "utem.h"


/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa);

void carga_inicial(std::string rutaArchivo);

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
    if (argc > 1) {
        carga_inicial(argv[1]);
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

void carga_inicial(std::string rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    // Omitir la primera línea si contiene encabezados
    std::string encabezado;
    std::getline(archivo, encabezado);

    std::string linea;
    // Lee el archivo línea por línea en paralelo
    while (std::getline(archivo, linea)) {
        Contenedor contenedor = utem::parseCsvLine(linea);
        std::cout
                << "Fecha: " << contenedor.GetYearMonth().GetYearMonth()
                << " SKU: " << contenedor.GetProducto().GetSku()
                << " Monto: " << contenedor.GetProducto().GetAmount()
                << std::endl;
    }

    archivo.close();
}
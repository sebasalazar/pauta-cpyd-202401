#ifndef YEAR_MONTH_H
#define YEAR_MONTH_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>

/**
 * @class YearMonth
 * @brief Clase para representar un año y un mes.
 *
 * La clase YearMonth proporciona una representación y manipulación de una combinación de año y mes.
 * Esta es una idea robada de Java 8+, que es útil para trabajar con año y mes de  una forma resuminda.
 */
class YearMonth {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un objeto YearMonth con el año y mes por defecto.
     */
    YearMonth();

    /**
     * @brief Constructor que inicializa con un código combinado de año y mes.
     *
     * @param code Código combinado de año y mes en el formato AAAAMM (AAAA: año 2024, MM: mes 6 sería 202406).
     */
    YearMonth(int code);

    /**
     * @brief Constructor que inicializa con un año y un mes específicos.
     *
     * @param year Año a ser establecido.
     * @param month Mes a ser establecido.
     * @throws std::invalid_argument Si el mes no está en el rango 1-12.
     */
    YearMonth(int year, int month);

    /**
     * @brief Constructor de copia.
     *
     * @param orig Objeto YearMonth a copiar.
     */
    YearMonth(const YearMonth& orig);

    /**
     * @brief Destructor.
     */
    virtual ~YearMonth();

    /**
     * @brief Obtiene el mes.
     *
     * @return El mes (1-12).
     */
    int GetMonth() const;

    /**
     * @brief Obtiene el año.
     *
     * @return El año.
     */
    int GetYear() const;

    /**
     * @brief Obtiene el código combinado de año y mes.
     *
     * @return El código combinado en el formato AAMM.
     */
    int GetYearMonth() const;

    /**
     * @brief Convierte el objeto YearMonth a una cadena de texto.
     *
     * @return Una cadena en el formato "YYYY-MM".
     */
    std::string toString() const;

    /**
     * @brief Operador de igualdad.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si ambos objetos son iguales, false en caso contrario.
     */
    bool operator==(const YearMonth& other) const;

    /**
     * @brief Operador de desigualdad.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si ambos objetos son diferentes, false en caso contrario.
     */
    bool operator!=(const YearMonth& other) const;

    /**
     * @brief Operador menor que.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si este objeto es menor que el otro, false en caso contrario.
     */
    bool operator<(const YearMonth& other) const;

    /**
     * @brief Operador menor o igual que.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si este objeto es menor o igual que el otro, false en caso contrario.
     */
    bool operator<=(const YearMonth& other) const;

    /**
     * @brief Operador mayor que.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si este objeto es mayor que el otro, false en caso contrario.
     */
    bool operator>(const YearMonth& other) const;

    /**
     * @brief Operador mayor o igual que.
     *
     * @param other Objeto YearMonth a comparar.
     * @return true si este objeto es mayor o igual que el otro, false en caso contrario.
     */
    bool operator>=(const YearMonth& other) const;

    /**
     * @brief Operador de asignación.
     *
     * @param right Objeto YearMonth a asignar.
     * @return Una referencia a este objeto.
     */
    YearMonth& operator=(const YearMonth& right);

private:
    /**
     * El valor del mes, dentro del rango 1 a 12 (Enero a Diciembre).
     */
    int month;

    /**
     * El valor de año.
     */
    int year;

    /**
     * @brief Valida el año y el mes.
     *
     * @param year Año a validar.
     * @param month Mes a validar.
     * @throws std::invalid_argument Si el mes no está en el rango 1-12.
     */
    void validate(int year, int month);
};

#endif /* YEAR_MONTH_H */

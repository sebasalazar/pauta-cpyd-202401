#ifndef SUMMARY_H
#define SUMMARY_H

/**
 * @class Summary
 * @brief Clase para representar un resumen con valores de IPC y sumas en diferentes monedas.
 */
class Summary {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un objeto Summary con valores predeterminados.
     */
    Summary();

    /**
     * @brief Constructor con parámetros.
     *
     * @param cpiPen Índice de Precios al Consumidor (IPC) en PEN.
     * @param sumPen Suma en PEN.
     * @param cpiClp Índice de Precios al Consumidor (IPC) en CLP.
     * @param sumClp Suma en CLP.
     */
    Summary(double cpiPen, double sumPen, double cpiClp, long sumClp);

    /**
     * @brief Constructor de copia.
     *
     * @param orig Objeto Summary a copiar.
     */
    Summary(const Summary& orig);

    /**
     * @brief Destructor.
     */
    virtual ~Summary();

    /**
     * @brief Obtiene el IPC en CLP.
     *
     * @return El IPC en CLP.
     */
    double GetCpiClp() const;

    /**
     * @brief Establece el IPC en CLP.
     *
     * @param cpiClp El nuevo valor del IPC en CLP.
     */
    void SetCpiClp(double cpiClp);

    /**
     * @brief Obtiene el IPC en PEN.
     *
     * @return El IPC en PEN.
     */
    double GetCpiPen() const;

    /**
     * @brief Establece el IPC en PEN.
     *
     * @param cpiPen El nuevo valor del IPC en PEN.
     */
    void SetCpiPen(double cpiPen);

    /**
     * @brief Obtiene la suma en CLP.
     *
     * @return La suma en CLP.
     */
    long GetSumClp() const;

    /**
     * @brief Establece la suma en CLP.
     *
     * @param sumClp El nuevo valor de la suma en CLP.
     */
    void SetSumClp(long sumClp);

    /**
     * @brief Obtiene la suma en PEN.
     *
     * @return La suma en PEN.
     */
    double GetSumPen() const;

    /**
     * @brief Establece la suma en PEN.
     *
     * @param sumPen El nuevo valor de la suma en PEN.
     */
    void SetSumPen(double sumPen);

private:
    /**
     * Índice de Precios al Consumidor (IPC) en Soles Peruanos (PEN).
     */
    double cpiPen;

    /**
     * Suma de la canasta básica en Soles Peruanos (PEN).
     */
    double sumPen;

    /**
     * Índice de Precios al Consumidor (IPC) en Pesos Chilenos (CLP).
     */
    double cpiClp;

    /**
     * Suma de la canasta básica en Pesos Chilenos (CLP).
     */
    long sumClp;
};

#endif /* SUMMARY_H */

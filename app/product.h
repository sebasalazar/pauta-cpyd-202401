#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

/**
 * @class Product
 * @brief Clase para representar un producto con un SKU y un monto asociado.
 */
class Product {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un objeto Product con valores predeterminados.
     */
    Product();

    /**
     * @brief Constructor con parámetros.
     *
     * @param sku SKU del producto.
     * @param amount Monto asociado al producto.
     */
    Product(std::string sku, double amount);

    /**
     * @brief Constructor de copia.
     *
     * @param orig Objeto Product a copiar.
     */
    Product(const Product& orig);

    /**
     * @brief Destructor.
     */
    virtual ~Product();

    /**
     * @brief Obtiene el monto del producto.
     *
     * @return El monto del producto.
     */
    double GetAmount() const;

    /**
     * @brief Establece el monto del producto.
     *
     * @param amount El nuevo monto del producto.
     */
    void SetAmount(double amount);

    /**
     * @brief Obtiene el SKU del producto.
     *
     * @return El SKU del producto.
     */
    std::string GetSku() const;

    /**
     * @brief Establece el SKU del producto.
     *
     * @param sku El nuevo SKU del producto.
     */
    void SetSku(std::string sku);

    /**
     * @brief Operador de desigualdad.
     *
     * @param right Objeto Product a comparar.
     * @return true si los productos son diferentes, false en caso contrario.
     */
    bool operator!=(const Product& right) const;

    /**
     * @brief Operador de igualdad.
     *
     * @param right Objeto Product a comparar.
     * @return true si los productos son iguales, false en caso contrario.
     */
    bool operator==(const Product& right) const;

    /**
     * @brief Operador de asignación.
     *
     * @param right Objeto Product a asignar.
     * @return Una referencia a este objeto.
     */
    Product& operator=(const Product& right);

    /**
     * @brief Operador menor que.
     *
     * @param right Objeto Product a comparar.
     * @return true si este producto es menor que el otro, false en caso contrario.
     */
    bool operator<(const Product& right) const;

    /**
     * @brief Operador menor o igual que.
     *
     * @param right Objeto Product a comparar.
     * @return true si este producto es menor o igual que el otro, false en caso contrario.
     */
    bool operator<=(const Product& right) const;

    /**
     * @brief Operador mayor que.
     *
     * @param right Objeto Product a comparar.
     * @return true si este producto es mayor que el otro, false en caso contrario.
     */
    bool operator>(const Product& right) const;

    /**
     * @brief Operador mayor o igual que.
     *
     * @param right Objeto Product a comparar.
     * @return true si este producto es mayor o igual que el otro, false en caso contrario.
     */
    bool operator>=(const Product& right) const;

private:
    /**
     * SKU del producto.
     */
    std::string sku;

    /**
     * Monto (en alguna unidad monetaria abstracta) asociado al producto.
     */
    double amount;
};

#endif /* PRODUCTO_H */

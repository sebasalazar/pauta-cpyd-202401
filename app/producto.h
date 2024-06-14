#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

class Producto {
public:
    Producto();
    Producto(std::string sku, double amount);
    Producto(const Producto& orig);
    virtual ~Producto();
    double GetAmount() const;
    void SetAmount(double amount);
    std::string GetSku() const;
    void SetSku(std::string sku);
    bool operator!=(const Producto& right) const;
    bool operator==(const Producto& right) const;
    Producto& operator=(const Producto& right);
private:
    std::string sku;
    double amount;
};

#endif /* PRODUCTO_H */


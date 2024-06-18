#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

class Product {
public:
    Product();
    Product(std::string sku, double amount);
    Product(const Product& orig);
    virtual ~Product();
    double GetAmount() const;
    void SetAmount(double amount);
    std::string GetSku() const;
    void SetSku(std::string sku);
    bool operator!=(const Product& right) const;
    bool operator==(const Product& right) const;
    Product& operator=(const Product& right);
    bool operator<(const Product& right) const;
    bool operator<=(const Product& right) const;
    bool operator>(const Product& right) const;
    bool operator>=(const Product& right) const;
private:
    std::string sku;
    double amount;
};

#endif /* PRODUCTO_H */


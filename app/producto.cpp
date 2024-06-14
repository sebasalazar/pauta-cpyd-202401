#include "producto.h"

Producto::Producto() {
    this->sku = std::string("");
    this->amount = 0;
}

Producto::Producto(std::string sku, double amount) {
    this->sku = std::string(sku);
    this->amount = amount;
}

Producto::Producto(const Producto& orig) {
    this->sku = std::string(orig.GetSku());
    this->amount = orig.GetAmount();
}

Producto::~Producto() {
    if (!sku.empty()) {
        sku.clear();
    }
}

double Producto::GetAmount() const {
    return amount;
}

void Producto::SetAmount(double amount) {
    this->amount = amount;
}

std::string Producto::GetSku() const {
    return sku;
}

void Producto::SetSku(std::string sku) {
    this->sku = sku;
}

bool Producto::operator!=(const Producto& right) const {
    return !(this->sku == right.sku);
}

bool Producto::operator==(const Producto& right) const {
    return (this->sku == right.sku);
}

Producto& Producto::operator=(const Producto& right) {
    if (this == &right) {
        return *this;
    }

    sku = right.sku;
    amount = right.amount;

    return *this;
}
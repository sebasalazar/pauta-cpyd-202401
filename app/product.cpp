#include "product.h"

Product::Product() {
    this->sku = std::string("");
    this->amount = 0;
}

Product::Product(std::string sku, double amount) {
    this->sku = std::string(sku);
    this->amount = amount;
}

Product::Product(const Product& orig) {
    this->sku = std::string(orig.GetSku());
    this->amount = orig.GetAmount();
}

Product::~Product() {
    if (!sku.empty()) {
        sku.clear();
    }
}

double Product::GetAmount() const {
    return amount;
}

void Product::SetAmount(double amount) {
    this->amount = amount;
}

std::string Product::GetSku() const {
    return sku;
}

void Product::SetSku(std::string sku) {
    this->sku = sku;
}

bool Product::operator!=(const Product& right) const {
    return !(this->sku == right.sku);
}

bool Product::operator==(const Product& right) const {
    return (this->sku == right.sku);
}

Product& Product::operator=(const Product& right) {
    if (this == &right) {
        return *this;
    }

    sku = right.sku;
    amount = right.amount;

    return *this;
}

bool Product::operator<(const Product& right) const {
    return right.sku > sku; // Reuse greater than operator
}

bool Product::operator<=(const Product& right) const {
    return !(sku > right.sku); // Reuse greater than operator
}

bool Product::operator>(const Product& right) const {
    return sku > right.sku;
}

bool Product::operator>=(const Product& right) const {
    return !(right.sku > sku);
}
#include "contenedor.h"

Contenedor::Contenedor() {
    this->yearMonth = YearMonth();
    this->producto = Producto();
}

Contenedor::Contenedor(YearMonth yearMonth, Producto producto) {
    this->yearMonth = yearMonth;
    this->producto = producto;
}

Contenedor::Contenedor(const Contenedor& orig) {
    this->yearMonth = orig.yearMonth;
    this->producto = orig.producto;
}

Contenedor::~Contenedor() {
}

Producto Contenedor::GetProducto() const {
    return producto;
}

YearMonth Contenedor::GetYearMonth() const {
    return yearMonth;
}
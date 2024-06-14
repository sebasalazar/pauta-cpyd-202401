#include "contenedor.h"

Contenedor::Contenedor() {
    this->yearMonth = YearMonth();
    this->producto = Producto();
}

Contenedor::Contenedor(YearMonth ym, Producto p) {
    this->yearMonth = YearMonth(ym.GetYear(), ym.GetMonth());
    this->producto = Producto(p.GetSku(), p.GetAmount());
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
#ifndef CONTENEDOR_H
#define CONTENEDOR_H

#include "producto.h"
#include "year_month.h"

class Contenedor {
public:
    Contenedor();
    Contenedor(YearMonth yearMonth, Producto producto);
    Contenedor(const Contenedor& orig);
    virtual ~Contenedor();
    Producto GetProducto() const;
    YearMonth GetYearMonth() const;
private:
    YearMonth yearMonth;
    Producto producto;
};

#endif /* CONTENEDOR_H */


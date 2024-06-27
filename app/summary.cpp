#include "summary.h"

Summary::Summary() {
    this->sumClp = 0;
    this->cpiClp = 0;
    this->cpiPen = 0;
    this->sumPen = 0;
}

Summary::Summary(double cpiPen, double sumPen, double cpiClp, long sumClp) {
    this->sumClp = sumClp;
    this->cpiClp = cpiClp;
    this->cpiPen = cpiPen;
    this->sumPen = sumPen;
}

Summary::Summary(const Summary& orig) {
    this->sumClp = orig.sumClp;
    this->cpiClp = orig.cpiClp;
    this->cpiPen = orig.cpiPen;
    this->sumPen = orig.sumPen;
}

Summary::~Summary() {
}

double Summary::GetCpiClp() const {
    return cpiClp;
}

void Summary::SetCpiClp(double cpiClp) {
    this->cpiClp = cpiClp;
}

double Summary::GetCpiPen() const {
    return cpiPen;
}

void Summary::SetCpiPen(double cpiPen) {
    this->cpiPen = cpiPen;
}

long Summary::GetSumClp() const {
    return sumClp;
}

void Summary::SetSumClp(long sumClp) {
    this->sumClp = sumClp;
}

double Summary::GetSumPen() const {
    return sumPen;
}

void Summary::SetSumPen(double sumPen) {
    this->sumPen = sumPen;
}

#ifndef SUMMARY_H
#define SUMMARY_H

class Summary {
public:
    Summary();
    Summary(double cpiPen, double sumPen, double cpiClp, long sumClp);
    Summary(const Summary& orig);
    virtual ~Summary();
    double GetCpiClp() const;
    void SetCpiClp(double cpiClp);
    double GetCpiPen() const;
    void SetCpiPen(double cpiPen);
    long GetSumClp() const;
    void SetSumClp(long sumClp);
    double GetSumPen() const;
    void SetSumPen(double sumPen);

private:
    double cpiPen;
    double sumPen;
    double cpiClp;
    long sumClp;
};

#endif /* SUMMARY_H */


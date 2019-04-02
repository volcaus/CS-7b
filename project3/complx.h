#include <iostream>

class Complx
{
public:
    Complx(double re = 0.0, double im = 1.0);
    double real();
    double real(double);
    double imag();
    double imag(double);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Complx& cNum);

    friend std::istream& operator>>(std::istream& is,
                                    const Complx& cNum);
    

private:
    double realNum;
    double imagNum;
};


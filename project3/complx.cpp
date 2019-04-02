#include "complx.h"

Complx::Complx(double re, double im) //default ctor
{
    realNum = re;
    imagNum = im;
}

double Complx::real()
{
    return realNum;
}

double Complx::real(double re)
{
    realNum = re;
}

double Complx::imag()
{
    return imagNum;
}

double Complx::imag(double im)
{
    imagNum = im;
}

std::ostream& operator<<(std::ostream& os, const Complx& cNum)
{
        os << cNum.realNum << ", " << cNum.imagNum << 'i';
        return os;
}

std::istream& operator>>(std::istream& is, const Complx& cNum)
{
        is >> cNum.realNum >> cNum.imagNum;
        return is;
}
#include <cmath>
#include "complx.h"

Complx::Complx(double re, double im) //ctor
{
    realNum = re;
    imagNum = im;
}

double Complx::real() // returns realNum for Complx object that calls this
{
    return realNum;
}

void Complx::real(double re) // sets realNum for Complx object that calls this
{
    realNum = re;
}

double Complx::imag() // returns imagNum for Complx object that calls this
{
    return imagNum;
}

void Complx::imag(double im) // sets imagNum for Complx object that calls this
{
    imagNum = im;
}

Complx Complx::conj() // returns conjugate of the Complx object that calls it
{
    Complx n;

    n.real(this -> realNum);
    n.imag(this -> imagNum * -1);

    return n;
}

double Complx::abs()
{
    return sqrt(this->realNum*this->realNum + this->imagNum*this->imagNum);
}

std::ostream& operator<<(std::ostream& os, const Complx& cNum)
{
        os << cNum.realNum << ", " << cNum.imagNum << 'i';
        return os;
}

std::istream& operator>>(std::istream& is, Complx& cNum)
{
    is >> cNum.realNum >> cNum.imagNum;
    return is;
}
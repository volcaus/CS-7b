#include <iostream>

class Complx
{
public:
	Complx(double re = 0.0, double im = 1.0); // default constructor yields a value of i
	double real(); // returns current real component
	void real(double); // sets new real component
	double imag(); // returns current imaginary component
	void imag(double); // sets new imaginary component
	Complx conj(); // returns the conjugate of the Complx object that calls it
	double abs(); // returns modulus (distance from origin) of the complex number

	friend std::ostream& operator<<(std::ostream& os, const Complx& cNum);

	friend std::istream& operator>>(std::istream& is, Complx& cNum);

	Complx operator+(const Complx& lhs)
	{
		Complx n;

		n.realNum = this->realNum + lhs.realNum;
		n.imagNum = this->imagNum + lhs.imagNum;

		return n;
	}

	Complx operator-(const Complx& lhs)
	{
		Complx n;

		n.realNum = lhs.realNum - this->realNum;
		n.imagNum = lhs.imagNum - this->imagNum;

		return n;
	}

	Complx operator*(const Complx& lhs)
	{
		Complx n;

		n.realNum = (this -> realNum * lhs.realNum) - (this -> imagNum * lhs.imagNum);
		n.imagNum = (lhs.realNum * this -> imagNum) + (lhs.imagNum * this -> realNum);

		return n;
	}

	Complx operator/(const Complx& lhs)
	{
		Complx n, temp(this -> realNum, this -> imagNum);
		double d;

		n = temp.conj() * lhs;
		d = (this -> realNum * this->realNum) + (this -> imagNum * this -> imagNum);

		n.realNum = n.realNum / d;
		n.imagNum = n.imagNum /d;

		return n;
	}

private:
	double realNum;
	double imagNum;
};


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

	Complx operator+(const Complx& rhs)
	{
		Complx n;

		n.realNum = this->realNum + rhs.realNum;
		n.imagNum = this->imagNum + rhs.imagNum;

		return n;
	}

	Complx operator-(const Complx& rhs)
	{
		Complx n;

		n.realNum = this->realNum - rhs.realNum;
		n.imagNum = this->imagNum - rhs.imagNum;

		return n;
	}

	Complx operator*(const Complx& rhs)
	{
		Complx n;

		n.realNum = (this -> realNum * rhs.realNum) - (this -> imagNum * rhs.imagNum);
		n.imagNum = (rhs.realNum * this -> imagNum) + (rhs.imagNum * this -> realNum);

		return n;
	}

	Complx operator/(const Complx& rhs)
	{
		Complx n, temp(rhs.realNum, rhs.imagNum);
		double d;

		temp = temp.conj();
		d = (rhs.realNum * rhs.realNum) + (rhs.imagNum * rhs.imagNum);

		n.realNum = ((this->realNum * temp.realNum) + (this->imagNum * temp.imagNum)*-1)/d;
		n.imagNum = ((this->imagNum*temp.realNum)+(this->realNum*temp.imagNum))/d;

		return n;
	}

private:
	double realNum;
	double imagNum;
};


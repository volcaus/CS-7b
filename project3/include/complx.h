#include <iostream>

class Complx
{
public:
	Complx(double re = 0.0, double im = 1.0);
	double real();
	void real(double);
	double imag();
	void imag(double);

	friend std::ostream& operator<<(std::ostream& os,
									const Complx& cNum);

	friend std::istream& operator>>(std::istream& is,
									Complx& cNum);

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

		n.realNum = this->realNum * lhs.realNum;
		n.imagNum = this->imagNum * lhs.imagNum;

		return n;
	}

		Complx operator/(const Complx& lhs)
	{
		Complx n;

		n.realNum = lhs.realNum / this->realNum;
		n.imagNum = lhs.imagNum / this->imagNum;

		return n;
	}

private:
	double realNum;
	double imagNum;
};


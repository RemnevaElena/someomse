#include "RationalFracs.h"

int Frac::gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void Frac::simplify()
{
	int del = gcd(num < 0 ? -num : num, den);
	num /= del;
	den /= del;
}
bool Frac::CompareToDouble(int sec) {
	if (double(*this) > sec) return true; else return false;
}
int Frac::getNumDen(int n)
{
	if (n == 0) return num; else return den;
}
Frac::Frac()
{
	num = 0;
	den = 1;
}

Frac::Frac(int num, int den)
{
	if (den < 0)
		this->den = -den;
	else
		this->den = den;
	this->num = num;
	//�������� �����
	simplify();
}
istream& operator >> (istream& in, Frac& fr)
{
	cout << "������� ���������: " << endl;
	in >> fr.num;
	cout << "������� �����������: " << endl;
	in >> fr.den;
	return in;
}
ostream& operator << (ostream& os, const Frac& fr)
{
	return os << fr.num << "/" << fr.den;
}

//����������� �������� �����������������
Frac& Frac::operator++()
{
	num += den;
	return *this;
}

//���������� �������� �����������������
Frac Frac::operator++(int)
{
	int temp = num;
	num += den;
	return Frac(temp, den);
}
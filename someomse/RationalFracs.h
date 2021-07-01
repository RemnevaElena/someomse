#pragma once

#include <iostream>
using namespace std;

class Frac
{
private:
    int num;
    int den;
    // Ищем наибольший делитель числителя и знаменателя
    int gcd(int a, int b);
    //Сокращаем дробь
    void simplify();
public:

    // Конструктор по умолчанию
    Frac();
    // Конструктор с параметрами
    //Знаменатель должен быть > 0, поэтому проверяем этот момент
    Frac(int num, int den);
    bool CompareToDouble(int sec);

    int getNumDen(int n);

    operator double() const {
        return (double)num / den;
    }
    operator int() const {
        return (int)num / den;
    }

    Frac operator + (const Frac& secfrac) const {
        return Frac(num * secfrac.den + den * secfrac.num, den * secfrac.den);
    }
    Frac operator += (Frac& secfrac) {
        *this = *this + secfrac;
        return *this;
    }
    Frac operator - (const Frac& secfrac) const {
        return Frac(num * secfrac.den - den * secfrac.num, den * secfrac.den);
    }
    Frac operator -= (Frac& secfrac) {
        *this = *this - secfrac;
        return *this;
    }
    Frac operator * (const Frac& secfrac) const {
        return Frac(num * secfrac.num, den * secfrac.den);
    }
    Frac operator *= (const Frac& secfrac) {
        *this = *this * secfrac;
        return *this;
    }
    Frac operator / (const Frac& secfrac) const {
        return Frac(num * secfrac.den, den * secfrac.num);
    }
    Frac operator /= (const Frac& secfrac) {
        *this = *this / secfrac;
        return *this;
    }
    Frac operator = (const Frac& secfrac) {
        num = secfrac.num;
        den = secfrac.den;
        return *this;
    }
    bool operator < (const Frac& secfrac) const {
        return num * secfrac.den < den* secfrac.num;
    }
    bool operator > (const Frac& secfrac) const {
        return secfrac < *this;
    }
    bool operator == (const Frac& secfrac) const {
        return secfrac.num == num && secfrac.den == den;
    }
    bool operator <= (const Frac& secfrac) const {
        return (secfrac < *this) || (secfrac == *this);
    }
    bool operator >= (const Frac& secfrac) const {
        return (secfrac > * this) || (secfrac == *this);
    }
    bool operator != (const Frac& secfrac) const {
        return !(*this == secfrac);
    }
    Frac& operator++();
    Frac operator++(int);

    friend istream& operator >> (istream& in, Frac& fr);
    friend ostream& operator << (ostream& os, const Frac& fr);
};


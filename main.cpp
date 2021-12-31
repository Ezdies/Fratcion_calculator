#include <iostream>
#include <numeric>

class Rational {
    int m_numerator;
    int m_denominator;

public:
    Rational(const int &numerator, const int &denominator) : m_numerator(numerator), m_denominator(denominator) {
        if (denominator == 0) throw std::runtime_error("0 w mianowniku");
    }

    Rational(const int &constant, const int &numerator, const int &denominator) : m_numerator(numerator),
                                                                                  m_denominator(denominator) {
        if (denominator == 0) throw std::runtime_error("0 w mianowniku");
        m_numerator += constant * denominator;
    }

    int getNumerator() const { return m_numerator; };

    int getDenominator() const { return m_denominator; };

};

void printExcluded(const Rational &rational) {
    const int excluded = rational.getNumerator() / rational.getDenominator();
    if (rational.getNumerator() >= rational.getDenominator()) {
        std::cout << excluded << " "
                  << rational.getNumerator() - excluded * rational.getDenominator();
        std::cout << '/' << rational.getDenominator();
    } else {
        std::cout << rational.getNumerator() << '/' << rational.getDenominator();
    }
}

std::ostream &printExcluded(std::ostream &os, const Rational &rational) {
    const int excluded = rational.getNumerator() / rational.getDenominator();
    if (rational.getNumerator() >= rational.getDenominator()) {
        os << excluded << " "
           << rational.getNumerator() - excluded * rational.getDenominator()
           << '/' << rational.getDenominator();
    } else {
        os << rational.getNumerator() << '/' << rational.getDenominator();
    }
    return os;
}

Rational reduce(const int numerator, const int denominator) {
    const int gcd = std::gcd(numerator, denominator);
    return {numerator / gcd, denominator / gcd};
}

Rational operator+(const Rational &a, const Rational &b) {
    const int denominator = std::lcm(a.getDenominator(), b.getDenominator());
    const int numerator = a.getNumerator() * (denominator / a.getDenominator()) +
                          b.getNumerator() * (denominator / b.getDenominator());
    return reduce(numerator, denominator);
}

Rational operator-(const Rational &a, const Rational &b) {
    const int denominator = std::lcm(a.getDenominator(), b.getDenominator());
    const int numerator = a.getNumerator() * (denominator / a.getDenominator()) -
                          b.getNumerator() * (denominator / b.getDenominator());
    return reduce(numerator, denominator);
}

Rational operator*(const Rational &a, const Rational &b) {
    return reduce(a.getNumerator() * b.getNumerator(), a.getDenominator() * b.getDenominator());
}

Rational operator/(const Rational &a, const Rational &b) {
    return reduce(a.getNumerator() * b.getDenominator(), a.getDenominator() * b.getNumerator());
}

std::ostream &operator<<(std::ostream &os, const Rational &rational) {
    return printExcluded(os, rational);
}

bool operator==(const Rational &a, const Rational &b) {
    return a.getNumerator() == b.getNumerator() && a.getDenominator() == b.getDenominator();
}

double toDouble(const Rational &rational) {
    return 1.0 * rational.getNumerator() / rational.getDenominator();
}

int main() {
    Rational rational1(3,4, 5);
    Rational rational2(9,2,5);
    Rational rational3( 7, 2);

    std::cout << rational1 + rational2 << std::endl;
    std::cout << (rational1 == rational2) << std::endl;
    std::cout << toDouble(rational3) << std::endl;
    printExcluded(rational3);

    return 0;
}

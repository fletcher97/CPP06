#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>
#include <ios>

#include "Converter.hpp"


/////////////
// Helpers //
/////////////

static size_t
len(const char *str) {
	size_t ret = -1;
	while (str[++ret]);
	return ret;
}

static bool
isPrint(const char c) {
	return (c >= 32 && c < 127);
}

static bool
isDigit(const char c) {
	return (c >= '0' && c <= '9');
}

static bool
cmp(const char *s1, const char *s2) {
	int i = 0;
	for (; s1[i] && s1[i] == s2[i]; i++);
	return (s1[i] == s2[i]);
}

///////////////////
// Type Checkers //
///////////////////

static bool
isChar(const char* s) {
	return (len(s) == 3 &&
		s[0] == '\'' &&
		s[2] == '\'' &&
		isPrint(s[1]));
}

static bool
isNan(const char* s) {
	return (cmp(s, "nan") || cmp(s, "nanf"));
}

static bool
isInf(const char* s) {
	return (cmp(s, "+inf") || cmp(s, "+inff")
		|| cmp(s, "-inf") || cmp(s, "-inff"));
}

static bool
isFloat(const char* s) {
	bool dot = false;
	bool now = false;
	for (size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0; i < len(s); i++) {
		if (s[i] == '.' && !dot && i > 0 && (s[i-1] != '+' && s[i-1] != '-')) {
			dot = true;
			now = true;
			continue;
		}
		if ((!isDigit(s[i]) && i < (len(s) - 1)) || (!isDigit(s[i]) && s[i] != 'f' && i == (len(s) - 1)) || (s[i] == 'f' && now))
			return false;
		now = false;
	}
	return dot && s[len(s) - 1] == 'f';
}

static bool
isDouble(const char* s) {
	bool dot = false;
	for (size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0; i < len(s); i++) {
		if (s[i] == '.' && !dot && i > 0 && (s[i-1] != '+' && s[i-1] != '-')) {
			dot = true;
			continue;
		}
		if (!std::isdigit(s[i]))
			return false;
	}
	return dot && s[len(s) - 1] != '.';
}

static bool
isInt(const char* s) {
	for (size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0; i < len(s); i++)
		if (!isDigit(s[i]))
			return false;
	return true;
}

static bool
isValid(const char* s) {
	return (isInf(s) || isNan(s) || isChar(s) || isInt(s) || isFloat(s) || isDouble(s));
}

////////////////////////////
// Constructor/Destructor //
////////////////////////////

Converter::Converter(const char* str) throw (std::invalid_argument, std::runtime_error) {
	if (str == NULL || !str[0])
		throw std::invalid_argument("Converter initialized with null pointer or empty string");
	if (!isValid(str)) {
		throw std::invalid_argument("Converter initialized with invalid string");
	}

	if (isInf(str)) {
		this->t = Inf;
		this->d.infnan = new char[len(str) + 1];
		for (size_t i = 0; i < len(str); i++)
			this->d.infnan[i] = str[i];
		this->d.infnan[len(str)] = '\0';
	} else if (isNan(str)) {
		this->t = Nan;
		this->d.infnan = new char[len(str) + 1];
		for (size_t i = 0; i < len(str); i++)
			this->d.infnan[i] = str[i];
		this->d.infnan[len(str)] = '\0';
	} else if (isChar(str)) {
		this->t = Char;
		this->d.c = str[1];
	} else if (isInt(str)) {
		this->t = Int;
		long tmp = std::strtol(str, NULL, 10);
		if (tmp > std::numeric_limits<int>::max())
			throw std::invalid_argument("int argument overflows");
		else if (tmp < std::numeric_limits<int>::min())
			throw std::invalid_argument("int argument underflows");
		this->d.i = static_cast<int>(tmp);
	} else if (isFloat(str)) {
		this->t = Float;
		this->d.f = std::strtof(str, NULL);
		if (this->d.f == HUGE_VALF)
			throw std::invalid_argument("int argument overflows");
		else if (this->d.f == -HUGE_VALF)
			throw std::invalid_argument("int argument underflows");
	} else if (isDouble(str)) {
		this->t = Double;
		this->d.d = std::strtod(str, NULL);
		if (this->d.d == HUGE_VAL)
			throw std::invalid_argument("int argument overflows");
		else if (this->d.d == -HUGE_VAL)
			throw std::invalid_argument("int argument underflows");
	} else
		throw std::runtime_error("Converter initialization failed due to an error getting type of argument passed");
}

Converter::Converter(const Converter& other) {
	this->t = other.t;
	this->d = other.d;
}

Converter*
Converter::operator=(const Converter& other) {
	if (this->t == Inf || this->t == Nan)
		delete[] this->d.infnan;
	this->t = other.t;
	if (this->t == Inf || this->t == Nan) {
		this->d.infnan = new char[len(other.d.infnan) + 1];
		for (size_t i = 0; i < len(other.d.infnan); i++)
			this->d.infnan[i] = other.d.infnan[i];
		this->d.infnan[len(other.d.infnan)] = '\0';
	} else
		this->d = other.d;
	return this;
}

Converter::~Converter() {
	if (this->t == Inf || this->t == Nan)
		delete[] this->d.infnan;
}

//////////////
// Printers //
//////////////

void
Converter::printChar() const {
	if (this->t == Inf || this->t == Nan)
		std::cout << "char: impossible => inf/nan" << std::endl;
	else if (this->t == Char)
		std::cout << "char: '" << this->d.c << "'" << std::endl;
	else if (this->t == Int) {
		if (this->d.i < 0)
			std::cout << "char: impossible => underflow" << std::endl;
		else if (this->d.i > 127)
			std::cout << "char: impossible => overflow" << std::endl;
		else if (this->d.i < 32 || this->d.i == 127)
			std::cout << "char: non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(this->d.i) << "'" << std::endl;
	} else if (this->t == Float) {
		if (this->d.f < 0)
			std::cout << "char: impossible => underflow" << std::endl;
		else if (this->d.f > 127)
			std::cout << "char: impossible => overflow" << std::endl;
		else if (this->d.f < 32 || this->d.f == 127)
			std::cout << "char: non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(this->d.f) << "'" << std::endl;
	} else if (this->t == Double) {
		if (this->d.d < 0)
			std::cout << "char: impossible => underflow" << std::endl;
		else if (this->d.d > 127)
			std::cout << "char: impossible => overflow" << std::endl;
		else if (this->d.d < 32 || this->d.d == 127)
			std::cout << "char: non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(this->d.d) << "'" << std::endl;
	}
}

void
Converter::printInt() const {
	if (this->t == Inf || this->t == Nan)
		std::cout << "int: impossible => inf/nan" << std::endl;
	else if (this->t == Char)
		std::cout << "int: " << static_cast<int>(this->d.c) << std::endl;
	else if (this->t == Int)
		std::cout << "int: " << this->d.i << std::endl;
	else if (this->t == Float) {
		if (this->d.f <= std::numeric_limits<int>::min())
			std::cout << "int: impossible => underflow" << std::endl;
		else if (this->d.f >= std::numeric_limits<int>::max())
			std::cout << "int: impossible => overflow" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(this->d.f) << std::endl;
	} else if (this->t == Double) {
		if (this->d.d <= std::numeric_limits<int>::min())
			std::cout << "int: impossible => underflow" << std::endl;
		else if (this->d.d >= std::numeric_limits<int>::max())
			std::cout << "int: impossible => overflow" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(this->d.d) << std::endl;
	}
}

void
Converter::printFloat() const
{
	std::cout.precision(std::numeric_limits<float>::digits10);
	std::cout << std::fixed;
	if (this->t == Inf)
		std::cout << (this->d.infnan[0] == '-' ? "float: -" : "float: +") << std::numeric_limits<float>::infinity() << 'f' << std::endl;
	else if (this->t == Nan)
		std::cout << "float: " << nanf("") << 'f' << std::endl;
	else if (this->t == Char)
		std::cout << "float: " << static_cast<float>(this->d.c) << "f" << std::endl;
	else if (this->t == Int)
		std::cout << "float: " << static_cast<float>(this->d.i) << "f" << std::endl;
	else if (this->t == Float)
		std::cout << "float: " << this->d.f << "f" << std::endl;
	else if (this->t == Double) {
		if (this->d.d <= -std::numeric_limits<float>::max())
			std::cout << "float: impossible => underflow" << std::endl;
		else if (this->d.d >= std::numeric_limits<float>::max())
			std::cout << "float: impossible => overflow" << std::endl;
		else
			std::cout << "float: " << static_cast<float>(this->d.d) << "f" << std::endl;
	}
}

void
Converter::printDouble() const
{
	std::cout.precision(std::numeric_limits<double>::digits10);
	std::cout << std::fixed;
	if (this->t == Inf)
		std::cout << (this->d.infnan[0] == '-' ? "double: -" : "double: +") << std::numeric_limits<double>::infinity() << std::endl;
	else if (this->t == Nan)
		std::cout << "double: " << nan("") << std::endl;
	else if (this->t == Char)
		std::cout << "double: " << static_cast<double>(this->d.c) << std::endl;
	else if (this->t == Int)
		std::cout << "double: " << static_cast<double>(this->d.i) << std::endl;
	else if (this->t == Float)
		std::cout << "double: " << static_cast<double>(this->d.f) << std::endl;
	else if (this->t == Double)
		std::cout << "double: " << this->d.d << std::endl;
}

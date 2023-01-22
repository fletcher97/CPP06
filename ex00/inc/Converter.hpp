#if !defined(CONVERTER_HPP)
#define CONVERTER_HPP

#include <stdexcept>


class Converter
{
public:
	enum Type {
		Inf = 0, Nan, Char, Int, Float, Double
	};

	union Data
	{
		char c;
		int i;
		float f;
		double d;
		char *infnan;
	};

	Type t;
	Data d;

public:
	Converter(const char* str) throw (std::invalid_argument, std::runtime_error);
	Converter(const Converter& other);
	Converter* operator=(const Converter& other);
	~Converter();

	// Printers
	void printChar() const;
	void printInt() const;
	void printFloat() const;
	void printDouble() const;
};

#endif // CONVERTER_HPP

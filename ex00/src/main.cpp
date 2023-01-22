#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include "Converter.hpp"

static void
test(std::string str)
{
	std::cout << "Testing: \"" << str << "\"" << std::endl;
	try {
		Converter c(str.c_str());
		c.printChar();
		c.printInt();
		c.printFloat();
		c.printDouble();
	} catch (std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

void
testEmpty() {
	std::cout << std::endl << "TESTING: Empty" << std::endl << std::endl << std::endl;

	test("");
}

void
testInfs() {
	std::cout << std::endl << "TESTING: Infs" << std::endl << std::endl << std::endl;

	test("+inf");
	test("+inff");

	test("-inf");
	test("-inff");

	test("inf");
	test("inff");

	test("0inf");
	test("0inff");

	test("+0inf");
	test("+0inff");

	test("-0inff");
	test("-0inf");
}

void
testNans() {
	std::cout << std::endl << "TESTING: Nans" << std::endl << std::endl << std::endl;

	test("nan");
	test("nanf");

	test("+nan");
	test("+nanf");

	test("-nan");
	test("-nanf");

	test("0nan");
	test("+0nan");
	test("0+nan");
	test("-0nan");
	test("0-nan");
	test("nan0");
	test("+nan0");
	test("-nan0");
}

void
testChars() {
	std::cout << std::endl << "TESTING: Chars" << std::endl << std::endl << std::endl;

	test("' '");
	test("'>'");
	test("'A'");
	test("'Z'");
	test("'a'");
	test("'z'");
	test("'*'");
	test("'0'");
	test("'9'");
	test("'~'");
}

void
testInts() {
	std::cout << std::endl << "TESTING: Ints" << std::endl << std::endl << std::endl;

	test("0");
	test("+0");
	test("-0");
	test("0000");
	test("+0000");
	test("-0000");
	test("1");
	test("+1");
	test("-1");
	test("0001");
	test("+0001");
	test("-0001");
	test("90");
	test("2147483647");
	test("2147483648");
	test("-2147483648");
	test("-2147483649");
}

void
testFloats() {
	std::cout << std::endl << "TESTING: Floats" << std::endl << std::endl << std::endl;

	test("0.0f");
	test("+0.0f");
	test("-0.0f");

	test("0000.0f");
	test("+0000.0f");
	test("-0000.0f");

	test("0.0000f");
	test("+0.0000f");
	test("-0.0000f");

	test("0.0000001f");
	test("+0.0000001f");
	test("-0.0000001f");

	test("1.0f");
	test("+1.0f");
	test("-1.0f");

	test("1.0000f");
	test("+1.0000f");
	test("-1.0000f");

	test("0001.0f");
	test("+0001.0f");
	test("-0001.0f");

	test("42.0f");
	test("+42.0f");
	test("-42.0f");

	test("42.1f");
	test("+42.1f");
	test("-42.1f");

	test("999999.0f");
	test("+999999.0f");
	test("-999999.0f");

	test("1000000.0f");
	test("+1000000.0f");
	test("-1000000.0f");

	test("999999999999999999999999999999.000000f");
	test("-999999999999999999999999999999.000000f");

	test("999999999999999999999999999999999999999.000000f");
	test("-999999999999999999999999999999999999999.000000f");
}

void
testDoubles() {
	std::cout << std::endl << "TESTING: Doubles" << std::endl << std::endl << std::endl;

	test("0.0");
	test("+0.0");
	test("-0.0");

	test("0000.0");
	test("+0000.0");
	test("-0000.0");

	test("0.0000");
	test("+0.0000");
	test("-0.0000");

	test("1.0");
	test("+1.0");
	test("-1.0");

	test("1.0000");
	test("+1.0000");
	test("-1.0000");

	test("0001.0");
	test("+0001.0");
	test("-0001.0");

	test("42.0");
	test("+42.0");
	test("-42.0");

	test("999999.0");
	test("+999999.0");
	test("-999999.0");

	test("1000000.0");
	test("+1000000.0");
	test("-1000000.0");

	test("999999999999999999999999999999.000000");
	test("-999999999999999999999999999999.000000");

	test("999999999999999999999999999999999999999.000000");
	test("-999999999999999999999999999999999999999.000000");

	test("999999999999999999999999999999999999999999999999999999999999999999999999999999.000000");
	test("-999999999999999999999999999999999999999999999999999999999999999999999999999999.000000");

	test("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.000000");
	test("-999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.000000");
}

void
testBadInput() {
	std::cout << std::endl << "TESTING: Bad input" << std::endl << std::endl << std::endl;

	test("a");
	test(".");
	test("0x42");
	test("0.f");
	test(".0f");
	test("1o1");
	test("hello");
	test("0x0");
	test("0f");
}

void
runTests() {
	testEmpty();
	testInfs();
	testNans();
	testChars();
	testInts();
	testFloats();
	testDoubles();
	testBadInput();
}

int main(int ac, char *av[])
{
	if (ac > 1)
		for (int i = 1; i < ac; i++)
			test(av[i]);
	else {
		runTests();
		// testInfs();
		// testNans();
	}

}

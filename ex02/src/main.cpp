#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Classes.hpp"

Base*
generate() {
	std::srand(std::time(NULL));
	int classToGen = std::rand() % 3;
	switch (classToGen)
	{
	case 0:
		std::cout << "Generating class A" << std::endl;
		return new A();
		break;
	case 1:
		std::cout << "Generating class B" << std::endl;
		return new B();
		break;
	case 2:
		std::cout << "Generating class C" << std::endl;
		return new C();
		break;
	}
	return 0;
}

void
identify(Base* base) {
	A* a = dynamic_cast<A*>(base);
	if (a != 0) {
		std::cout << "Class is A" << std::endl;
		return;
	}
	B* b = dynamic_cast<B*>(base);
	if (b != 0) {
		std::cout << "Class is B" << std::endl;
		return;
	}
	C* c = dynamic_cast<C*>(base);
	if (c != 0) {
		std::cout << "Class is C" << std::endl;
		return;
	}
	std::cout << "Class is not A, B, or C" << std::endl;
}

void
identify(Base& base) {
	try {
		A& a = dynamic_cast<A&>(base);
		(void) a;
		std::cout << "Class is A" << std::endl;
		return;
	} catch(const std::exception& e) {}
	try {
		B& b = dynamic_cast<B&>(base);
		(void) b;
		std::cout << "Class is B" << std::endl;
		return;
	} catch(const std::exception& e) {}
	try {
		C& c = dynamic_cast<C&>(base);
		(void) c;
		std::cout << "Class is C" << std::endl;
		return;
	} catch(const std::exception& e) {}
	std::cout << "Class is not A, B, or C" << std::endl;
}

int
main() {
	Base *b = generate();
	std::cout << "Pointer detection:   ";
	identify(b);
	std::cout << "Reference detection: ";
	identify(*b);
	delete b;
}

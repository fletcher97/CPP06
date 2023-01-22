#include <iostream>
// #include <cstdint>
#include <stdint.h>

#include "Data.hpp"

std::ostream&
operator <<(std::ostream& out, const Data *d) {
	out << static_cast<const void*>(d) << " - {a: " << d->a << ", b: " << d->b << ", c: " << d->c << "}" ;
	return out;
}

uintptr_t
serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*
deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

int main() {

	Data d;
	d.a = 42;
	d.b = 'A';
	d.c = 0;

	std::cout << "Original: " << &d << std::endl;

	uintptr_t raw = serialize(&d);
	std::cout << "Raw: " << raw << std::endl;

	Data *newPtr = deserialize(raw);
	std::cout << "New: " << newPtr << std::endl;

}

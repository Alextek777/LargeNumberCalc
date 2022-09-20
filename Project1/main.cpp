#include <iostream>
#include "CustomInt.h"

int main() {
	CustomInt value1("10212");
	CustomInt value2("100");


	value1 /= value2;

	std::cout << value1 << std::endl;

	return 0;
}
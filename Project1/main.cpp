#include <iostream>
#include "CustomInt.h"

int main() {
	CustomInt value1("52345234523");
	CustomInt value2("23452345234");

	long long v1 = 52345234523;
	long long v2 = 23452345234;

	for (int i = 0; i < 10000; i++)
		value1 += value2;

	for (int i = 0; i < 10000; i++)
		v1 += v2;


	std::cout << value1 << std::endl;

	return 0;
}
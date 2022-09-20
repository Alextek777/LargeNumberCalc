#include <iostream>
#include "CustomInt.h"

#include <random>

bool check_addition() {
	for (int i = 0; i < 120; i++) {
		long standard_result;
		long standard_value1 = rand() % 2000000 - 1000000;
		long standard_value2 = rand() % 2000000 - 1000000;

		CustomInt custom_result;
		CustomInt custom_value1(standard_value1);
		CustomInt custom_value2(standard_value2);

		standard_result = standard_value1 + standard_value2;
		custom_result = custom_value1 + standard_value2;

		if (standard_result != custom_result) {
			std::cout << "Error! : " << standard_value1 << " + " << standard_value2 << " != " << custom_result << std::endl;
			return false;
		}
	}
	std::cout << "Addition test successfully passed" << std::endl;
	return true;
}

bool check_substraction() {
	for (int i = 0; i < 120; i++) {
		long standard_result;
		long standard_value1 = rand() % 2000000 - 1000000;
		long standard_value2 = rand() % 2000000 - 1000000;

		CustomInt custom_result;
		CustomInt custom_value1(standard_value1);
		CustomInt custom_value2(standard_value2);

		standard_result = standard_value1 - standard_value2;
		custom_result = custom_value1 - standard_value2;

		if (standard_result != custom_result) {
			std::cout << "Error! : " << standard_value1 << " - " << standard_value2 << " != " << custom_result << std::endl;
			return false;
		}
	}
	std::cout << "Substraction test successfully passed" << std::endl;
	return true;
}

bool check_multiplication() {
	for (int i = 0; i < 120; i++) {
		long standard_result;
		long standard_value1 = rand() % 2000 - 1000;
		long standard_value2 = rand() % 2000 - 1000;

		CustomInt custom_result;
		CustomInt custom_value1(standard_value1);
		CustomInt custom_value2(standard_value2);

		standard_result = standard_value1 * standard_value2;
		custom_result = custom_value1 * standard_value2;

		if (standard_result != custom_result) {
			std::cout << "Error! : " << standard_value1 << " * " << standard_value2 << " != " << custom_result << std::endl;
			return false;
		}
	}
	std::cout << "Multiplication test successfully passed" << std::endl;
	return true;
}

bool check_division() {
	for (int i = 0; i < 120; i++) {
		long standard_result;
		long standard_value1 = rand() % 20000000 - 10000000;
		long standard_value2 = rand() % 20000000 - 10000000;

		CustomInt custom_result;
		CustomInt custom_value1(standard_value1);
		CustomInt custom_value2(standard_value2);

		standard_result = standard_value1 / standard_value2;
		custom_result = custom_value1 / standard_value2;

		if (standard_result != custom_result) {
			std::cout << "Error! : " << standard_value1 << " / " << standard_value2 << " != " << custom_result << std::endl;
			return false;
		}
	}
	std::cout << "Division test successfully passed" << std::endl;
	return true;
}

bool check_operations() {
	if (check_addition() && check_substraction() && check_multiplication() && check_division())
		return true;
	return false;
}

int main() {
	srand(1525);
	
	if (!check_operations())
		return -1;

	return 0;
}
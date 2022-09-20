#include <iostream>
#include <random>

#include "CustomInt.h"
#include "Checks.h"



int main() {	
	if (CustomChecks::check_operations() == false)
		return -1;

	return 0;
}
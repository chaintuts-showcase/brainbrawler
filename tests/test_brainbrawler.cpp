/* This file contains simpel unit tests for the brainbrawler library
*
* Author: Josh McIntyre
*/
#include "attack.h"
#include "test_brainbrawler.h"

// Test iteration calculations
bool test_attack()
{
	std::string address = "167pV6UnXfYe6DFyxubM45rWVeW1uA6bF7";
	std::string passphrase = "rockyou";
	
	AttackResult result = attack(address);
	
	if (result.found == true && result.passphrase == passphrase)
	{
		return true;
	}
	
	return false;
}

// The main entry point for the unit tests
int main(int argc, char* argv[])
{
	int tests = 1;
	bool results[1];

	bool res_attack = test_attack();
	results[0] = res_attack;
	
	int tests_passed = 0;
	int tests_failed = 0;
	for (int i = 0; i < tests; i++)
	{
		if (results[i] == true)
		{
			tests_passed++;
		}
		else
		{
			tests_failed++;
		}
	}
	
	std::cout << "-----" << std::endl;
	std::cout << "Tests passed: " << tests_passed << std::endl;
	std::cout << "Tests failed: " << tests_failed << std::endl;
	
	return 0;
}
/* This file contains code for cracking  Bitcoin brainwallets with a dictionary attack
* This file contains the main entry point for the program
* 
* Author: Josh McIntyre
*/

#include "brainbrawler.h"

// This function is the main entry point for the program
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		output_help();
		exit(1);
	}

	std::string address = std::string(argv[1]);

	AttackResult result = attack(address);
	
	if (result.found == true)
	{
		std::cout  << "Password found: " << result.passphrase << std::endl;
	}
	else
	{
		std::cout  << "No password found for the specified brainwallet" << std::endl;
	}

	return 0;
}

void output_help()
{
	std::cout << "Usage: ./brainbrawler.exe <bitcoin address>";
}


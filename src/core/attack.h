/* This file contains function definitions and includes for the dictionary attack code
*
* Author: Josh McIntyre
*/

#include <iostream>
#include <fstream>
#include "cryptops.h"

const std::string WORDLIST_FILENAME = "./bin/wordlist_sample.txt";

struct AttackResult
{
	bool found;
	std::string passphrase;
	std::string address;
};

AttackResult attack(std::string address);
void output_help();

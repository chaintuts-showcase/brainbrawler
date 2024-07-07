/* This file contains code for cracking  Bitcoin brainwallets with a dictionary attack
* 
* Author: Josh McIntyre
*/

#include "attack.h"

// Conduct a dictionary attack on possible brainwallets
AttackResult attack(std::string address)
{
	AttackResult result;

	std::string word;
	std::ifstream wordlist_file(WORDLIST_FILENAME);
	while (std::getline(wordlist_file, word))
	{
		std::string candidate_address = generate_brainwallet(word);
		
		if (address == candidate_address)
		{
			result.found = true;
			result.passphrase = word;
			result.address = candidate_address;
			
			return result;
		}	
	}
	
	result.found = false;
	result.passphrase = "";
	result.address = "";
	
	return result;
}

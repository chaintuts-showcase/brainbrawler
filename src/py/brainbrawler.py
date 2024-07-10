# This file contains code for cracking Bitcoin brainwallets with a dictionary attack
#
# Author: Josh McIntyre
#
import argparse

import bitaddrlib

WORDLIST_FILENAME = "wordlist_sample.txt"

class AttackResult:
    
    def __init__(self, found, passphrase, address):
        
        self.found = found
        self.passphrase = passphrase
        self.address = address

# Run a dictionary attack on possible brainwallets
def attack(address):

    bitaddr = bitaddrlib.BitAddr()

    with open(WORDLIST_FILENAME) as f:
        for word in f:
            word = word.strip()
            candidate_address = bitaddr.generate_brainwallet(word)
            if candidate_address == address:
                result = AttackResult(True, word, candidate_address)

                return result
        
        result = AttackResult(False, "", "")

        return result

# The main entry point for the program
def main():

    parser = argparse.ArgumentParser(description="Run a dictionary attack on a suspected Bitcoin brainwallet")
    parser.add_argument("address", type=str, help="The address to run the attack on")
    args = parser.parse_args()
    
    result = attack(args.address)
    
    if result.found:
        print(f"Password found: {result.passphrase}")
    else:
        print("No password found for the specified brainwallet")

if __name__ == "__main__":
	main()
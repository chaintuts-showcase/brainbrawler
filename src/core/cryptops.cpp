/* This file contains the underlying implementation for brainwallet generation functions
*
* Author: Josh McIntyre
*/

#include "cryptops.h"

size_t ADDRESS_LENGTH_NC = 40;
size_t PRIVKEY_WIF_LENGTH_NC = 70;

// Calculate the secp256k1 public key from the private key
void pubkey_from_privkey(unsigned char privkey[SHA256_DIGEST_LENGTH],  unsigned char pubkey[PUBKEY_65_LENGTH])
{
	 ecdsa_get_public_key65(&secp256k1, (uint8_t*) privkey,
                            (uint8_t*) pubkey);
}

// Generate address from pubkey
void address_from_pubkey(const unsigned char pubkey[PUBKEY_65_LENGTH], unsigned char version_prefix, unsigned char address[ADDRESS_LENGTH])
{
	// First, "double hash" the public key
	unsigned char round_1[SHA256_DIGEST_LENGTH];
	unsigned char round_2[RIPEMD160_DIGEST_LENGTH];

	sha256_Raw((uint8_t*) pubkey, PUBKEY_65_LENGTH, (uint8_t*) round_1);
	ripemd160((uint8_t*) round_1, SHA256_DIGEST_LENGTH, (uint8_t*) round_2);

	// Add the version specifier
	unsigned char raw_address_nocheck[RAW_ADDRESS_NOCHECK_LENGTH];
	raw_address_nocheck[0] = version_prefix;
	memcpy(raw_address_nocheck + 1, round_2, RIPEMD160_DIGEST_LENGTH);

	// Generate a checksum
	unsigned char check_round_1[SHA256_DIGEST_LENGTH];
	unsigned char check_round_2[SHA256_DIGEST_LENGTH];
	unsigned char checksum[CHECKSUM_LENGTH];

	sha256_Raw((uint8_t*) raw_address_nocheck, RAW_ADDRESS_NOCHECK_LENGTH, check_round_1);
	sha256_Raw((uint8_t*) check_round_1, SHA256_DIGEST_LENGTH, check_round_2);
	memcpy(checksum, check_round_2, CHECKSUM_LENGTH);


	// Finalize the raw address
	// 1 byte for the version string
	// 20 bytes for the pubkey hash
	// 4 bytes for the checksum
	unsigned char raw_address_check[RAW_ADDRESS_CHECK_LENGTH];
	memcpy(raw_address_check, raw_address_nocheck, RAW_ADDRESS_NOCHECK_LENGTH);
	memcpy(raw_address_check + RAW_ADDRESS_NOCHECK_LENGTH, checksum, CHECKSUM_LENGTH);

	// Base58 encode
	b58enc((char*) address, &ADDRESS_LENGTH_NC, raw_address_check, RAW_ADDRESS_CHECK_LENGTH);
}

void privkey_wif_from_raw(unsigned char* privkey_raw, unsigned char version_prefix, unsigned char* privkey)
{
	
	// Add the version specifierd
	unsigned char raw_privkey_nocheck[RAW_PRIVKEY_NOCHECK_LENGTH];
	raw_privkey_nocheck[0] = version_prefix;
	memcpy(raw_privkey_nocheck + 1, privkey_raw, SHA256_DIGEST_LENGTH);

	// Generate a checksum
	unsigned char check_round_1[SHA256_DIGEST_LENGTH];
	unsigned char check_round_2[SHA256_DIGEST_LENGTH];
	unsigned char checksum[CHECKSUM_LENGTH];

	sha256_Raw((uint8_t*) raw_privkey_nocheck, RAW_PRIVKEY_NOCHECK_LENGTH, check_round_1);
	sha256_Raw((uint8_t*) check_round_1, SHA256_DIGEST_LENGTH, check_round_2);
	memcpy(checksum, check_round_2, CHECKSUM_LENGTH);


	// Finalize the raw WIF format privkey
	// 1 byte for the version string - 0x80 for mainneti BTC/BCH
	// 32 bytes for the raw private key data
	// 4 bytes for the checksum
	unsigned char raw_privkey_check[RAW_PRIVKEY_CHECK_LENGTH];
	memcpy(raw_privkey_check, raw_privkey_nocheck, RAW_PRIVKEY_NOCHECK_LENGTH);
	memcpy(raw_privkey_check + RAW_PRIVKEY_NOCHECK_LENGTH, checksum, CHECKSUM_LENGTH);

	// Base58 encode
	b58enc((char*) privkey, &PRIVKEY_WIF_LENGTH_NC, raw_privkey_check, RAW_PRIVKEY_CHECK_LENGTH);
}

// Generate a Bitcoin address given the raw private key bits
std::string generate_bitcoin_address(unsigned char* passphrase_hash)
{
	// Generate the public key from the private key bytes
	unsigned char pubkey[PUBKEY_65_LENGTH];
	pubkey_from_privkey(passphrase_hash, pubkey);

	// Generate the address from the public key
	// This address can use the legacy base58check encoding valid
	// in both BTC and BCH, or BCH cashaddr
	unsigned char address_char[ADDRESS_LENGTH];
	address_from_pubkey(pubkey, BTC_ADDR_PREFIX, address_char);
	
	const char* address_tmp = reinterpret_cast<const char*>(address_char);
	std::string address = std::string(address_tmp);

	return address;	
}

/* Generate a Bitcoin address from a brainwallet
* This method uses one round of SHA-256 to generate the key bitset
*/
std::string generate_brainwallet(std::string passphrase)
{
	
	// Generate the SHA-256 hash of the passphrase to use as the private key
	unsigned char* passphrase_raw = new unsigned char[passphrase.size()+1];
	char* passphrase_raw_tmp = new char[passphrase.size()+1];
	unsigned char passphrase_hash[SHA256_DIGEST_LENGTH];
	
	strcpy(passphrase_raw_tmp, passphrase.c_str());
	passphrase_raw = reinterpret_cast<unsigned char*>(passphrase_raw_tmp);
	sha256_Raw((uint8_t*) passphrase_raw, passphrase.size(), (uint8_t*) passphrase_hash);
	
	std::string address = generate_bitcoin_address(passphrase_hash);
	
	delete passphrase_raw;
	delete passphrase_raw_tmp;
	
	return address;
}


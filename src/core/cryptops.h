/* Function prototypes and include for cryptographic operations like generating Bitcoin keypairs
*
* Author: Josh McIntyre
*/
#include <string.h>
#include <sha2.h>
#include <ripemd160.h>
#include <secp256k1.h>
#include <ecdsa.h>
#include <rand.h>
#include <base58.h>
#include <stdio.h>
#include <string>

// Some size definitions we'll need to implement the pubkey -> address conversion
const size_t RAW_ADDRESS_NOCHECK_LENGTH = 21;
const size_t RAW_ADDRESS_CHECK_LENGTH = 25;
const size_t PUBKEY_65_LENGTH = 65;
const size_t CHECKSUM_LENGTH = 4;
const size_t ADDRESS_LENGTH = 40;
const size_t RAW_PRIVKEY_NOCHECK_LENGTH = 33;
const size_t RAW_PRIVKEY_CHECK_LENGTH = 37;
const size_t PRIVKEY_WIF_LENGTH = 70;

const unsigned char BTC_ADDR_PREFIX = 0x0;
const unsigned char BTC_WIF_PREFIX = 0x80;

std::string generate_bitcoin_address(unsigned char* passphrase_raw);
std::string generate_brainwallet(std::string passphrase);

void pubkey_from_privkey(unsigned char privkey[SHA256_DIGEST_LENGTH],  unsigned char pubkey[PUBKEY_65_LENGTH]);
void address_from_pubkey(const unsigned char pubkey[PUBKEY_65_LENGTH], unsigned char version_prefix, unsigned char address[ADDRESS_LENGTH]);
void privkey_wif_from_raw(unsigned char* privkey_raw, unsigned char version_prefix, unsigned char* privkey);

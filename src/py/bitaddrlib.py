# This file contains code for generating a Bitcoin address/private key
#
# Author: Josh McIntyre
#
import os
import hashlib

from ecpy.curves import Curve,Point
from ecpy.keys import ECPublicKey, ECPrivateKey
from ecpy.ecdsa import ECDSA
import base58
from ripemd import ripemd160
import base58

class BitAddr:

    # Class level constants

    # Regardless of system endianness (which is little on Adafruit M4),
    # interpret hash outputs, pubkey bytes left-to-right big endian
    ENDIAN = "big"

    # Cryptocurrency prefixes, etc. for keys, addresses
    BTC_PUBKEY_PREFIX = 0x04 # Uncompressed public key prefix
    BTC_WIF_PREFIX = 0x80
    BTC_ADDRESS_PREFIX = 0x00
    
    # Generate a Bitcoin brainwallet from passphrase
    def generate_brainwallet(self, passphrase):
        
        privkey_raw = hashlib.sha256(passphrase.encode()).digest()
        
        address = self.generate_address_btc_privkey(privkey_raw)
        
        return address
    
    # Generate an address with the given private key bits
    def generate_address_btc_privkey(self, privkey_raw):
        
        pubkey_raw = self._generate_pubkey_raw(privkey_raw)
        
        address = self._generate_address(pubkey_raw, self.BTC_ADDRESS_PREFIX)
        
        return address

    # Generate a private key, address pair for Bitcoin
    # Returns an address, privkey tuple
    def generate_address_privkey_btc(self):

        key_raw = self._generate_privkey_raw()
        pubkey_raw = self._generate_pubkey_raw(key_raw)

        wif = self._generate_privkey_wif(key_raw, self.BTC_WIF_PREFIX)
        address = self._generate_address(pubkey_raw, self.BTC_ADDRESS_PREFIX)

        return (address, wif)

    # Generate the private key from entropy
    def _generate_privkey_raw(self):

        key = os.urandom(32)

        return key

    def _generate_pubkey_raw(self, key_raw):

        key_int = int.from_bytes(key_raw, self.ENDIAN)

        curve = Curve.get_curve("secp256k1")
        ec_privkey = ECPrivateKey(key_int, curve)

        # Generate the public key
        ec_pubkey = ec_privkey.get_public_key()

        pubkey_prefix_bytes = self.BTC_PUBKEY_PREFIX.to_bytes(1, self.ENDIAN)

        pubkey_x_bytes = ec_pubkey.W.x.to_bytes(32, self.ENDIAN)
        pubkey_y_bytes = ec_pubkey.W.y.to_bytes(32, self.ENDIAN)

        # ECPy generates pubkeys with individual points
        # For a Bitcoin uncompressed private key, combine the prefix, x, and y coordinates
        pubkey_bytes = pubkey_prefix_bytes + pubkey_x_bytes + pubkey_y_bytes

        return pubkey_bytes

    # Function for generating the WIF private key
    def _generate_privkey_wif(self, key_raw, wif_prefix):

        # Generate the private key
        wif_prefix_btc_bytes = wif_prefix.to_bytes(1, self.ENDIAN)

        privkey_prefix_bytes = wif_prefix_btc_bytes + key_raw

        wif_checksum_round1 = hashlib.sha256(privkey_prefix_bytes).digest()
        wif_checksum_round2 = hashlib.sha256(wif_checksum_round1).digest()

        wif_raw = privkey_prefix_bytes + wif_checksum_round2[:4]
        wif = base58.b58encode(wif_raw).decode()

        return wif

    # Function for generating a Bitcoin address
    def _generate_address(self, pubkey_raw, address_prefix):

        round1 = hashlib.sha256(pubkey_raw).digest()
        round2 = ripemd160.ripemd160(round1)

        with_prefix = address_prefix.to_bytes(1, self.ENDIAN) + round2

        checksum_round1 = hashlib.sha256(with_prefix).digest()
        checksum_round2 = hashlib.sha256(checksum_round1).digest()
        checksum_length = 4
        checksum_final = checksum_round2[:checksum_length]

        address_raw = with_prefix + checksum_final
        address = base58.b58encode(address_raw).decode()

        return address
# This file contains unit tests for BrainBrawler library functionality
#
# Author: Josh McIntyre
#
import hashlib
import unittest

import brainbrawler

class TestBrainBrawler(unittest.TestCase):

    def test_attack(self):

        address = "167pV6UnXfYe6DFyxubM45rWVeW1uA6bF7"
        
        result = brainbrawler.attack(address)
        
        assert result.found
        assert result.passphrase == "rockyou"
        assert result.address == "167pV6UnXfYe6DFyxubM45rWVeW1uA6bF7"

## General
____________

### Author
* Josh McIntyre

### Website
* jmcintyre.net

### Overview
* BrainBrawler is a tool for running dictionary attacks on Bitcoin brainwallets

## Development
________________

### Git Workflow
* development for bugfixes and new features

### Building
* make build
Build the utility
* make clean
Clean the build directory

### Features
* Run a dictionary attack on a suspected Bitcoin brainwallet address
* Takes an address, and uses a given wordlist file to try possible passphrase -> address combinations
* Report either a found password, or no password found for the address

### Requirements
* Requires a terminal emulator
* Requires Python for the Python version

### Platforms
* Windows
* Linux
* MacOSX

## Usage
____________

### CLI Usage
* Run `brainbrawler.exe <bitcoin address>` to run dictionary attack against the address
* Sample from wordlist: `rockyou` -> `167pV6UnXfYe6DFyxubM45rWVeW1uA6bF7

### Python CLI Usage
* Run `brainbrawler.py <bitcoin address>`

### Unit Tests
* Run `test_brainbrawler.exe`

### Python Unit Tests
* Run  `python3 -m pytest test_brainbrawler.py`

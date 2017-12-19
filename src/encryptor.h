#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>
#include <memory>
#include <iostream>
#include "util.h"
#include "keygenerator.h"
#include <bitset> // bitset<64>(str.c_str())
#include <chrono>

using namespace std;
typedef unsigned int uint;

class Encryptor
{
 public:

	Encryptor(string& inputBlock);
	~Encryptor();
	unique_ptr<string> getCipherText();
	KeyGenerator * getKeyGenerator();

 private:
		string key;
		string permutedBlock;
		string leftBlock;
		string rightBlock;
		KeyGenerator * aKeyGenerator;
};

#endif

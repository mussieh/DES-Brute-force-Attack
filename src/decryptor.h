#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <string>
#include <memory>
#include <iostream>
#include "util.h"
#include "buffer.h"
#include "keygenerator.h"
#include <bitset> // bitset<64>(str.c_str())
#include <chrono>

using namespace std;
typedef unsigned int uint;

class Decryptor
{
 public:

	Decryptor(Buffer * buf, string& key);
	~Decryptor();
	unique_ptr<vector<string>> getPlainTextBlocks();

 private:

		Buffer * aBuffer;
		KeyGenerator * aKeyGenerator;
};

#endif

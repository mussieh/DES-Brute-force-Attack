#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <string>
#include <memory>
#include <iostream>
#include "util.h"
#include <bitset> // bitset<64>(str.c_str())

using namespace std;
typedef unsigned int uint;

class KeyGenerator
{
 public:

	KeyGenerator(string& in);
	unique_ptr<vector<string>> getKeys();
	Util & getUtil();
	string& getPC1();
	string getKey();
	void setKey(string& key);
 private:

		string originalKey;
		string pc2;
		string lstr;
		Util util;

		string& getPC2(string& aString);
		string& leftShift(bitset<28>& x, bitset<28>& y, uint shiftSchedule);
		unique_ptr<vector<string>> getShiftedStrings();
};

#endif

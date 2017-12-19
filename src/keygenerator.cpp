#include "keygenerator.h"

KeyGenerator::KeyGenerator(string& in) {
	originalKey = in;
	pc2 = "";
	lstr = "";
}

void KeyGenerator::setKey(string& key) {
	originalKey = key;
}

string KeyGenerator::getKey() {
	return originalKey;
}

/* Not used since key is given to be 56-Bits
string& KeyGenerator::getPC1() {
	pc1 = "";
	for (uint i = 0; i < 56; i++) {
		pc1 += originalKey.at(util.PERMUTED_CHOICE1[i] - 1);
	}
	return pc1;
}
*/

string& KeyGenerator::getPC2(string& aString) {
	pc2 = "";
	for (uint i = 0; i < 48; i++) {
		pc2 += aString.at(util.PERMUTED_CHOICE2[i] - 1);
	}
	return pc2;
}

string& KeyGenerator::leftShift(bitset<28>& x, bitset<28>& y, uint shiftSchedule) {
	bitset<28> temp;
	bool tx;
	bool ty;
	while ( shiftSchedule != 0 ) {
		tx = x[27];
		ty = y[27];
		x = x << 1;
		y = y << 1;
		x.set(0, tx);
		y.set(0, ty);
		shiftSchedule--;
	}
	lstr = x.to_string() + y.to_string();
	return lstr;
}

unique_ptr<vector<string>> KeyGenerator::getShiftedStrings() {
	unique_ptr<vector<string>> blocks = util.getDividedStrings(originalKey, 28);
	bitset<28> x = bitset<28>((*blocks)[0].c_str());
	bitset<28> y = bitset<28>((*blocks)[1].c_str());
	unique_ptr<vector<string>> shiftedStrings = unique_ptr<vector<string>>(new vector<string>(16));
	unique_ptr<vector<string>> bStrings = unique_ptr<vector<string>>(new vector<string>(2));
	string nleftBlock;
	string nrightBlock;
	string nBlock;

	for (uint i = 0; i < 16; i++) {
		nBlock = leftShift(x, y, util.LEFT_SHIFT_SCHEDULE[i]);
		bStrings = util.getDividedStrings(nBlock, 28);
		nleftBlock = (*bStrings)[0];
		nrightBlock = (*bStrings)[1];
		(*shiftedStrings).at(i) = nleftBlock + nrightBlock;
		(*blocks).at(0) = nleftBlock;
		(*blocks).at(1) = nrightBlock;
	}
	return shiftedStrings;
}

unique_ptr<vector<string>> KeyGenerator::getKeys() {
	unique_ptr<vector<string>> nKeyArray = unique_ptr<vector<string>>(new vector<string>(16));
	unique_ptr<vector<string>> shiftedStrings = getShiftedStrings();
	for (uint i = 0; i < 16; i++) {
		(*nKeyArray).at(i) = getPC2((*shiftedStrings).at(i));
	}

	return nKeyArray;
}

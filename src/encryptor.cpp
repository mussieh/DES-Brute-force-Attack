#include "encryptor.h"

Encryptor::Encryptor(string& inputBlock) {
	Util util;
	permutedBlock = *util.getInitialPermuation( inputBlock );
	leftBlock = "";
	rightBlock = "";
	aKeyGenerator = new KeyGenerator(key);
}

Encryptor::~Encryptor() {

	if (aKeyGenerator != NULL) {
		delete aKeyGenerator;
	}
}

KeyGenerator * Encryptor::getKeyGenerator() {
	return aKeyGenerator;
}

unique_ptr<string> Encryptor::getCipherText() {
	Util util;
	bitset<32> x;
	bitset<32> y;
	string permutedString;
	unique_ptr<string> cipherBlock = unique_ptr<string>(new string());
	unique_ptr<vector<string>> nKeyArray = aKeyGenerator->getKeys();
	string tempLeftBlock = "";
	permutedString = permutedBlock;
	leftBlock = (*util.getDividedStrings(permutedBlock, 32)).at(0);
	rightBlock = (*util.getDividedStrings(permutedBlock, 32)).at(1);

	for (uint j = 0; j < 16; j++) {
		tempLeftBlock = leftBlock;
		leftBlock = rightBlock;
		x = bitset<32>(tempLeftBlock.c_str());
		y= bitset<32>( (*util.conversionFunction(rightBlock, (*nKeyArray).at(j) ) ).c_str() );
		rightBlock = util.XOR32(x,y);
	}
	permutedString = rightBlock + leftBlock;
	*cipherBlock  =  *util.getInversePermutation( permutedString );

	return cipherBlock;
}

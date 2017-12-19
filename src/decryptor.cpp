#include "decryptor.h"

Decryptor::Decryptor(Buffer * buf, string& key) {
	aBuffer = buf;
	aKeyGenerator = new KeyGenerator(key);
}

Decryptor::~Decryptor() {

	if (aKeyGenerator != NULL) {
		delete aKeyGenerator;
	}
}

unique_ptr<vector<string>> Decryptor::getPlainTextBlocks() {
	Util util;
	string leftBlock = "";
	string rightBlock = "";
	bitset<32> x;
	bitset<32> y;
	vector<string> * cipherBlocks = (*aBuffer).getBlocks();
	uint pLen = (*cipherBlocks).size();

	unique_ptr<vector<string>> permutedStrings = unique_ptr<vector<string>>(new vector<string>(pLen));
	unique_ptr<vector<string>> plainBlocks = unique_ptr<vector<string>>(new vector<string>(pLen));
	unique_ptr<vector<string>> nKeyArray = aKeyGenerator->getKeys();
	string tempLeftBlock = "";
	string temp = "";

	for (uint i = 0; i < pLen; i++) {
		(*permutedStrings).at(i)  =  ( *util.getBinaryFromHex( ( (*cipherBlocks).at(i) ) ) ) ;
	}

	for (uint i = 0; i < pLen; i++) {
		(*permutedStrings).at(i)  =  *util.getInitialPermuation( (*permutedStrings).at(i) );
	}

	for (uint i = 0; i < pLen; i++) {
		leftBlock = (*util.getDividedStrings((*permutedStrings).at(i), 32)).at(0);
		rightBlock = (*util.getDividedStrings((*permutedStrings).at(i), 32)).at(1);
		for (int j = 15; j >= 0; j--) {
			tempLeftBlock = leftBlock;
			leftBlock = rightBlock;
			x = bitset<32>(tempLeftBlock.c_str());
			y= bitset<32>( (*util.conversionFunction(rightBlock, (*nKeyArray).at(j) ) ).c_str() );
			rightBlock = util.XOR32(x,y);
		}
		temp = rightBlock + leftBlock;
		(*permutedStrings).at(i)  =  temp;
	}

	for (uint i = 0; i < pLen; i++) {
		(*plainBlocks).at(i)  =  *util.getInversePermutation( (*permutedStrings).at(i) );
	}

		return plainBlocks;
}

#include "util.h"

Util::Util() {
}

unique_ptr<string> Util::getInitialPermuation(string& aString) {
	unique_ptr<string> tempArray (new string());
	for (uint i = 0; i < aString.length(); i++) {
		*tempArray += aString.at(IP[i] - 1);
	}
	return tempArray;
}

unique_ptr<string> Util::getEBitPermutation(string& aString) {
	unique_ptr<string> tempArray (new string());
	for (uint i = 0; i < 48; i++) {
		*tempArray += aString.at(E_TABLE[i] - 1);
	}
	return tempArray;
}

unique_ptr<string> Util::getPPermutation(string& aString) {
	unique_ptr<string> tempArray (new string());
	for (uint i = 0; i < 32; i++) {
		*tempArray += aString.at(P_TABLE[i] - 1);
	}
	return tempArray;
}

unique_ptr<string> Util::getInversePermutation(string& aString) {
	unique_ptr<string> tempArray (new string());
	for (uint i = 0; i < 64; i++) {
		*tempArray += aString.at(INVERSE_IP[i] - 1);
	}
	return tempArray;
}

string& Util::XOR32(bitset<32>& x, bitset<32>& y) {
	bitset<32> temp;
	temp = x ^ y;
	xr32 = temp.to_string();
	return xr32;
}

string& Util::XOR48(bitset<48>& x, bitset<48>& y) {
	bitset<48> temp;
	temp = x ^ y;
	xr48 = temp.to_string();
	return xr48;
}


unique_ptr<string> Util::conversionFunction(string& rightBlock, string& nthKey) {
	unique_ptr<string> expandedString = getEBitPermutation(rightBlock);
	bitset<48> nkbits = bitset<48>(nthKey.c_str());
	bitset<48> expbits = bitset<48>((*expandedString).c_str());
	string XOR1 = XOR48(nkbits, expbits);
	uint counter = 0;
	uint previousIndex = 0;
	string sboxOutput = "";
	uint i;
	uint j;
	string temp = "";
	uint ioutput = 0;
	uint sboxCounter = 0;
	while (counter < XOR1.length()) { // SBox mapping

		if ( (counter + 1) % 6 == 0 ){
			sboxCounter++;
			temp = XOR1.at(previousIndex);
			temp += XOR1.at(counter);
			i = stoi(temp, nullptr, 2);
			temp = XOR1.substr(previousIndex + 1, 4);
			j = stoi(temp, nullptr, 2);
			ioutput = sboxCounter == 1 ? s1[i][j] : ioutput;
			ioutput = sboxCounter == 2 ? s2[i][j] : ioutput;
			ioutput = sboxCounter == 3 ? s3[i][j] : ioutput;
			ioutput = sboxCounter == 4 ? s4[i][j] : ioutput;
			ioutput = sboxCounter == 5 ? s5[i][j] : ioutput;
			ioutput = sboxCounter == 6 ? s6[i][j] : ioutput;
			ioutput = sboxCounter == 7 ? s7[i][j] : ioutput;
			ioutput = sboxCounter == 8 ? s8[i][j] : ioutput;
			sboxOutput += (bitset<4>(ioutput).to_string());
			previousIndex = counter + 1;
		}
		counter++;
	}
	unique_ptr<string> pOutput = getPPermutation(sboxOutput);
	return pOutput;
}

unique_ptr<string> Util::getHexFromBinary(string& binary) {
	unique_ptr<string> hexString(new string());
	string tempString;
	char tempChar;

	for (uint i = 0; i < binary.length(); i++) {
		tempString += binary.at(i);
		if ( (i + 1) % 4 == 0 ) {
			uint temp = stoi(tempString, nullptr, 2);
			tempString = "";
			tempChar = ' ';
			if (temp < 10) {
				*hexString += to_string(temp);
			}
			else {
				tempChar = temp == 10 ? 'A' : tempChar;
				tempChar = temp == 11 ? 'B' : tempChar;
				tempChar = temp == 12 ? 'C' : tempChar;
				tempChar = temp == 13 ? 'D' : tempChar;
				tempChar = temp == 14 ? 'E' : tempChar;
				tempChar = temp == 15 ? 'F' : tempChar;
				*hexString += tempChar;
			}
		}
	}
	return hexString;
}

unique_ptr<string> Util::getBinaryFromHex(string& hexCode) {
	unique_ptr<string> binaryString(new string());
	uint decimal;
	bitset<4> tempBits;
	string tempString = "";
	char temp;

	for (uint i = 0; i < hexCode.length(); i++) {
		temp = hexCode.at(i);
		decimal = isalpha(temp) ? (uint) temp : (temp - '0');

		if (decimal >= 0 && decimal < 10 ) {
			*binaryString += bitset<4>(decimal).to_string();
		}
		else {

			if (temp == 'A') {
				decimal = 10;
			}
			else if (temp == 'B') {
				decimal = 11;
			}
			else if (temp == 'C') {
				decimal = 12;
			}
			else if (temp == 'D') {
				decimal = 13;
			}
			else if (temp == 'E') {
				decimal = 14;
			}
			else if (temp == 'F') {
				decimal = 15;
			}
			*binaryString += bitset<4>(decimal).to_string();
		}
	}
	return binaryString;
}

unique_ptr<string> Util::getBinaryFromText(string& aString) {
	unique_ptr<string> binary(new string());
	for (uint j = 0; j < 8; j++) {
		*binary += bitset<8>(aString.c_str()[j]).to_string();
	}
	return binary;
}

unique_ptr<vector<string>> Util::getDividedStrings(string& aString, uint numberOfBits) {
	vector<string> * parts = new vector<string>(2);
	parts->at(0) = aString.substr(0, numberOfBits);
	parts->at(1) = aString.substr(numberOfBits, numberOfBits);
	unique_ptr<vector<string>> partptr(parts);
	return partptr;
}

unique_ptr<string> Util::getTextFromBinary(string& aString) {
	unique_ptr<string> text(new string());
	uint len = aString.length();
	uint pIndex = 0;
	char letter;
	for (uint i = 0; i < len; i++) {
		if ( (i + 1) % 8 == 0 ) {
			letter = (char) stoi(aString.substr(pIndex, 8), nullptr, 2);
			*text += letter;
			pIndex = i + 1;
		}
	}
	return text;
}

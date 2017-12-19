#include "buffer.h"

Buffer::Buffer (const char *inputPath, const char *outputPath, int blockSize, int blockLength)
{
  inputFilePath = inputPath;
  outputFilePath = outputPath;
  buffer = new char [blockSize * blockLength];
  this->blockSize = blockSize;
  this->blockLength = blockLength;
  blocks = new vector<string>(blockSize);

  // Open the file and fill the buffer.
  input_file.open(inputFilePath, ifstream::binary);
  output_file.open(outputFilePath);
  if (input_file.fail()) {
    // Failed to open source file.
    cerr << "Can't open source file " << *inputFilePath << endl;
    buffer_fatal_error();
  }

  if (output_file.fail()) {
    // Failed to open output file.
    cerr << "Can't open output file " << *outputFilePath << endl;
    buffer_fatal_error();
  }

}

Buffer::~Buffer()
{
	input_file.close();
	output_file.close();

	if (buffer != NULL) {
		delete[] buffer;
	}

	if (blocks != NULL) {
		delete blocks; // since blocks is not an array but a vector pointer
	}

}

vector<string>* Buffer::getBlocks() {
	input_file.read(buffer, blockSize * blockLength);
	int nextByteStatus = input_file.gcount();
	int completeBlockStatus = nextByteStatus % blockLength;
	int leftOver = nextByteStatus - completeBlockStatus;
	string block = "";

	if ( nextByteStatus != 0 ) {
		int loopCounter = 0;
		int blockCounter = 0;
		while (loopCounter < leftOver) {
			block += buffer[loopCounter];
			if ( (loopCounter + 1) % blockLength == 0) {
				blocks->at(blockCounter) = block;
				block = "";
				blockCounter++;
			}
			loopCounter++;
		}

		if ( completeBlockStatus != 0  ) {
			uint bufLength = (sizeof(buffer)/sizeof(*buffer));
			// Complete the rest of the block
			for (uint i = leftOver; i < bufLength; i++) {
				char item = buffer[i];
				if (item != (char) 0) {
					block += item;
				}
			}
		}
		// Add Padding if block is not complete from file
		while (block.length() < blockLength && block != "") {
			block += "0";
			if (block.length() == blockLength) {
				blocks->at(blockCounter) = block;
			}
		}
	}
	return blocks;
}

void Buffer::writeString (string& aString) {
	output_file << aString;
}


void Buffer::buffer_fatal_error() const
{
  cerr << "Exiting on BUFFER FATAL ERROR" << endl;
  exit (-1);
}



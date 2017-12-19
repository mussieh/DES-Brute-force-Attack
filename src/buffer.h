#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
typedef unsigned int uint;

class Buffer
{
 public:

  // Open the program file and initialize the buffer.
  Buffer(const char *inputPath, const char *outputPath, int blockSize, int blockLength);

  // Close the file and cleanup.
  ~Buffer();

 vector<string>* getBlocks();
 void writeString (string& aString);


 private:
  const char *inputFilePath;
  const char *outputFilePath;
  char *buffer;
  vector<string>* blocks;
  unsigned int blockSize;
  unsigned int blockLength;
  ifstream input_file;
  ofstream output_file;

  /* If something catastrophic happens in the buffer, print
     an error message and then call this method to exit. */
  void buffer_fatal_error() const;

};

#endif

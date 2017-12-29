//============================================================================
// Name        : DES.cpp
// Author      : Mussie Habtemichael
// Version     :
// Copyright   :
// Description : DES in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "client.h"
#include "util.h"
#include "keygenerator.h"
#include "encryptor.h"
#include "decryptor.h"
#include <chrono>
#include <bitset>
#define NUM_THREADS 5
using namespace std;

Util util;
bool bruteForce_Done = false;

struct thread_data {
   int  thread_id;
   long long startIndex;
   long long endIndex;
   string plainString;
   string cipherText;
};

// Network Error
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void *checkKeys(void *threadarg) {
	Client threadClient;
	struct thread_data *t_data;
	t_data = (struct thread_data *) threadarg;
	Encryptor enc(t_data->plainString);
	KeyGenerator * keyGen = enc.getKeyGenerator();
	string cipherString;
	string key;
	long long startIndex = t_data->startIndex;
	long long endIndex = t_data->endIndex;
    	long long previous = startIndex;
	string cipherText = t_data->cipherText;

	for (long long i = startIndex; i < endIndex; ++i) {
        if ( threadClient.keyStatus() > 0) {
            cout << threadClient.getMessage() << endl;
			pthread_exit(NULL);
		}

		// Bruteforce Progress
		if ( t_data->thread_id == 4 && i - previous == 200000 ) {
			cout << '\r' << i << flush;
			previous = i;
		}

		key = (bitset<56>(i).to_string());
		keyGen->setKey(key);
		cipherString = *(enc.getCipherText());

		if (  cipherText == cipherString ) {
            		key = *util.getHexFromBinary(key);
			threadClient.informServer(key);
			cout << t_data->thread_id << endl;
			cout << key << endl;
		}
	}
	pthread_exit(NULL);
}


int main(int argc, char** argv) {
	auto started = std::chrono::high_resolution_clock::now();

	string plainString = "12345qwe";
	string cipherString = "7162855231E3E281";
	plainString = *util.getBinaryFromText(plainString);
	cipherString = *util.getBinaryFromHex(cipherString);

	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	int rc;
	int i;
	pthread_attr_t attr;
	void *status;

	/* Key Values */
	// 1441151880758559 keys per thread
	long long indexes [5][2] = {
			{43234559931156764, 44675708303515323},
			{44675708891915323, 46116860184273882},
			{46116860772673882, 47558012065032441},
			{47558012653432441, 48999163945791000},
			{48999164534191000, 50440315826549557}
	};

	/* Multi-threading Part
	 * Simple Implementation
	 */
	// Initialize and set thread joinable
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for( i = 0; i < NUM_THREADS; i++ ) {
	   cout <<"main() : creating thread, " << i << endl;
	   td[i].thread_id = i;
	   td[i].startIndex = indexes[i][0];
	   td[i].endIndex = indexes[i][1];
	   td[i].plainString = plainString;
	   td[i].cipherText = cipherString;


	   rc = pthread_create(&threads[i], NULL, checkKeys, (void *)&td[i]);

	   if (i == NUM_THREADS - 1) {
		   cout << endl;
		   cout << "Brute Forcing...." << endl;
	   }

	   if (rc) {
	       cout << "Error:unable to create thread," << rc << endl;
	       exit(-1);
	      }
	   }

	// free attribute and wait for the other threads
	pthread_attr_destroy(&attr);
	for( i = 0; i < NUM_THREADS; i++ ) {
	   rc = pthread_join(threads[i], &status);
	   if (rc) {
	       cout << "Error:unable to join," << rc << endl;
	       exit(-1);
	   }
	}

	auto done = std::chrono::high_resolution_clock::now();
	cout << "Time in msec: " << chrono::duration_cast<chrono::milliseconds>(done-started).count() << endl;
	pthread_exit(NULL);

	return 0;
}

/*
This test case generate large keys and insert into hash structure.
Then, delete keys from the set.
*/
#include <vector>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
#include "test_util.h"
#include "LinearHash.h"

using namespace std;

int main(){
	LinearHash* lhPtr = new LinearHash();
	lhPtr->printHashMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int keySize = MODPRIME * 0.8;
	KeyType* keys = new KeyType[keySize];

	genDistinctKeys(keys, keySize);

	/*
		Initialize hash and insert keys
	*/
	lhPtr->create();	

	/*
		Begin meassuring performance
	*/
	auto start = chrono::high_resolution_clock::now();

	long long *msecInsert = new long long[(keySize/SAMPLE_PERIOD) + 1];


	for(unsigned int idx=0; idx < keySize; idx++){
		if(lhPtr->insert(keys[idx], keys[idx]) != SUCCESS){
			assert(false);
		}
		if((idx % SAMPLE_PERIOD) == 0){
			auto elapsed = chrono::high_resolution_clock::now() - start;
			msecInsert[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();
		}
	}
	/*
		Dump into result file.
	*/
	fstream fs;
	fs.open("result/linearHash_uniform_insert_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < keySize/SAMPLE_PERIOD; idx++){
		fs << idx*SAMPLE_PERIOD << " " << msecInsert[idx] << endl;
	}
	fs.close();
	cout<<"Finish linear hash insertion "<<keySize <<" elements"<<endl;

	vector<KeyType> shuffledKeys_v(keys, keys+keySize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	KeyType* shuffledKeys = new KeyType[keySize];
	for(unsigned int idx=0; idx < keySize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	start = chrono::high_resolution_clock::now();

	long long *msecDelete = new long long[(keySize/SAMPLE_PERIOD) + 1];

	// Test deleteion
	for(unsigned int idx=0; idx < keySize; idx++){
		if(lhPtr->delkey(shuffledKeys[idx]) != SUCCESS){
			assert(false);
		}
		if((idx % SAMPLE_PERIOD) == 0){
			auto elapsed = chrono::high_resolution_clock::now() - start;
			msecDelete[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();
		}
	}
	cout<<"Finish linear hash deletion "<<keySize <<" elements"<<endl;
	assert(lhPtr->isEmptyHash());

	/*
		Dump into result file.
	*/
	fs.open("result/linearHash_uniform_delete_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < keySize/SAMPLE_PERIOD; idx++){
		fs << (keySize - idx*SAMPLE_PERIOD) << " " << msecDelete[keySize/SAMPLE_PERIOD - 1] - msecDelete[idx] << endl;
	}
	fs.close();

	delete [] keys;
	delete [] shuffledKeys;
	return 0;
}

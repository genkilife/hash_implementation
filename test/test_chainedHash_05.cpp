/*
This test case generate large keys and insert into hash structure.
Then, delete keys from the set.
*/
#include <vector>
#include <algorithm>
#include "test_util.h"
#include "ChainedHash.h"

using namespace std;

int main(){
	ChainedHash* chPtr = new ChainedHash();
	chPtr->printHashMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int keySize = MODPRIME * 0.8;
	KeyType* keys = new KeyType[keySize];

	genDistinctKeys(keys, keySize);

	/*
		Initialize hash and insert keys
	*/
	chPtr->create();
	for(unsigned int idx=0; idx < keySize; idx++){
		if(chPtr->insert(keys[idx], keys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish chained hash insertion "<<keySize <<" elements"<<endl;

	vector<KeyType> shuffledKeys_v(keys, keys+keySize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	KeyType* shuffledKeys = new KeyType[keySize];
	for(unsigned int idx=0; idx < keySize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	// Test deleteion
	for(unsigned int idx=0; idx < keySize; idx++){
		if(chPtr->delkey(shuffledKeys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish chaind hash deletion "<<keySize <<" elements"<<endl;
	assert(chPtr->isEmptyHash());

	delete [] keys;
	delete [] shuffledKeys;
	return 0;
}

/*
This test case generate large keys and insert into hash structure.
Then, delete keys from the set.
*/
#include <vector>
#include <algorithm>
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
	for(unsigned int idx=0; idx < keySize; idx++){
		if(lhPtr->insert(keys[idx], keys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish linear hash insertion "<<keySize <<" elements"<<endl;

	vector<KeyType> shuffledKeys_v(keys, keys+keySize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	KeyType* shuffledKeys = new KeyType[keySize];
	for(unsigned int idx=0; idx < keySize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	// Test deleteion
	for(unsigned int idx=0; idx < keySize; idx++){
		if(lhPtr->delkey(keys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish linear hash deletion "<<keySize <<" elements"<<endl;
	assert(lhPtr->isEmptyHash());


	delete [] keys;
	delete [] shuffledKeys;
	return 0;
}

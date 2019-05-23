/*
This test case generate small keys and insert into hash structure.
*/
#include <vector>
#include <algorithm>
#include "test_util.h"
#include "DoubleHash.h"

using namespace std;

int main(){
	DoubleHash* dhPtr = new DoubleHash();
	dhPtr->printHashMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int keySize = MODPRIME * 0.8;
	KeyType* keys = new KeyType[keySize];

	genDistinctKeys(keys, keySize);

	/*
		Initialize hash and insert keys
	*/
	dhPtr->create();	
	for(unsigned int idx=0; idx < keySize; idx++){
		if(dhPtr->insert(keys[idx], keys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish double hash insertion "<<keySize <<" elements"<<endl;

	vector<KeyType> shuffledKeys_v(keys, keys+keySize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	KeyType* shuffledKeys = new KeyType[keySize];
	for(unsigned int idx=0; idx < keySize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	// Test deleteion
	for(unsigned int idx=0; idx < keySize; idx++){
		if(dhPtr->search(keys[idx]) != SUCCESS){
			cout<<"serach not found"<<endl;
			assert(false);
		}
		if(dhPtr->delkey(shuffledKeys[idx]) != SUCCESS){
			cout<<"delete error"<<endl;
			assert(false);
		}
	}
	cout<<"Finish double hash deletion "<<keySize <<" elements"<<endl;
	assert(dhPtr->isEmptyHash());

	delete [] keys;
	delete [] shuffledKeys;
	return 0;
}

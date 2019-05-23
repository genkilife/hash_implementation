#include <vector>
#include <algorithm>
#include "test_util.h"
#include "CuckooHash.h"

using namespace std;

int main(){
	CuckooHash* ckPtr = new CuckooHash();
	ckPtr->printHashMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int keySize = MODPRIME * 0.8;
	KeyType* keys = new KeyType[keySize];

	genDistinctKeys(keys, keySize);

	/*
		Initialize hash and insert keys
	*/
	ckPtr->create();
	for(unsigned int idx=0; idx < keySize; idx++){
		if(ckPtr->insert(keys[idx], keys[idx]) != SUCCESS){
			assert(false);
		}
	}
	cout<<"Finish cuckoo hash insertion "<<keySize <<" elements"<<endl;

	vector<KeyType> shuffledKeys_v(keys, keys+keySize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	KeyType* shuffledKeys = new KeyType[keySize];
	for(unsigned int idx=0; idx < keySize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	// Test deleteion
	for(unsigned int idx=0; idx < keySize; idx++){
		if(ckPtr->search(shuffledKeys[idx]) != SUCCESS){
			cout<<"serach not found"<<endl;
			assert(false);
		}
		if(ckPtr->delkey(shuffledKeys[idx]) != SUCCESS){
			cout<<"delete error"<<endl;
			assert(false);
		}
	}
	cout<<"Finish cuckoo hash deletion "<<keySize <<" elements"<<endl;
	assert(ckPtr->isEmptyHash());

	delete [] keys;
	delete [] shuffledKeys;
	return 0;
}

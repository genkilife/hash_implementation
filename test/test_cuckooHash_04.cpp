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

	delete [] keys;
	return 0;
}

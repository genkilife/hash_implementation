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

	delete [] keys;
	return 0;
}

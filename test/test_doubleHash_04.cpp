/*
This test case generate small keys and insert into hash structure.
*/
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

	delete [] keys;
	return 0;
}

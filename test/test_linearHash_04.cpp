/*
This test case generate small keys and insert into hash structure.
*/
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

	delete [] keys;
	return 0;
}

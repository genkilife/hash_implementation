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
	unsigned int keySize = 100;
	KeyType* keys = new KeyType[keySize];

	genDistinctKeys(keys, keySize);

	for(int i=0; i<keySize; i++){
		cout<<keys[i]<<endl;
	}

	delete [] keys;
	return 0;
}

#ifndef _CHAINED_HASH_H_
#define _CHAINED_HASH_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BasicHash.h"

class ChainedHash: public BasicHash{
	public:
		ChainedHash();
		~ChainedHash();
	// hash function
	public:
		RC create();
		RC insert(KeyType, ValType);
		RC search(KeyType);
		RC delkey(KeyType);
		RC printHashMethod();
		bool isEmptyHash();
	private:
		Bucket* buckets;
		unsigned int bucketSize;
		unsigned int keyNum;
};
#endif

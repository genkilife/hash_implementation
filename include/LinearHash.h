#ifndef _LINEAR_HASH_H_
#define _LINEAR_HASH_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BasicHash.h"

class LinearHash: public BasicHash{
	public:
		LinearHash();
		~LinearHash();
	// hash function
	public:
		RC create();
		RC insert(KeyType, ValType);
		RC search(KeyType);
		RC delkey(KeyType);
		RC printHashMethod();
	private:
		Bucket* buckets;
		unsigned int bucketSize;
		unsigned int keyNum;
};
#endif

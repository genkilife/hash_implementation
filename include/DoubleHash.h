#ifndef _DOUBLE_HASH_H_
#define _DOUBLE_HASH_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BasicHash.h"

class DoubleHash: public BasicHash{
	public:
		DoubleHash();
		~DoubleHash();
	// hash function
	public:
		RC create();
		RC insert(KeyType, ValType);
		RC search(KeyType);
		RC delkey(KeyType);
		RC printHashMethod();
		bool isEmptyHash();

	private:
		KeyType hashFunc0(KeyType);
		KeyType hashFunc1(KeyType);
	private:
		Bucket* buckets;
		unsigned int bucketSize;
		unsigned int keyNum;
};
#endif

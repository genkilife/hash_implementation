#ifndef _CUCKOO_HASH_H_
#define _CHCKOO_HASH_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BasicHash.h"

class CuckooHash: public BasicHash{
	public:
		CuckooHash();
		~CuckooHash();
	// hash function
	public:
		RC create();
		RC insert(KeyType, ValType);
		RC search(KeyType);
		RC delkey(KeyType);
		RC printHashMethod();

	private:
		KeyType hashFunc0(KeyType);
		KeyType hashFunc1(KeyType);
		RC bucketswap(Bucket&, Bucket&); 
	private:
		Bucket* buckets0;
		Bucket* buckets1;
		unsigned int bucketSize;
		unsigned int keyNum;
};
#endif

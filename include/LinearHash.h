#ifndef _LINEAR_HASH_H_
#define _LINEAR_HASH_H_

#include <iostream>
#include "test_util.h"
#include "BasicHash.h"

class LinearHash: public BasicHash{
	public:
		LinearHash();
		~LinearHash();
	// hash function
	public:
		virtual RC create();
		virtual RC insert(KeyType, ValType);
		virtual RC search(KeyType);
		virtual RC delkey(KeyType);
		virtual RC printHashMethod();
};
#endif

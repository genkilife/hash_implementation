#ifndef _BASIC_HASH_H_
#define _BASIC_HASH_H_

#include <iostream>
#include "test_util.h"

class BasicHash{
	public:
		BasicHash();
		~BasicHash();
	// hash function
	public:
		virtual RC create();
		virtual RC insert(KeyType, ValType);
		virtual RC search(KeyType);
		virtual RC delkey(KeyType);
		virtual RC printHashMethod();
};
#endif

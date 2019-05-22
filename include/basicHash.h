#ifndef _BASIC_HASH_H_
#define _BASIC_HASH_H_

#include "test_util.h"

class basicHash{
	public:
		basicHash();
		~basicHash();
	// hash function
	public:
		virtual RC create();
		virtual RC insert();
		virtual RC search();
};
#endif

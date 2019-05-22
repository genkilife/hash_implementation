#ifndef _TEST_UTIL_
#define _TEST_UTIL_

typedef int RC;

typedef unsigned int KeyType;
typedef unsigned int ValType;

#define MODPRIME 32749

// for non-return usage
#define SUCCESS 0


struct Bucket{
	bool valid;
	KeyType key;
	ValType value;
};

// for returning error status

#endif

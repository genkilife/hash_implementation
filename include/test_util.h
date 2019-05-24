#ifndef _TEST_UTIL_
#define _TEST_UTIL_

typedef int RC;

typedef unsigned int KeyType;
typedef unsigned int ValType;

#define MODPRIME 32749

// for non-return usage
#define SUCCESS 0

#define SAMPLE_PERIOD 200

struct Bucket{
	bool valid;
	KeyType key;
	ValType value;
	Bucket* next;
};

RC genDistinctKeys(KeyType*, unsigned int);

#endif

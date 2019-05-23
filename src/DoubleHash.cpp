#include "DoubleHash.h"

DoubleHash::DoubleHash(){
	buckets = NULL;
}

DoubleHash::~DoubleHash(){
	if(buckets != NULL){
		delete [] buckets;
	}
}

RC DoubleHash::create(){

	bucketSize = MODPRIME;
	keyNum = 0;

	if(buckets == NULL){
		buckets = new Bucket[bucketSize];
	}

	// Clear valid flag
	for(unsigned int id=0; id < bucketSize; id++){
		buckets[id].valid = false;
	}
	
	return SUCCESS;
}

RC DoubleHash::insert(KeyType key, ValType val){

	// We assume no resize is needed
	if(keyNum == bucketSize){
		return -1;
	}

	#ifdef _ASSERTION_
		assert(keyNum < bucketSize);
	#endif

	KeyType hashedId  = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	unsigned int cnt=0;
	while(buckets[hashedId].valid == true){
		hashedId = (hashedId + hashedId1) % bucketSize;
		cnt++;
		if(cnt >= bucketSize){
			return -1;
		}
	}

	buckets[hashedId].valid = true;
	buckets[hashedId].key   = key;
	buckets[hashedId].value = val;
	
	keyNum++;
	return SUCCESS;
}

RC DoubleHash::search(KeyType key){

	KeyType hashedId  = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	#ifdef _ASSERTION_
		assert(hashedId  < bucketSize);
		assert(hashedId1 < bucketSize);
	#endif
	
	while(buckets[hashedId].valid){
		if(buckets[hashedId].key == key){
			return SUCCESS;
		}
		hashedId = (hashedId + hashedId1) % bucketSize;
	}

	return -1;
}

RC DoubleHash::delkey(KeyType key){
	
	KeyType hashedId  = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	#ifdef _ASSERTION_
		assert(hashedId  < bucketSize);
		assert(hashedId1 < bucketSize);
	#endif

	while(buckets[hashedId].valid){
		if(buckets[hashedId].key == key){
			buckets[hashedId].valid = false;
			keyNum--;
			return SUCCESS;
		}
		hashedId = (hashedId + hashedId1) % bucketSize;
	}

	return -1;
}

RC DoubleHash::printHashMethod(){
	std::cout<<"Double hash class is used!"<<std::endl;
	return SUCCESS;
}

KeyType DoubleHash::hashFunc0(KeyType key){
	return (key>>15) % bucketSize;
}

KeyType DoubleHash::hashFunc1(KeyType key){
	return key % bucketSize;
}


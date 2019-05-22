#include "LinearHash.h"

LinearHash::LinearHash(){
	buckets = NULL;
}

LinearHash::~LinearHash(){
	if(buckets != NULL){
		delete [] buckets;
	}
}

RC LinearHash::create(){

	bucketSize = MODPRIME;
	keyNum = 0;

	if(buckets == NULL){
		buckets = new Bucket[bucketSize];
	}

	// Clear valid flag
	for(unsigned int id=0; id < bucketSize; id++){
		buckets[id].valid = false;
	}
	
	#ifdef _ASSERTION_
	for(int id=0; id < bucketSize; id++){
		assert(!buckets[id].valid);
	}
	#endif

	return SUCCESS;
}

RC LinearHash::insert(KeyType key, ValType val){

	if(keyNum == bucketSize){
		return -1;
	}

	#ifdef _ASSERTION_
		assert(keyNum < bucketSize);
	#endif

	KeyType hashedId = key % bucketSize;
	
	while(buckets[hashedId].valid == true){
		hashedId++;
		if(hashedId == bucketSize){
			hashedId = 0;
		}
	}
	
	// Insert on the selected ID
	buckets[hashedId].valid = true;
	buckets[hashedId].key   = key;
	buckets[hashedId].value = val;

	return SUCCESS;
}

RC LinearHash::search(KeyType key){

	KeyType hashedId = key % bucketSize;
	KeyType keyId = hashedId;

	while(buckets[hashedId].valid == true){
		if(buckets[hashedId].key == key){
			return SUCCESS;
		}
		
		// If coninuous keys don't hash on the same key
		KeyType bucketsId = buckets[hashedId].key % bucketSize;
		if(bucketsId != keyId){
			return -1;
		}

		hashedId++;
		if(hashedId == bucketSize){
			hashedId = 0;
		}
	}

	return -1;
}

RC LinearHash::delkey(KeyType key){
	
	KeyType hashedId = key % bucketSize;

	KeyType keyId = hashedId;

	while(buckets[hashedId].valid == true){
		if(buckets[hashedId].valid == key){
			break;
		}

		KeyType bucketsId = buckets[hashedId].key % bucketSize;
		if(bucketsId != keyId){
			// Can't find delete key
			return -1;
		}

		hashedId++;
		if(hashedId == bucketSize){
			hashedId = 0;
		}
	}
	buckets[hashedId].valid = false;

	KeyType preId = hashedId;
	KeyType nxtId = (hashedId+1) % bucketSize;
	while(buckets[nxtId].valid && 
			(buckets[nxtId].key % bucketSize) == keyId
		){
		buckets[preId] = buckets[nxtId];
		preId = nxtId;
		nxtId++;
		if(nxtId == bucketSize){
			nxtId = 0;
		}
	}
	buckets[nxtId].valid = false;

	keyNum--;

	return SUCCESS;
}

RC LinearHash::printHashMethod(){
	std::cout<<"Linear hash class is used!"<<std::endl;
	return SUCCESS;
}


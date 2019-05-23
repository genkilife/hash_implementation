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
		hashedId = (hashedId+1) % bucketSize;
	}
	
	// Insert on the selected ID
	buckets[hashedId].valid = true;
	buckets[hashedId].key   = key;
	buckets[hashedId].value = val;

	keyNum++;

	return SUCCESS;
}

RC LinearHash::search(KeyType key){

	KeyType hashedId = key % bucketSize;

	while(buckets[hashedId].valid == true){
		if(buckets[hashedId].key == key){
			return SUCCESS;
		}
		hashedId = (hashedId+1) % bucketSize;
	}

	return -1;
}

RC LinearHash::delkey(KeyType key){
	
	KeyType hashedId = key % bucketSize;

	while(buckets[hashedId].valid == true){
		if(buckets[hashedId].valid == key){
			break;
		}

		hashedId = (hashedId+1) % bucketSize;
	}
	buckets[hashedId].valid = false;

	KeyType preId = hashedId;
	KeyType nxtId = (hashedId+1) % bucketSize;

	while(buckets[nxtId].valid){ 
		KeyType nexthashed = buckets[nxtId].key % bucketSize;
		if(preId < nxtId){
			if(nexthashed < (preId+1) || nexthashed >(nxtId)){
				buckets[preId] = buckets[nxtId];
				preId = nxtId;
			}
		} else{
			if(nexthashed < (preId+1) && nexthashed >(nxtId)){
				buckets[preId] = buckets[nxtId];
				preId = nxtId;
			}
		}
		nxtId = (nxtId+1) % bucketSize;
	}
	buckets[nxtId].valid = false;

	keyNum--;

	return SUCCESS;
}

RC LinearHash::printHashMethod(){
	std::cout<<"Linear hash class is used!"<<std::endl;
	return SUCCESS;
}

bool LinearHash::isEmptyHash(){
	for(unsigned int id=0; id < bucketSize; id++){
		if(buckets[id].valid){
			return false;
		}
	}
	return true;
}

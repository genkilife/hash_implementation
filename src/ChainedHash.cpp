#include "ChainedHash.h"

ChainedHash::ChainedHash(){
	buckets = NULL;
}

ChainedHash::~ChainedHash(){
	if(buckets != NULL){
		//TODO: need to recursively delete the node on the bucket
		delete [] buckets;
	}
}

RC ChainedHash::create(){

	bucketSize = MODPRIME;
	keyNum = 0;

	if(buckets == NULL){
		buckets = new Bucket[bucketSize];
	}

	// Clear valid flag
	for(unsigned int id=0; id < bucketSize; id++){
		buckets[id].valid = false;
		buckets[id].next = NULL;
	}
	
	#ifdef _ASSERTION_
	for(int id=0; id < bucketSize; id++){
		assert(!buckets[id].valid);
	}
	#endif

	return SUCCESS;
}

RC ChainedHash::insert(KeyType key, ValType val){

	// We assume no resize is needed
	if(keyNum == bucketSize){
		return -1;
	}

	#ifdef _ASSERTION_
		assert(keyNum < bucketSize);
	#endif

	KeyType hashedId = key % bucketSize;

	Bucket* bucketPtr = &buckets[hashedId];
	
	while(bucketPtr->valid == true && bucketPtr->next != NULL){
		bucketPtr = bucketPtr->next;
	}

	bucketPtr->next = new Bucket[1];
	bucketPtr = bucketPtr->next;

	bucketPtr->valid = true;
	bucketPtr->key = key;
	bucketPtr->value = val;
	bucketPtr->next = NULL;
	return SUCCESS;
}

RC ChainedHash::search(KeyType key){

	KeyType hashedId = key % bucketSize;
	Bucket* bucketPtr = &buckets[hashedId];

	while(bucketPtr->valid == true){
		if(bucketPtr->key == key){
			return SUCCESS;
		}

		if(bucketPtr->next == NULL){
			return -1;
		} else{
			bucketPtr = bucketPtr->next;
		}
	}

	return -1;
}

RC ChainedHash::delkey(KeyType key){
	
	KeyType hashedId = key % bucketSize;
	Bucket* preBucketPtr = &buckets[hashedId];
	Bucket* nxtBucketPtr = preBucketPtr->next;

	if(nxtBucketPtr == NULL){
		if(preBucketPtr->key == key){
			preBucketPtr->valid = false;
		} else{
			return -1;
		}
	}
	while(nxtBucketPtr!=NULL){

		if(nxtBucketPtr->key == key){
			// delete this node
			preBucketPtr->next = nxtBucketPtr->next;
			delete nxtBucketPtr;
			return SUCCESS;
		}

		preBucketPtr = nxtBucketPtr;
		nxtBucketPtr = nxtBucketPtr->next;
	}
	return -1;
}

RC ChainedHash::printHashMethod(){
	std::cout<<"Chained hash class is used!"<<std::endl;
	return SUCCESS;
}


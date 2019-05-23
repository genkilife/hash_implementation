#include "CuckooHash.h"

CuckooHash::CuckooHash(){
	buckets0 = NULL;
	buckets1 = NULL;
}

CuckooHash::~CuckooHash(){
	if(buckets0 != NULL){
		delete [] buckets0;
	}
	if(buckets1 != NULL){
		delete [] buckets1;
	}
}

RC CuckooHash::create(){

	bucketSize = MODPRIME;
	keyNum = 0;

	if(buckets0 == NULL){
		buckets0 = new Bucket[bucketSize];
	}
	if(buckets1 == NULL){
		buckets1 = new Bucket[bucketSize];
	}

	// Clear valid flag
	for(unsigned int id=0; id < bucketSize; id++){
		buckets0[id].valid = false;
		buckets1[id].valid = false;
	}
	
	return SUCCESS;
}

RC CuckooHash::insert(KeyType key, ValType val){

	// We assume no resize is needed
	if(keyNum == bucketSize){
		return -1;
	}

	#ifdef _ASSERTION_
		assert(keyNum < bucketSize);
	#endif

	KeyType hashedId;

	Bucket writeBucket = {.valid=true, .key=key, .value=val, .next=NULL};
	bool isLookup0 = true;
	unsigned int cnt=0;

	while(writeBucket.valid == true){
		if(isLookup0){
			hashedId = hashFunc0(writeBucket.key);
			bucketswap(writeBucket, buckets0[hashedId]);
		} else{
			hashedId = hashFunc1(writeBucket.key);
			bucketswap(writeBucket, buckets1[hashedId]);
		}
		isLookup0 = (isLookup0 == false);
		cnt++;
		if(cnt >= 2*bucketSize){
			return -1;
		}
	}
	keyNum++;
	return SUCCESS;
}

RC CuckooHash::search(KeyType key){

	KeyType hashedId0 = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	#ifdef _ASSERTION_
		assert(hashedId0 < bucketSize);
		assert(hashedId1 < bucketSize);
	#endif
	
	if(	 (buckets0[hashedId0].valid && buckets0[hashedId0].key == key)
	  || (buckets1[hashedId1].valid && buckets1[hashedId1].key == key)){
		return SUCCESS;
	}

	return -1;
}

RC CuckooHash::delkey(KeyType key){
	
	KeyType hashedId0 = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	#ifdef _ASSERTION_
		assert(hashedId0 < bucketSize);
		assert(hashedId1 < bucketSize);
	#endif
	if(	 buckets0[hashedId0].valid && buckets0[hashedId0].key == key){
		buckets0[hashedId0].valid = false;
		keyNum--;
		return SUCCESS;
	}
    if(buckets1[hashedId1].valid && buckets1[hashedId1].key == key){
		buckets1[hashedId1].valid = false;
		keyNum--;
		return SUCCESS;
	}

	return -1;
}

RC CuckooHash::printHashMethod(){
	std::cout<<"Cuckoo hash class is used!"<<std::endl;
	return SUCCESS;
}

KeyType CuckooHash::hashFunc0(KeyType key){
	return key % bucketSize;
}

KeyType CuckooHash::hashFunc1(KeyType key){
	return (key/bucketSize) % bucketSize;
}

RC CuckooHash::bucketswap(Bucket& a, Bucket& b){
	Bucket tmp = a;
	a = b;
	b = tmp;
	return SUCCESS;
}

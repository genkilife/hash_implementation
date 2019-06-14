
# Problem scope
Based on the project requirement, I implemented following hash functions in C++:
* Linear hashing
* Chained hashing
* Cuckoo hashing
* Double hashing

# Code structure
.
├── bin  -> compiled binary file
├── include -> header definition files
├── makefile -> makefile to compile project
├── makefile.inc -> included variables
├── obj -> intermediate compiled object files
├── README.md -> explanation of the project
├── result -> Collect experiment data
├── src -> hash function core source code
├── test -> test patterns to evaluate performance

# Experiment step
```makefile
cd $PROJECT_ROOT
module load gcc/5.4.0
make clean
make all
make run
```
# Benchmark
To create the test cases, we use C++ rand() function to generate random number in the selected range.

I adopt the number to be quite less then 2^15=32768 and the largest prime below 32768 is 32749. I force the generated key locates in range from 0 to 32749^2-1. Because some hash methods require 2 different hash function, this distribution can ensure that the keys are uniformly distributed into buckets by using (key % prime) and ((key/prime) % prime) hash functions. It can create closely uniform distribution when we map the keys on the buckets.

# Hash function implementation
## Linear hash method
``` C++
// We use hash function to compute the target bucket.
// While loop can iterate through all of the valid keys.
// The worst case of insert need to visit all of the valid buckets which is O(1+ aN)
// In the average case, the expected of visited buckets is O(1 + a + a^2 ...)
// = O(1/(1-a)) = O(1)
RC LinearHash::insert(KeyType key, ValType val){

	KeyType hashedId = key % bucketSize;

	while(buckets[hashedId].valid){
		hashedId = (hashedId+1) % bucketSize;
	}

	// Insert on the selected ID
	buckets[hashedId] = (valid, key, value);
}

// Search is similar to insert. It needs to iterate through all continous valid buckets
// until it find the right key.
// In the worst case, the right key is at the last valid bucket and it takes O(1+aN).
// If we always give existing key which is ensured the key resides in the hash function,
// it is expected to take half of the time to do search. The complexity is O(1+a/2+a^2/2...)
// = O(1)
// If the search key is not in the hash function, then the analysis is the same as insert
// which takes average O(1/(1-a)) = O(1)
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

// Delete function first do search operation.
// After it finds out the target key, it needs to adjust the position of following buckets.
// It continues putting out-boxed buckets into the suitable range. The length of continous
// valid block is bounded by ratio a. The average time complexity is not worst then
// O(search) + O(adjust) = O(1) + O(1+a) = O(1)
LinearHash::delkey(KeyType key){

	KeyType hashedId = key % bucketSize;

	while(buckets[hashedId].valid == true){
		if(buckets[hashedId].key == key){
			break;
		}
		hashedId = (hashedId+1) % bucketSize;
	}

	KeyType preId = hashedId;
	KeyType nxtId = (hashedId+1) % bucketSize;

  // We adjust the bucket to make hashed key closer to its hashed buckets
	while(buckets[nxtId].valid){
		KeyType nexthashed = buckets[nxtId].key % bucketSize;
		if(nexthashed is not in range [preId+1 .. nxtId]){
				buckets[preId] = buckets[nxtId];
		}
		nxtId = (nxtId+1) % bucketSize;
	}
	buckets[preId].valid = false;
}

```
## Chained hash method
``` C++
// Insertion has to go through all of the buckets appended on the head.
// The inserted data is put at tail.
// Worst case is that all keys collide into 1 bucket which is O(1+aN).
// In average, the average visited bucket is O(1+aN/(bucket size)) = O(1+a)
RC ChainedHash::insert(KeyType key, ValType val){

	KeyType hashedId = key % bucketSize;

	Bucket* bucketPtr = &buckets[hashedId];

	while(bucketPtr->next != NULL){
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

// Search is similar to insert but the key might be found before reaching tail.
// Worst case is all keys hashed on the same bucket and the right key is at the last one.
// Worst time complexity is O(1+aN).
// Average time complexity can be O(1+a/2) = O(1) because we have probability to find
// right key earlier.
RC ChainedHash::search(KeyType key){

	KeyType hashedId = key % bucketSize;
	Bucket* bucketPtr = buckets[hashedId].next;

	while(bucketPtr!=NULL){
		if(bucketPtr->valid == true && bucketPtr->key == key){
			return SUCCESS;
		}

		if(bucketPtr->next == NULL){
			return -1;
		} else{
			bucketPtr = bucketPtr->next;
		}
	}
}

// Delete key is to search the key and remove the node from the cascaded list.
// Remove takes O(1) in any analysis.
// Worst case is the given by O(search) + O(remove) = O(1+aN) +O(1) = O(1+aN)
// Average case is O(1+a) + O(1) = O(1)
RC ChainedHash::delkey(KeyType key){

	KeyType hashedId = key % bucketSize;
	Bucket* preBucketPtr = &buckets[hashedId];
	Bucket* nxtBucketPtr = preBucketPtr->next;

	while(nxtBucketPtr!= NULL){
		if(nxtBucketPtr->valid == true && nxtBucketPtr->key == key){
			// delete this node
			preBucketPtr->next = nxtBucketPtr->next;
			delete nxtBucketPtr;
			return SUCCESS;
		}

		preBucketPtr = nxtBucketPtr;
		nxtBucketPtr = nxtBucketPtr->next;
	}
}

```

## Cuckoo hash method
```C++
// Besides the normal lookup on first hash funciton, Cuckoo hashing keeps pushing
// existing keys into next buckets.
// The worst case is that only 1 buckets is left in the acylic graph and it has to move
// all of the keys to eventually keep the state stable. It takes O(1+aN) in worst case.
// The average case is that it is probability p to hash a key and the position
// exists another key. The average time complexity is O(1+p+p^2...) = O(1/(1-p)) = O(1)
RC CuckooHash::insert(KeyType key, ValType val){
	KeyType hashedId;

	Bucket writeBucket = {.valid=true, .key=key, .value=val, .next=NULL};
	bool isLookup0 = true;

	while(writeBucket.valid == true){
		if(isLookup0){
			hashedId = hashFunc0(writeBucket.key);
			bucketswap(writeBucket, buckets0[hashedId]);
		} else{
			hashedId = hashFunc1(writeBucket.key);
			bucketswap(writeBucket, buckets1[hashedId]);
		}
		isLookup0 = (isLookup0 == false);
	}
	keyNum++;
	return SUCCESS;
}

// It takes constant time to lookup 2 bucket and delete one if found match
// It is O(1) in worst case analysis.
RC CuckooHash::search(KeyType key){

	KeyType hashedId0 = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	#ifdef _ASSERTION_
		assert(hashedId0 < bucketSize);
		assert(hashedId1 < bucketSize);
	#endif

	if(  (buckets0[hashedId0].valid && buckets0[hashedId0].key == key)
	  || (buckets1[hashedId1].valid && buckets1[hashedId1].key == key)){
		return SUCCESS;
	}

	return -1;
}

// It takes constant time to lookup 2 bucket and delete one if found match
// It is O(1) in worst case analysis.
RC CuckooHash::delkey(KeyType key){

	KeyType hashedId0 = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	if(	 buckets0[hashedId0].valid && buckets0[hashedId0].key == key){
		buckets0[hashedId0].valid = false;
		keyNum--;
		return SUCCESS;
	}
    if(buckets1[hashedId1].valid && buckets1[hashedId1].key == key){
		buckets1[hashedId1].valid = false;
		return SUCCESS;
	}
}
```

## Double hashing
```C++
// We need to compute 2 hash functions.
// While loop keeps finding next available bucket and 2nd hash function can
// avoid data skew.

// The worst case of insert need to visit all of the valid buckets when data is
// placed in extreme non-ideal. It takes O(1+ aN).
// In the average case, the expected of visited buckets is O(1 + a + a^2 ...)
// = O(1/(1-a)) = O(1)
RC DoubleHash::insert(KeyType key, ValType val){
	KeyType hashedId  = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	unsigned int cnt=0;
	while(buckets[hashedId].valid == true){
		hashedId = (hashedId + hashedId1) % bucketSize;
	}

	buckets[hashedId].valid = true;
	buckets[hashedId].key   = key;
	buckets[hashedId].value = val;

	return SUCCESS;
}

// Search begins from the hashed position and begin circularly matching the keys.
// In the worst case, the right key is at the last valid bucket and it could search
// all of the buckets which takes O(1+N). Double hashing doesn't stop when find invalid bucket.
// In average, the probability of the key to be a valid key is p (p is small) and it takes
// O(1+(1-p)+p^2...) = O(1/(1-p)) = O(1).
RC DoubleHash::search(KeyType key){

	unsigned int cnt=0;
	while(cnt < bucketSize){
		if(buckets[hashedId].key == key){
			return SUCCESS;
		}
		hashedId = (hashedId + hashedId1) % bucketSize;
		cnt++;
	}

	return -1;
}

// Delete evokes search and it takes O(1) to invalidate the bucket.
// Worst time complexity is the same as O(search) = O(1+N)
// Average time complexity remains O(1)
RC DoubleHash::delkey(KeyType key){

	KeyType hashedId  = hashFunc0(key);
	KeyType hashedId1 = hashFunc1(key);

	unsigned int cnt=0;
	while(cnt < bucketSize){
		if(buckets[hashedId].valid && buckets[hashedId].key == key){
			buckets[hashedId].valid = false;
			return SUCCESS;
		}
		hashedId = (hashedId + hashedId1) % bucketSize;
		cnt++;
	}
}
```

# Performance result
We have test_cases_06 inside tests directory. We use C++ chrono library to sample the running time of the function and get the consuming time on each operation.

We first generate distinct keys and insert the keys into hash function one-by-one. The input is uniformly distributed on each bucket for the used hash function.
Every 300 insert, we would switch to search operation and collect the execution time of search.
After inserting normally full 80% loading, we begin delete operation and compute the average time of each 300 delete.
Following are the results of our experiment in every loading factor:

* Insert
![uniform_insert](/assets/uniform_insert.png)
Chained hashing has high initial cost but grows slowly as loading factor increase.
Linear and double hashing has very low initial cost but cost grows fast as loading factor increase. Linear hash is obviously grows faster then other hashing because it
Cuckoo hashing grows execution time but it is not as obvious as linear or double hashing.

All of the hashing keeps within 2X time complexity when loading factor is not large(less then 50%). We can claim all of the hashing takes O(1) at insertion.

* Search
![uniform_search](/assets/uniform_search.png)
Cuckoo hashing and Chained hashing has nearly perfect constant O(1) search time. It is because the benchmark we use is uniform distribution and these 2 hashing can dispatch keys into equally buckets.
Linear and double hashing increases time complexity as loading factor increases. They are close to be proportional because we have to fetch more continuous valid keys until we get the right one.

* Delete
![uniform_delete](/assets/uniform_delete.png)
Double hashing needs to adjust its keys and we can see the time complexity goes up as loading factor increase. But it grows very slowly and we can treat it as constant.
Cuckoo hashing doesn't have obvious time change as loading factor changes.
Linear and chained hashing needs to visited more keys to find the right key for deletion and the time complexity increases severely as loading factor increases.

We can observe the jitter in the graph. It can explain worst case analysis because the time complexity could rise abruptly when worst case happens.But amortized time complexity is still relatively constant.

# Conclusion
We can conclude linear and double hashing are suitable when loading factor is relatively small because these 2 method have small initial cost.
Cuckoo hashing can resist the change of loading factor and it is the most general use.
Chained hash is easy to implemented if we can't generate independent hash function for cuckoo hashing.

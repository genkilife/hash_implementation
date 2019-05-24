#include <iostream>
#include <cstdlib>
#include "test_util.h"

/*
	We have constraints:
	* Keys are not duplicated
	* Key is in range (0, 2^30-1)
	* Delete must success and key always exist
*/

RC genDistinctKeys(KeyType* keys, unsigned int keySize){
	srand(0);
	unsigned int cnt = 0;
	unsigned int idx;

	KeyType r;
	while(cnt < keySize){
		r = rand() % (MODPRIME*MODPRIME);
		// Find r in keys
		for(idx=0; idx < cnt; idx++){
			if(r == keys[idx]){
				break;
			}
		}
		if(idx == cnt){
			keys[cnt++] = r;
		}
	}

	return SUCCESS;
}

RC genCollideKeys(KeyType* keys, unsigned int keySize){
	srand(0);
	unsigned int cnt = 0;
	unsigned int idx;

	KeyType r;
	while(cnt < keySize){
		r = rand() % int(MODPRIME/1.05);
		// Find r in keys
		for(idx=0; idx < cnt; idx++){
			if(r == keys[idx]){
				break;
			}
		}
		if(idx == cnt){
			keys[cnt++] = r;
		}
	}

	return SUCCESS;
}

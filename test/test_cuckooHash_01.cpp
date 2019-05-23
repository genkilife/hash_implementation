#include "test_util.h"
#include "CuckooHash.h"

using namespace std;

int main(){
	CuckooHash* ckPtr = new CuckooHash();
	ckPtr->printHashMethod();
	return 0;
}

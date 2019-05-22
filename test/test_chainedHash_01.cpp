#include "test_util.h"
#include "ChainedHash.h"

using namespace std;

int main(){
	ChainedHash* chPtr = new ChainedHash();
	chPtr->printHashMethod();
	return 0;
}

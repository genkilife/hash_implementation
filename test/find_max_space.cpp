#include <iostream>
#include <cstdlib>

using namespace std;

int main(){

	srand(0);
	unsigned int num = 0;
	unsigned int r = rand();
	while(1){
		if(num < r){
			num = r;
			cout<<num<<endl;
		}
		r = rand();
	}

	
	int* arr;
	int size=4096;
	while(1){
		arr = new int[size];
		cout<<"size: "<<size<<endl;
		delete [] arr;
		size += 4096;
	}

	return 0;
}

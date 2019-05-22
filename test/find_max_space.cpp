#include <iostream>

using namespace std;

int main(){
	
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

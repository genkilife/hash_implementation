#include <iostream>

using namespace std;

int main(){
	
	bool* arr;
	int size=32768;
	arr = new bool[size];
	cout<<"size: "<<size<<endl;
	
	for(int i=0; i<size; i++){
		arr[i] = false;
	}

	arr[0] = true;
	arr[1] = true;

	for(int i=2; i<size; i++){
		for(int j=i*2; j<size; j+=i){
			arr[j] = true;
		}
	}
	int prime=0;
	for(prime=size-1; prime>2; prime--){
		if(arr[prime] == false){
			break;
		}
	}
	cout<<"Largest prime below 32768 is "<< prime <<endl;


	delete [] arr;

	return 0;
}

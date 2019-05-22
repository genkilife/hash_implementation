#include "LinearHash.h"

LinearHash::LinearHash(){
}

LinearHash::~LinearHash(){
}

RC LinearHash::create(){
	return SUCCESS;
}

RC LinearHash::insert(KeyType key, ValType val){
	return SUCCESS;
}

RC LinearHash::search(KeyType key){
	return SUCCESS;
}

RC LinearHash::delkey(KeyType key){
	return SUCCESS;
}

RC LinearHash::printHashMethod(){
	std::cout<<"Linear hash class is used!"<<std::endl;
	return SUCCESS;
}


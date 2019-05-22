#include "BasicHash.h"

BasicHash::BasicHash(){
}

BasicHash::~BasicHash(){
}

RC BasicHash::create(){
	return SUCCESS;
}

RC BasicHash::insert(KeyType key, ValType val){
	return SUCCESS;
}

RC BasicHash::search(KeyType key){
	return SUCCESS;
}

RC BasicHash::delkey(KeyType key){
	return SUCCESS;
}

RC BasicHash::printHashMethod(){
	std::cout<<"Basic hash class is used!"<<std::endl;
	return SUCCESS;
}


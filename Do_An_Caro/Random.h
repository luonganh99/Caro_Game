#pragma once
#include <iostream>
#include <time.h>
using namespace std;

class Random{
public:
	Random(){
		srand(time(NULL));
	}

	int Next(){
		return rand();
	}

	int Next(int ceiling){
		return Next() % ceiling;
	}
};
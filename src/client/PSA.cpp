//============================================================================
// Name        : PSA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "../constraint/seg.hpp"
#include "../constraint/datastructure2/constraintMaps.hpp"

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	//SEGraph seg("test1.json");
	ConstraintMaps constraintMaps("/Users/wangyifei/CLionProjects/PSA/test0.json");
	constraintMaps.print();
	return 0;
}

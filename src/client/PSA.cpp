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
#include "../constraint/pseudoPC.hpp"
#include "../constraint/datastructure2/constraintMaps.hpp"

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	SEGraph seg("/Users/wangyifei/CLionProjects/PSA/test4.json", "/Users/wangyifei/CLionProjects/PSA/func2indexMap");
	//ConstraintMaps constraintMaps("/Users/wangyifei/CLionProjects/PSA/test4.json");
	//constraintMaps.print();
	PseudoPC ppc=PseudoPC("[(3,0), (3,2)]");
    RealPC rpc=seg.retrieveConstraint(ppc);
	cout<<rpc.getConstraint();
	return 0;
}

/*
	File: kruskals.cpp
	Author: Melchisedek Dulcio
	Descr: Calculates the minimum weight spanning tree of a connected graph
*/
#include "multilist.h"
#include "dj.h"

using namespace std;
int main(){
	Multilist<int> ml(cin);
	int min = 0;
	min = ml.kruskals();
	cout << "The total of the MWST is " << min << ".\n";
	return 1;
}
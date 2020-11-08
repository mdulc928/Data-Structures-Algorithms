#include "adjlist.h"
#include "adjmatrix.h"
#include "multilist.h"
#include<iostream>


int main(){
	int src, dst, wght = 0;
	
	Adjlist adjl();
	
	while(cin >> src >> dst >> wght){
		adjl.addEdge(src, dst, wght);
		cout << "Source: " << src << " Dest: " << dst << " Weight: " << wght << endl; 
	}
	return 1;
}
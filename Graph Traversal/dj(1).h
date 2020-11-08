/*
	File: dj.h
	Author: Melchisedek Dulcio
	Descr: Contains an implementation of a Partition aka Disjoint set
*/
#ifndef PARTITION_H
#define PARTITION_H
#include<map>
#include<iostream>

using namespace std;
template<typename T>
class Partition {
	map<T, int> parent;
	map<T, T> sets;
	unsigned int nSets;
public:
	Partition() { ; } //Initialize parents to -1
	//Constructor
	unsigned int NumberOfSets() const { return nSets; }
	
	// return the root of the tree containing k
	T find(T k) {
		if(sets.find(k) != sets.end()){//it is in sets
			while(sets[k] != -1){
				k = sets[k]; //goes through until it reaches a parent
			}
		}else{//element is not yet in sets
			sets[k] = -1;
			parent[k] = 1;
		}		
		return k;
	}
	
	// merge the set containing a with the set containing b
	bool merge(T a, T b) {
		T aa = a, bb = b;
		a = find(a);
		b = find(b);
		
		if(a == b){return false; }//parent[a];}
		
		if(parent[a] >= parent[b]){
			parent[a] += parent[b];
			sets[b] = a;
			sets[bb] = a;
			return true; //parent[a];
		}else if(parent[b] > parent[a]){
			parent[b] += parent[a];
			sets[a] = b;
			sets[aa] = b;
			return true; //parent[b];
		}
		
		return false;//something greater than 0
	}
	//void clear(){
	~Partition(){
		sets.erase(sets.begin(), sets.end());
		parent.erase(parent.begin(), parent.end());
	}
};

#endif
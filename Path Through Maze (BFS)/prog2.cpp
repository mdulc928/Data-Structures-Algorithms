/*
	File: prog2.cpp
	Author: Melchisedek Dulcio (mdulc928)
	Class: CpS210
	Descr: Contains implementation to find the shortest Path Thru a Maze
*/

#include "maze.h"
#include "stdio.h"
#include <cstring>
#include <fstream>

//finds the number of exits in the maze;
void findExits(const int r, const string l, int &numExits){
	if(r == 1){
		numExits = count(l.begin(), l.end(), '0');
	}
	else{
		if(l[0] == '0' || l[l.size() - 1] == '0'){
			numExits++;
		}
	}
}

//resizes my vector containing the initial values;
void resizeV(vector<char> v, const int c){
	if(v.size() + c >= v.capacity()){
		v.resize(v.capacity()/2 + v.capacity());
	}
}

void addS(vector<char> &v, const string ss){
	for(char s : ss){
		v.push_back(s);
	}
}

int main(int argc, char *argv[]){
	
	if(argc < 2){
		cout << "Usage: prog2 <filename>" << endl;
		exit(1);
	}
	
	fstream mz(argv[1]);
	if(!mz){
		cerr << "Sorry couldn't find the file: " << argv[1] << endl;
		exit(1);
	}
	
	bool ent = false;		//true when is found
	string rows, temp;
	int rw = 0, cl = 0, entPs = 0, /*exPs = 0*/ exits = 0;
	vector<char> m;
	
	
	//cout << "Done initializing vars" << endl;
	
	while(getline(mz, rows)){
		
		if(rows.size() == 0){
			break;
		}
		temp = rows; 			//designed to hold the last value of the of 
		cl = rows.length();		
		rw++;
		
		if(ent == false){
			entPs = rows.find('E');	
			if((unsigned int)entPs != string::npos){			
				entPs = cl * (rw - 1) + entPs;
				ent = true;
			}
		}

		findExits(rw, rows, exits);
		
		resizeV(m, cl);
		addS(m, rows);
	}
	mz.close();
	
	
	if(exits == 0){
		findExits(1, temp, exits);
	}
	if(exits == 0){
		cout << "There is no exit in the maze, sadly." << endl;
		exit(1);
	}
	
	Maze menace(m, rw, cl, entPs);
	try{
		menace.search_Maze();
	}catch(string e){
		cout << e << endl;
		exit(1);
	}
		
	menace.display(cout);
	
	m.clear();
	
	cout << "Rows: " << rw << endl << "Cols: " << cl << endl;
	cout << "Entrance: " << entPs << endl << "Num Exits: " << exits;
	
	return 0;
}
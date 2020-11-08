/* gol.cpp : This file contains implementation of the Game of Life by John H. Conway. 
*/

#include "pch.h"
#include <iostream>
#include "GenBoard.h"
//#include "Counter.h"

int main()
{
	int gens, N, M = 0 ; //number of generations, and dimensions
	string rps = "";
	cout << "Would you prefer a rectangular board or a square one? (r/s): ";
	cin >> rps;
	if (rps == "r") {
		cout << "\nEnter the number of rows: ";
		cin >> N;
		cout << "\nEnter the number of columns: ";
		cin >> M;
	}
	else if (rps == "s") {
		cout << "\nEnter size: ";
		cin >> N;
	}
	else {
		cout << "\nWoops.Not a valid entry.";
		exit(1);
	}

	cout << "Enter the number of generations: ";
	cin >> gens;

	if (M != 0) {
		square<int> sq(N, M);
		for (int i = 0; i < (gens - 1); i++) {
			cout << "\n\n";
			sq.generate();
			
		}
	}
	else {
		square<int> sq(N);
		for (int i = 0; i < (gens - 1); i++) {
			cout << "\n\n";	
			sq.generate();
			
		}
	}
	
	

}
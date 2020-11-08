#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <cmath>
//#include "Counter.h"
#define in :

using namespace std;

template <typename T>
class square {
	public:
		const int N, M;
		bool begin = false;
		
		map<int, string> Counters;

		//generate random Counters;
		void firstGen() {			
			
			int numCells = N * M; 
			int lower = (int)ceil((numCells / 2)) - (M / 2);

			int cnt = 0;

			int numOfCounters = rand() % (int)ceil((M/2)) + lower;

			while (cnt < numOfCounters) {
				int place = rand() % numCells;

				if (Counters.count(place) == 0) {
					Counters[place] = "X";
					cnt++;
				}
			}
			int s = Counters.size();
			markedForDeletion.resize(s);
			updateCountersCells();

			print(cout);
		}

		std::ostream &print(std::ostream &os, char sep = '|') {
			for (int row = 0; row < N; ++row) {
				os << sep << chars[at(row, 0)];
				for (int col = 1; col < M; ++col) {
					os << sep << chars[at(row, col)];
				}
				os << std::endl;
				os << string(M * 2, '-') << endl;
			}
			return os;
		}

		void updateCountersCells(){
			for (int i = 0; i < markedForDeletion.size(); ++i) {
				Counters.erase(markedForDeletion[i]);
			}

			
			markedForDeletion.resize(0);

			delete[] cells;
			cells = new T[N*M];
			for (int k = 0; k < N*M; cells[k++] = 0) { ; }

			for (auto &k : Counters) {
				cells[k.first] = 1;
			}
		}

		/*
		I will need two boards: an initial and next; assign initial to next at the end of loop
		Generate: loops through cells and based on the rules of survival add or remove Counters.
		have a temporary map to hold the new Counters, add them to Counters after loop and then destroy map
		*/

		// Figure out random value generator

		void generate() {
			int cntsz = Counters.size();
			markedForDeletion.resize(cntsz);
			int delcnt = 0;

			for (int cell = 0; cell < (N*M); cell++) {
				int fellows = CheckAround(cell);

				if (fellows == 3) {
					Counters[cell] = "X";
				}else if(fellows > 3 || fellows < 2){
				    if (cells[cell] == 1) {
						Counters.erase(cell);
						markedForDeletion[delcnt] = cell;
						delcnt++;
					}
				}
			}
			updateCountersCells();
			print(cout);
		}

		
		int CheckAround(int cell) {
			int others = 0;
			vector<int> toCheck;
			bool frames = false;

			if (cell < M || cell >= M * (N - 1) || cell % M == 0 || cell % M == M - 1 ) {
				frames = true;
			}

			if (frames) {
				toCheck = whichFrame(cell);
			}
			else {
				int up = cell - M;
				int down = cell + M;
				toCheck = { cell - 1, cell + 1, up, up - 1, up + 1, down, down - 1, down + 1 };
			}

			for (int i = 0; i < toCheck.size(); i++) {
				int num = toCheck[i];
				if (cells[num] == 1) {
					others++;
				}
			}

			return others;
		}

		//TODO: Implement frame logic
		vector<int> whichFrame(int cell) {
			vector<int> frameEnviron(8);
			int up = cell - M;
			int down = cell + M;

			map<int, vector<int>> corners = { {0,{ down, down + 1, cell + 1 }}, {M - 1, { down, down - 1, cell - 1 }}, {(M * (N - 1)), { up, up + 1, cell + 1 }}, {(N * M - 1), { up, up - 1, cell - 1 }} };

			if (corners.count(cell)) {
				frameEnviron = corners[cell];
			}
			else if((cell < M || cell > M * (N - 1)) && (cell != 0 || cell != M - 1 || cell != (M * (N - 1)) || cell != (N * M - 1))) {
				if (cell < M) {
					frameEnviron = { cell - 1, cell + 1, down, down + 1, down - 1 };
				}
				else{
					frameEnviron = { cell - 1, cell + 1, up, up + 1, up - 1 };
				}
			}
			else {
				if (cell % M == 0) {
					frameEnviron = { cell + 1, up, up + 1, down, down + 1 }; 
				}
				else {
					frameEnviron = { cell - 1, up, up - 1, down, down - 1 };
				}
			}

			return frameEnviron;
		}

	private:
		T *cells;
		char chars[2] = {' ', 'X'};
		vector<int> markedForDeletion;

	public:

		//Constructors
		square(int n, bool zero = true) :
			N(n), M(n), cells(new T[n*n]) 
		{
			if (zero) {
				for (int k = 0; k < n*n; cells[k++] = 0) { ; }
			}
			firstGen();
			begin = true;
		}

		square(int r, int c, bool zero = true):
			N(r), M(c), cells(new T[r*c]), markedForDeletion(r*c)
		{
			if (zero) {
				for (int k = 0; k < r*c; cells[k++] = 0) { ; }
			}
			firstGen();
			begin = true;
		}
		~square() { delete[] cells; markedForDeletion.resize(0); }; //Destructor

		T &at(int row, int col) {
			return cells[N*row + col];
		}

		const T& at(int row, int col) const {
			return cells[N*row + col];
		}
}; // end of class square



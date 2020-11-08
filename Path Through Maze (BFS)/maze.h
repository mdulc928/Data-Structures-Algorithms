/*
	File: maze.h
	Author: Melchisedek Dulcio (mdulc928)
	Descr: contains definition for the class maze;
*/
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <queue>
#include <map>

using namespace std;
typedef long long dimens;
/*TODO: 
	Check to see that each maze has a solution
	Don't forget to think about the extreme cases
	Keep a queue so long as the 
	
	Have a method to read the file into a vector and then store it into an array;
	
	Have a struct Node to that has a value, a prev, loc
 *Output:
	List of ordered pairs (x, y)
	Original maze with indications of path(maybe arrows: ^v<>)
	
 *Input:
	1. Use getline(blah) to get the columns - done
	2. increment rows each time you read - done

 * Implement: 
	1. Check if it has a solution: if(n(number of 0's on edge) == 0 
		return no solution if n == 0 zero, or choose the best and no need to indicate that there were multiple exits - Done
	2. Check if any line contains E, which will be your entrance;
		Once found be sure to check that it is not walled in - Can't do outside of class
	3. Check first elem and last to  see if they each equal 1. - done
	
	Return index of either,
	bool exit_found, entrance_found
 * Think about this: a queue of Nodes where you will be linking the next node to the previous one? Maybe :)
	
*/

//a Node holds the address of the Node pointing to it.
struct Node {
	int value = 0; 
	int loc = 0;	//location in array
	//struct Node* prev = nullptr;	//Node pointing to it;
};

//class Queue - implements queue class with a vector
template<typename T>
class Queue{
	private:
		vector<T> v;
		long frnt = 0, bck = -1;
	public:
		Queue(){;}
		
		const T& front() {return v[frnt];}
		const T& back() {return v[bck];}
		
		void push(const T& val){v.push_back(val); bck++;}
		void pop() {frnt++;}
		bool empty() {return ( 0 > (bck - frnt));};
		
		~Queue(){v.clear(); bck = -1; frnt = 0;}
	
}; //end of class


class Maze {
	
	private:	
		const dimens Row, Col; //set col to strlen(getline(first_line)), and increment row for each line I read
		Node* maze;
		Node* finalM;
		int entrance;
		Node exit;
		bool exit_found = 0;

	
		//Do I want to returnt the node or the value in the Node? Where will I need to use this?
		Node &at(int row, int col) {
			return maze[Row*row + col];
		}

		const Node& at(int row, int col) const {
			return maze[Row*row + col];
		}
		
		//reads a Maze into an array an returns to 
		void readMaze(vector<char> raw){
			map<char, int> numVals = {{'1', 1}, {'0', 0}, {'E', -1}};
			for(int i = 0; i < raw.size(); i ++){
				Node n = {numVals[raw[i]], i};
				Node m = {raw[i], i};
				maze[i] = n;
				finalM[i] = m;
			}		
		}
		
		//find the row and column of the node for me
		int mRow(Node n){ return n.loc/Row;}
		int mCol(Node n){ return n.loc%Col;}
		
		//checks if Node is an exit
		void Exit(const Node& nde){
			if(mRow(nde) == 0 || mRow(nde) == (Row-1) || mCol(nde) == 0 || mCol(nde) == (Col - 1)){
				exit = nde;
				exit_found = 1;
			} 
		}
		

		//checks the nodes up, down, left and right of it and links if it has not been linked or its value is '0'
		void BreadthLink(Node n, Queue<Node> &nxt, int num){
			cout << "Breadthandlink" << endl;
			int nrow = mRow(n), ncol = mCol(n), up = nrow - 1, down = nrow + 1, left = ncol - 1, right = ncol + 1;
			
			if(up > -1 && at(up, ncol).value == 0){
				nxt.push(at(up, ncol));
				Exit(at(up, ncol));
				at(up, ncol).value = num;
			}//up
			if(down < Row && at(down, ncol).value == 0){
				nxt.push(at(down, ncol));
				Exit(at(down, ncol));
				at(down, ncol).value = num;
			}//down
			if(left > - 1 && at(nrow, left).value == 0){
				nxt.push(at(nrow, left));
				Exit(at(nrow, left));
				at(nrow, left).value = num;
			}//left
			if(right < Col && at(nrow, right).value == 0){
				nxt.push(at(nrow, right));
				Exit(at(nrow, right));
				at(nrow, right).value = num;
			}//right
		}
		
		void traceBackOut(){
			stack<int> coords;
			
			Node n = exit;
			coords.push(n.loc);
			
			int nrow = mRow(n), ncol = mCol(n), up = nrow - 1, down = nrow + 1, left = ncol - 1, right = ncol + 1;
			
			int counter = n.value, nextLoc = n.loc;
			
			while(counter > -1){
				Node p;
				if(right < Col && (at(nrow, right).value == (counter -1) || at(nrow, right).value == - 1)){
					p = at(nrow, right);
					nextLoc = p.loc;
					coords.push(nextLoc);
					nrow = mRow(p), ncol = mCol(p), up = nrow + 1, down = nrow - 1, left = ncol - 1, right = ncol + 1;
					counter -= 1;
					n = p;
					continue;
				}
				if(left > - 1 && (at(nrow, left).value == (counter-1) || at(nrow, left).value == - 1)){
					p = at(nrow, left);
					nextLoc = p.loc;
					coords.push(nextLoc);
					nrow = mRow(p), ncol = mCol(p), up = nrow + 1, down = nrow - 1, left = ncol - 1, right = ncol + 1;
					counter -= 1;
					n = p;
					continue;
				}
				if(down < Row && (at(down, ncol).value == (counter - 1) || at(down, ncol).value == - 1)){
					p = at(down, ncol);
					nextLoc = p.loc;
					coords.push(nextLoc);
					nrow = mRow(p), ncol = mCol(p), up = nrow + 1, down = nrow - 1, left = ncol - 1, right = ncol + 1;
					counter -= 1;
					n = p;
					continue;
				}
				if(up > -1 && (at(up, ncol).value == (counter - 1) || at(up, ncol).value == - 1)){
					p = at(up, ncol);
					nextLoc = p.loc;
					coords.push(nextLoc);
					nrow = mRow(p), ncol = mCol(p), up = nrow + 1, down = nrow - 1, left = ncol - 1, right = ncol + 1;
					counter -= 1;
					n = p;
					continue;
				}
				
				nextLoc = n.loc;
				counter -= 1;				
			}
			
			while(!coords.empty()){
				finalM[coords.top()].value != 69 ? finalM[coords.top()].value = 88: NULL;
				if(coords.top() == exit.loc){
					finalM[coords.top()].value = 64;
				}					
					
				cout << "(" << coords.top()/Row << "," << coords.top()%Col << ")" << endl;
				coords.pop();
			} 
		}
		
	public:
		//maybe try this, but we will see;
		
		//prints the Maze
		ostream &display(ostream &os, char sep = '|'){
			int rw = 0, cl = 0, inc = 0;
			
			for(int i = 0; i < (Row * Col); i++){
				if(i%Col == 0){					
					os << endl << string(Col * 2, '-') << endl;
					if(inc != 0){++rw;}
					cl = 0;
					++inc;
				}
				os << sep << (char)finalM[i].value;
				++cl;
			}
			os << endl << string(Col * 2, '-') << endl;
			return os;
		}
		
		//Constructor for Maze class
		Maze(vector<char> rawMaze, dimens r, dimens c, int ent): Row(r), Col(c), entrance(ent) {
			maze = new Node[r*c];
			finalM = new Node[r*c];
			readMaze(rawMaze);
		}
		
		//this is where I actually build the queues to search the maze, once I have the exit though
		//I will stop and build a stack to store my coordinates as I backtrack to the entrance. 
		void search_Maze(){
			Queue<Node> prevQ;
			Queue<Node> nextQ;
						
			Node& entr = at(entrance/Row, entrance%Col);
			prevQ.push(entr);
			
			int counter = 2;
			
			while(!prevQ.empty() && exit_found == 0){
				cout << "In search" << endl;
				BreadthLink(prevQ.front(), nextQ, counter);
				prevQ.pop();
				
				if(prevQ.empty()){
					while(!nextQ.empty()){
						prevQ.push(nextQ.front());
						nextQ.pop();
					}
					counter++;
					
				}
			}
			if(exit_found == 0){
				throw string("There is no exit in the maze, sadly.");
			}
			
			exit.value = counter;
			
			traceBackOut();
			
		}
		
		~Maze(){delete [] maze; delete [] finalM;}//destructor;		
};

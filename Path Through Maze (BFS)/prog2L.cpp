#include<iostream>
#include<string>
using namespace std;

class Maze{
private:
	struct Node{
		char val = 0;
		int loc;
		Node* prev = nullptr;
	}; //end of struct 
	
	int rw = 0, cl = 0, ent_pos = 0 ;
	string rows;
public:
	Maze(istream& is){
		is >> rows;
		for(;rows[cl] != '\0'; ++cl){;}
		++rw;
		
		size_t c = rows.find('e');
		size_t C = rows.find('E');
		if(c != string::npos){
			ent_pos = (rw - 1)* (cl) + c;
		}
		if(C != string::npos){
			ent_pos = (rw - 1) * cl + C;
		}
		while(is >> rows){
			++rw;
			
			if(c == string::npos){
				c = rows.find('e');
				if(c != string::npos){
					ent_pos = (rw -1) * cl + c;
				}
			}
			if(C == string::npos){
				C = rows.find('E');
				if(C != string::npos){
					ent_pos = (rw -1) * cl + C;
				}
			}
		}
	}
	
	
	
	int rdimens(){
		return rw;
	}
	int cdimens(){
		return cl;
	}
	int ent(){
		return ent_pos;
	}
	
	
	
	
}; //end of class Maze

int main(){
	Maze m(cin);
	
	cout << "Row: " << m.rdimens() << " Col: " << m.cdimens() << "Entrance Pos: " << m.ent() << endl;
	return 0;
}
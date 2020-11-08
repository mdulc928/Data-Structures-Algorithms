/*
	Author: Melchisedek Dulcio	(mdulc928)
	File: obst_p3.cpp
	Descr: Contains implementation of a optimal binary search tree used to calculate the
			optimal cost of frequencies and which item should be at the top of the tree.
*/

//#include<pair>
#include<ostream>

using namespace std;
/*
	class obst:
		methods: insert, remove, optimize, balance, print
		attributes:	size, root
*/

template<typename T>
class Obst{	
	struct Node{
		T key = nullptr;
		int freq, depth = 0;
		Node *left, *right;
		
		Node() {left = nullptr; right = nullptr;}
		Node(T _key, int frq = 0): key(_key), freq(frq) {left = nullptr; right = nullptr;}
		
		~Node(){
			if(left != nullptr){left->~Node();}
			if(right != nullptr){right->~Node();}
			left = nullptr; right = nullptr;
		}//destructor
		
		ostream &print(ostream &os){
			//os << "Children: " << endl;
			if(left != nullptr){
				//os << "Left: " << endl;
				left->print(os);
			}
			if(right != nullptr){

				right->print(os);
			}
			os << "Key: " << key << '\t' << "Cost: " << freq << "\t Depth: " << depth << endl;
			return os;
		}//print node and children;
		
		int costCalc(){
			int lsum = 0, rsum = 0;
			if(left != nullptr){
				lsum = left->costCalc();
			}
			if(right != nullptr){
				rsum = right->costCalc();
			}
			return ((depth * freq) + lsum + rsum);
		}
	};
	
	private:
		Node *root = nullptr;
		int insertn(Node *pos, pair<T, int> obj){
			if(empty()){root = new Node(obj.first, obj.second); ++nSz; fxCost += root->freq; return 1;}//not at root;
			while(true){
				if(obj.first > pos->key){
					if(pos->right == nullptr){
						pos->right = new Node(obj.first, obj.second);
						++nSz;
						pos->right->depth = pos->depth + 1;
						fxCost += pos->right->freq;
						break;
					}else{
						pos = pos->right;
					}
				}else if(pos->key > obj.first){
					if(pos->left == nullptr){
						pos->left = new Node(obj.first, obj.second);
						++nSz;
						pos->left->depth = pos->depth + 1;
						fxCost += pos->left->freq;
						break;
					}else{
						pos = pos->left;
					}
				}else{
					return 0;
				}
			}			
			return 1;
		}
	public:
		int nSz = 0; 	//number of nodes
		int	fxCost = 0;
		
		Obst(){;}		//constructor for optimal binary search tree
		~Obst(){root->~Node();}		//must think about how to deallocate each struct
		
		int insert(pair<T, int> obj){
			int s = insertn(root, obj);
			return s;
		}
		
		bool empty() {return (root == nullptr);}
		int calcCostO(){
			return (root->costCalc() + fxCost);
		}
		ostream &printO(ostream &os){
			os << "Optimal Binary Search Tree: " << endl;
			return root->print(os);
		}
};


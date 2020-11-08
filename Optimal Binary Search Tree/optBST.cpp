/*
	Author: Melchisedek Dulcio	(mdulc928)
	File: optBST.cpp
	Descr: Calculates the optimal binary tree made from the data set.
*/

#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

pair<string, int> buildSheet(map<string, int> wf, map<string, int> sum, int size){
	vector<int> col(size + 1, 0);
	vector<vector<int>> sheet(size + 1, col);
	vector<string> col2(size + 1, "0");
	vector<vector<string>> wrdsheet(size + 1, col2);
	vector<string> heads;
	vector<int> sumsAll;
	
	int min = 0, i = 0, r = 0, c = 0, delt = 3;
	string minstr = "0";
	
	for(auto p : sum){
		sumsAll.push_back(p.second);
		heads.push_back(p.first);
		
		sheet[i][i + 1] = wf[p.first];
		wrdsheet[i][i + 1] = p.first;
		++i;
		if(min == 0){
			i = 0;
			++min;
		}
	}
	
	r = 0; c = 2; i = 1; int cvar = 0, rvar = 0, rfac = 0;
	while(delt < size + 2){
		while(c < size + 1){
			for(; i < delt; ++i){
				
				cvar = c - i;
				rvar = r + (delt - i);
				
				
				if(rfac == 0){
					min = sheet[r][cvar] + sheet[rvar][c];
					minstr = heads[cvar + 1];
					++rfac;
				}
				if((sheet[r][cvar] + sheet[rvar][c]) < min){
					min = sheet[r][cvar] + sheet[rvar][c];
					minstr = heads[cvar + 1];
				}
			}			
			i = 1;

			sheet[r][c] = sumsAll[c] - sumsAll[r] + min;
			wrdsheet[r][c] = minstr;
			++r; ++c;
			rfac = 0;
		}
		++delt;
		r = 0; c = delt - 1;
	}
	
	pair<string, int> p;
	p.first = wrdsheet[0][size];
	p.second = sheet[0][size];
	
	wrdsheet.clear();
	sheet.clear();
	wrdsheet.resize(0);
	sheet.resize(0);
	col.clear();
	col.resize(0);
	col2.clear();
	col2.resize(0);
	heads.clear();
	heads.resize(0);
	sumsAll.clear();
	sumsAll.resize(0);
	
	return p;
	
}//simulate a sheet like the one in the excel;

int main(){	
	int freq;
	string word = "", prev = "";
	map<string, int> sums;
	map<string, int> wrdFrq;
	pair<string, int> p;
	
	while(cin >> word >> freq){
		wrdFrq[word] = freq;
	}
	
	for(auto p: wrdFrq){
		sums[p.first] = p.second + sums[prev];
		prev = p.first;
	}
	
	p = buildSheet(wrdFrq, sums, wrdFrq.size());
	cout << p.first << " " << p.second << endl;
	sums.clear();
	wrdFrq.clear();
	
	return 1;
};
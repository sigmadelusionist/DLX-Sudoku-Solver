#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")//use pragma's only for GCC compilers

using namespace std;

int a;
char bn,cr;
bool fi,valid;
vector<vector<int>> sudoku(9,vector<int>(9));
vector<vector<bool>> row(9,vector<bool>(10)),col(9,vector<bool>(10)),box(9,vector<bool>(10));

bool rec(int l){
	int i=l/9,j=l%9;
	if(l==81){
		cout<<'\n';
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++)
				cout<<sudoku[i][j]<<' ';
			cout<<'\n';
		}
		return 1;
	}
	if(sudoku[i][j])
		return rec(l+1);
	for(int n=1;n<10;n++){
		if(!row[i][n] && !col[j][n] && !box[3*(i/3)+(j/3)][n]){
			sudoku[i][j]=n;
			row[i][n]=col[j][n]=box[3*(i/3)+(j/3)][n]=1;
			if(rec(l+1))
				return 1;
			sudoku[i][j]=0;
			row[i][n]=col[j][n]=box[3*(i/3)+(j/3)][n]=0;
		}
	}
	return 0;
}

void solve(){
	cout<<"Hey!! Welcome to the Game of Sudoku 9x9.\n\n";
	cout<<"Enter the initial state of game\nPress 0 or . for empty positions \nand give a space between each entry.....\n";
	cout<<"Press s to start..\n";
	fi=0;valid=1;
	do{
		if(fi)cout<<"Invalid entry, try again..\n";
		cin>>bn;
		fi=1;
	}while(bn!='s');
	cout<<'\n';
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fi=0;
			do{
				if(fi)cout<<"Invalid entry, try again..\n";
				cin>>cr;
				fi=1;
				if(cr=='.')//for . inputs
					a=0;
				else a=cr-'0';
			}while(a<0 || a>9);
			sudoku[i][j]=a;
			if(a && (row[i][a] || col[j][a] || box[3*(i/3)+(j/3)][a]))
				valid=0;
			row[i][a]=col[j][a]=box[3*(i/3)+(j/3)][a]=1;
		}
	}
	if(valid && rec(0))
		cout<<"\nThank you for playing with us.\n";
	else cout<<"\nNot possible..\n";

}

//Think twice code once

signed main(){

	solve();
}



/*
Algorithm's to solve Sudoku
• Brute force
• Simplex Algorithm(If there is more than one solution (non-proper Sudokus) the simplex algorithm will generally yield a solution with fractional amounts of more than one digit in some squares.)
• Integer Linear programming(The logical rules used by presolve techniques for the reduction of LP problems include the set of logical rules used by humans to solve Sudokus.)
• DL-X Algorithm
*/
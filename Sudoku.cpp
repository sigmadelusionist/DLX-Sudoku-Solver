#include "SudokuSolver.h"

using namespace std;

signed main(){
	Solver game;
	game.welcome();

	cout<<"Press enter to Continue.....";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<<'\n';

	game.instructions();

	cout<<"Press enter to Continue.....";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<<'\n';
	
	if(game.takeInput()){
		cout<<"Validating Sudoku...\n\n";
		if(game.validate()){
			cout<<"Validated Succesfully..\n\n";
			game.solve();
		}else 
			cout<<"Invalid Sudoku...\n\n";
	}

	cout<<"\nPress a number to exit..";
	game.intIp();

	return 0;
}

//g++ Sudoku.cpp DancingLinks.cpp Node.cpp SudokuSolver.cpp
//cd cpp files\projects\sudoku
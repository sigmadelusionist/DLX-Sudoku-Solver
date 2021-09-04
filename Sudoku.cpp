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
			clock_t start_t = clock();
			game.solve();
			clock_t end_t = clock();
			cout<<'\n'<<"Hurray!!\nSolved in: "<<(double) (end_t - start_t) / CLOCKS_PER_SEC<<'\n'<<" sec\n";
		}else 
			cout<<"Invalid Sudoku...\n\n";
	}

	cout<<"\nPress a number to exit..\n";
	game.intIp();

	return 0;
}

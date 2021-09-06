#include "SudokuSolver.h"

Solver::Solver(){
	bmk=false;//by default not benchmarking
}

void Solver::ask(){
	char a;
	std::cout<<"Are you benchmarking??(Y/N): ";
	reask:
	std::cin>>a;
	if(a=='Y'){
		std::cout<<"How many Sudoku??:";
		n=intIp();
		bmk=true;
		time = 0.0;
	}else if(a=='N'){
		n=1;
	}else{
		std::cout<<"Y/N: ";
		goto reask;
	}
}

void Solver::welcome(){
	printf("----------------------------------------------------\n");
	printf("|===================== SUDOKU =====================|\n");
	printf("|                                                  |\n");
	printf("|             Welcome to Sudoku Solver             |\n");
	printf("|                                                  |\n");
	printf("----------------------------------------------------\n\n\n");

	printf("----------------------------------------------------\n");
	printf("|================== About Sudoku ==================|\n");
	printf("----------------------------------------------------\n");
	printf("|                                                  |\n");
	printf("| 1. Board of Sudoku is of size nxn, where n should|\n");
	printf("|    be a perfect square.                          |\n");
	printf("| 2. In each row of length n all numbers from 1 to |\n");
	printf("|    n should be present once.                     |\n");
	printf("| 3. In each column of length n all numbers from   |\n");
	printf("|    1 to n should be present once.                |\n");
	printf("| 4. In each sub-square of size n(or of side length|\n");
	printf("|    sqrt(n)) all numbers from 1 to n should be    |\n");
	printf("|    present once.                                 |\n");
	printf("----------------------------------------------------\n\n");

	printf("Sample: Size 4x4\n\n");
	printf("2 1 3 4\n");
	printf("4 3 1 2\n");
	printf("1 2 4 3\n");
	printf("3 4 2 1\n\n");
}

void Solver::instructions(){
	printf("----------------------------------------------------\n");
	printf("|================== Instructions ==================|\n");
	printf("----------------------------------------------------\n");
	printf("|                                                  |\n");
	printf("| 1. Give nxn entries with a space in between.     |\n");
	printf("| 2. Break the line after each n entries.          |\n");
	printf("| 3. Give 0's in place of empty cells.             |\n");
	printf("----------------------------------------------------\n\n");
}

int Solver::intIp(){
	int n;
	while(!(std::cin>>n)){
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		printf("Invalid input, not an Integer!\n\nPlease try again.: ");
	}
	return n;
}

bool Solver::checkSize(int a){
	int i=1;
	while(i*i<=a){
		if(i*i==a)
			return true;
		i++;
	}
	return false;
}

bool Solver::takeInput(){
	if(!bmk){
	    printf("Please give the size of your Sudoku(a perfect square): ");
		size=intIp();
		while(size<0 || !checkSize(size)){
			printf("Invalid input!\nSize should be a perfect square.\n\nPlease try again.: ");
			size=intIp();
		}
	}
	else size=9;//bechmarking 9x9 Sudoku

	int s=size;

	sudoku=new int* [s];
	dlx.cover=new bool* [s*s*s];

	for(int i=0;i<s*s*s;i++){
		dlx.cover[i]=new bool [s*s*4];
		for(int j=0;j<s*s*4;j++)
			dlx.cover[i][j]=0;
	}
	
	if(!bmk)std::cout<<"\nStart giving entries line by line..\n";
	std::string sudoku_line;
	if(bmk)
		std::cin>>sudoku_line;
    for(int i=0;i<s;i++){
    	sudoku[i]=new int [s];
        for(int j=0;j<s;j++){
            if(!bmk){
            	sudoku[i][j]=intIp();
	            if(sudoku[i][j]<0 || sudoku[i][j]>s){
	                std::cout<<"Invalid entry at ("<<i<<','<<j<<") "<<sudoku[i][j]<<" is not in range 0 to "<<s<<"\n\n";
	                std::cout<<"Application terminated...\n\n";
	                return false;
	            }
	        }
	        else{
	        	sudoku[i][j]=(sudoku_line[i*s+j]=='.')?0:sudoku_line[i*s+j]-'0';
	        }
        }
    }
    std::cout<<'\n';
    return true;
}

bool Solver::validate(){
	//validating rows
	for(int i=0;i<size;i++){
		bool val[size+1];
		for(int j=0;j<=size;j++)
			val[j]=0;
		for(int j=0;j<size;j++)
			if(val[sudoku[i][j]]){
				printf("%d is repeated in row %d\n\n",sudoku[i][j],i+1);
				return false;
			}
			else if(sudoku[i][j]) val[sudoku[i][j]]=1;
	}

	//validating columns
	for(int i=0;i<size;i++){
		bool val[size+1];
		for(int j=0;j<=size;j++)
			val[j]=0;
		for(int j=0;j<size;j++)
			if(val[sudoku[j][i]]){
				printf("%d is repeated in column %d\n\n",sudoku[j][i],i+1);
				return false;
			}
			else if(sudoku[j][i]) val[sudoku[j][i]]=1;
	}

	//validating boxes
	int sq=round(sqrt(size));
	for(int i=0;i<size;i++){
		bool val[size+1];
		for(int j=0;j<=size;j++)
			val[j]=0;
		for(int j=0;j<size;j++){
			if(val[sudoku[sq*(i/sq)+j/sq][sq*(i%sq)+j%sq]]){
				printf("%d is repeated in box %d\n\n",sudoku[sq*(i/sq)+j/sq][sq*(i%sq)+j%sq],i+1);
				return false;
			}
			else if(sudoku[sq*(i/sq)+j/sq][sq*(i%sq)+j%sq]) val[sudoku[sq*(i/sq)+j/sq][sq*(i%sq)+j%sq]]=1;
		}
	}

	return true;
}

void Solver::solve(){

	clock_t start_t = clock();

	BuildMatrix();
	BuildCover();
	TransformToCurrentGrid();

	
	dlx.search(0,sudoku);
	clock_t end_t = clock();

	time = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	if(!dlx.isSolved){
		std::cout<<"No Solution!"<<'\n';
		time=0.0;
	}
	else print();
}

void Solver::BuildMatrix(){

	//Constraint I:only 1 value in a cell
	int j=0,counter=0;
	int s=size;
	for(int i=0;i<s*s*s;i++){
		dlx.cover[i][j]=1;
		counter++;
		if(counter>=s){
			j++;
			counter=0;
		}
	}

	//Constraint II: only 1 instance in a row
	int x=0;
	counter=1;
	for(j=s*s;j<2*s*s;j++){
		for(int i=x;i<counter*s*s;i+=s){
			dlx.cover[i][j]=1;
		}
		if((j+1)%s==0){
			x=counter*s*s;
			counter++;
		}else x++;
	}

	//Constraint III: only 1 instance in a column
	j=2*s*s;
	for(int i=0;i<s*s*s;i++){
		dlx.cover[i][j]=1;
		j++;
		if(j==3*s*s)
			j-=s*s;
	}

	//Constraint IV: only 1 instance in a box
	x=0;
	//s is a perfect square
	for(j=3*s*s;j<4*s*s;j++){//for nums 1 to s in a box for s boxes
		for(int k=0;k*k<s;k++){//for columns
			for(int l=0;l*l<s;l++){//for rows
				dlx.cover[x+ k*s + l*s*s][j]=1;
			}
		}

		x++;
		if((j+1)%s==0){
			x+=round(sqrt(s)-1)*s;
			if((j+1)%(int)(round(sqrt(s))*s) == 0){
				x+=round(sqrt(s)-1)*s*s;
			}
		}
	}
}

void Solver::BuildCover(){

	Node* header = new Node;
	header->l = header->r = header->u = header->d = header;
	header->size = -1;
	header->head = header;
	Node* prev = header;

	int s=size;

	//Linking all Column headers
	for(int i=0;i<s*s*4;i++){
		Node* newCol = new Node;
		newCol->size = 0;
		newCol->u = newCol->d = newCol;
		newCol->l = prev;
		newCol->r = header;
		newCol->head = newCol;
		prev->r = newCol;
		prev=newCol;

	}

	Node* colHead;
	int rowEl[3] = {0,0,0};//Num,R,C
	//Add a node for each 1 in dlx.cover
	for(int i=0;i<s*s*s;i++){
		colHead = header->r;
		prev = NULL;//empty row

		rowEl[0] = (rowEl[0])%s + 1;
		if(i%s==0){
			rowEl[2] = (rowEl[2])%s + 1;
			if(i%(s*s)==0)
				rowEl[1] = (rowEl[1])%s + 1;
		}

		for(int j=0;j<s*s*4;j++, colHead = colHead->r){
			if(dlx.cover[i][j]){
				Node* newNode=new Node;

				newNode->rowEl[0] =rowEl[0];
				newNode->rowEl[1] =rowEl[1];
				newNode->rowEl[2] =rowEl[2];

				colHead->size++;
				newNode->head=colHead;//head

				if(prev == NULL){
					prev=newNode;
					prev->r=newNode;//circular
				}

				newNode->l=prev;//1lrn
				newNode->r=prev->r;//2lrn

				newNode->d=colHead;//3udn
				newNode->u=colHead->u;//4udn

				newNode->r->l=newNode;//1lro
				prev->r=newNode;//2lro

				colHead->u->d=newNode;//3udo
				colHead->u=newNode;//4udo

				prev=newNode;//updating for next;
			}
		}
	}
	dlx.HeadNode = header;
}

void Solver::TransformToCurrentGrid(){

	for(int i=0;i<size;i++){//rowEl are 1 indexed
		for(int j=0;j<size;j++){
			if(sudoku[i][j]){
				Node* nh=NULL;//if not found
				//Although would be found in 1st s*s cols
				Node* nv=NULL;

				for(nh=dlx.HeadNode->r;nh!=dlx.HeadNode;nh=nh->r){//header traversal
					for(nv=nh->d;nv!=nh;nv=nv->d){//vertical traversal
						if(nv->rowEl[0]==sudoku[i][j] && nv->rowEl[1]==i+1 && nv->rowEl[2]==j+1){
							Node* nr=nv;
							do{
								dlx.coverCol(nr->head);
								nr=nr->r;
							}while(nr!=nv);
							goto Out;
						}
					}
				}

			}
			Out:
			;
		}
	}

}

void Solver::print(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			std::cout<<sudoku[i][j]<<' ';
		}
		std::cout<<'\n';
	}
}

void Solver::reset(){
	dlx.isSolved=false;
}

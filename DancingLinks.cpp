#include "DancingLinks.h"

DancingLinks::DancingLinks(){
	isSolved=false;
	HeadNode=&Head;	

}

void DancingLinks::coverCol(Node* col){
	col->l->r=col->r;
	col->r->l=col->l;//hide the column

	for(Node* nv=col->d; nv!=col; nv = nv->d){//vertical traversal
		for(Node* nh=nv->r; nh!=nv; nh = nh->r){//horizontal traversal
			nh->d->u = nh->u;
			nh->u->d = nh->d;

			nh->head->size--;
		}
	}
}

void DancingLinks::uncoverCol(Node* col){
	col->l->r=col;
	col->r->l=col;//unhide the column

	//here everything is done in exact reverse fashion
	//to retain the information and to avoid 
	//intermingling of pointers
	for(Node* nv=col->u; nv!=col; nv = nv->u){//reverse vertical traversal
		for(Node* nh=nv->l; nh!=nv; nh = nh->l){//reverse horizontal traversal
			nh->d->u = nh;
			nh->u->d = nh;

			nh->head->size++;
		}
	}
}

bool DancingLinks::search(int sc,int **sudoku){//source

	if(HeadNode->r==HeadNode){
		return isSolved=true;
	}

	//Choosing column deterministically
	//with lowest number of nodes
	Node* col=HeadNode->r;
	for(Node* nh=col->r;nh!=HeadNode;nh=nh->r)//traversing header
		if(nh->size < col->size)
			col=nh;

	coverCol(col);

	for(Node* nv=col->d;nv!=col;nv=nv->d){//traversing vertical
		for(Node* nh=nv->r;nh!=nv;nh=nh->r){//traversing horizontal
			coverCol(nh->head);
		}

		if(search(sc+1,sudoku)){
			sudoku[nv->rowEl[1]-1][nv->rowEl[2]-1]=nv->rowEl[0];
			return true;
		}

		for(Node* nh=nv->l;nh!=nv;nh=nh->l){//traversing horizontal
			uncoverCol(nh->head);
		}
	}

	uncoverCol(col);

	return false;
}
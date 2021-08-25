#include "Node.h"

class DancingLinks{
	public:
		DancingLinks();
		Node Head;
		Node* HeadNode;
		bool isSolved;
		bool **cover;

		void coverCol(Node*);
		void uncoverCol(Node*);
		bool search(int,int **);
};
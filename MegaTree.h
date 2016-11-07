//John McElvenny 
#ifndef __MEGATREE_H__
#define __MEGATREE_H__

#include <string>
#include "MegaNode.h"
using namespace std;

class MegaTree {
	public:
		void insert(string name, double vals[]);
		void preorder();
		MegaTree( int );
		MegaTree( int, string );
		~MegaTree ( );
		string nearestNode(double vals[]);
	private:
		MegaNode* balancehelper(MegaNode* n, item* items, int d);
		void inserthelper(string n, double vals[]);
		int dimension; //MegaTree is the root node
		MegaNode *root;
};

#endif
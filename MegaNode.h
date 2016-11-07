//John McElvenny 
#ifndef __MEGANODE_H__
#define __MEGANODE_H__

#include <string>
#include <iostream>
using namespace std;

typedef struct s_item {
	int k; //dimension to sort by
	string name;
	double* points;
	s_item() {
		k=0;
		name="";
		points = nullptr;
	}
	s_item(string n, int size) {
		k=0;
		name = n;
		points = new double[size];
	}
	void advance() {
		k++;
	}
} item;


class MegaNode {
	public:
		MegaNode(int dim, string name, double v[]);
		void setLeft( MegaNode* );
		void setRight( MegaNode* );
		void preorder(MegaNode* , int, int);
		MegaNode* insert(int d, string name, MegaNode* n, double vals[], int depth);
		void deleteNode(MegaNode* );
		MegaNode* insertbalanced(MegaNode* n, item* items, int d, int sz, int dim);
		string nearestNodeHelper(double cookie[], int d);
	private:
		string name;
		int dimension;
		double *vals;
		MegaNode *left, *right;

		friend ostream & operator<< ( ostream & , const MegaNode* );
};

#endif
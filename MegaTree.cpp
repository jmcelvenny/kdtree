//John McElvenny 
#include "MegaTree.h"
#include <iostream>
#include <fstream>

MegaTree::MegaTree(int dim) : dimension(dim) {
	root = nullptr;
}

void MegaTree::insert(string name, double vals[]) {
	inserthelper(name, vals);
}

void MegaTree::inserthelper(string name, double vals[]) {
	root = root->insert(dimension, name, root, vals, 0);
}

void MegaTree::preorder() {
	root->preorder(root, 0, -1);
}

MegaTree::~MegaTree() {
	root->deleteNode(root);
}

string MegaTree::nearestNode(double cookie[]) {
	if (root == nullptr) return "tree is null";
	return root->nearestNodeHelper(cookie, 0);
}

MegaTree::MegaTree( int dim, string fname ) : dimension(dim) {
	int n = 0;
	fstream in(fname, fstream::in);
	in >> n;

	s_item* items = new s_item[n]; //all the colors read in

	for (int i=0; i<n; i++) {
		string name;
		in >> name; //color name
		//now get all of the values
		double* points = new double[dimension];
		for (int j=0; j<dimension; j++) {
			in >> points[j];
		}

		items[i] = item(name, dimension);
		items[i].points = points;
	}

	root = root->insertbalanced(root, items, 0, n, dimension);
}

//John McElvenny 
#include <string>
#include <iostream>
#include "MegaTree.h"

using namespace std;

int main() {
	MegaTree* tree = new MegaTree(2);

	cout << "How many sets of points? ";
	int points;
	cin >> points;

	for (int i=0; i<points; i++) {
		double val1=0, val2=0;
		cout << "Enter x and y values: ";
		cin >> val1;
		cin >> val2;
		double* vals;
		vals = new double[2];
		vals[0] = val1;
		vals[1] = val2;
		tree->insert("point", vals);
		cout << endl;
	}

	tree->preorder();


	return 0;
}
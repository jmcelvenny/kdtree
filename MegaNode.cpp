//John McElvenny 
#include "MegaNode.h"
#include <cmath>
#include <algorithm>

MegaNode::MegaNode(int d, string n, double v[]) : dimension(d), name(n), vals(v) {
	left = nullptr;
	right = nullptr;
}

bool itemcompare(item i1, item i2) {
	return (i1.points[i1.k] < i2.points[i2.k]);
}

void MegaNode::setLeft( MegaNode* t) {
	left = t;
}


void MegaNode::setRight( MegaNode* t) {
	right = t;
}

void MegaNode::preorder(MegaNode* n, int depth, int dir) {
	if (depth > 3) return;
	if (n == nullptr) return; //check
	for (int i=0; i<depth; i++) cout << "..."; //print dots
	if (dir == -1) {
		//do nothing, it's root
		cout << n << endl;
	} else if (dir==0) {
		//left
		cout << "L: " << n << endl;
	} else {
		//right
		cout << "R: " << n << endl;;
	}

	if (n->left != nullptr) preorder(n->left, depth+1, 0);
	if (n->right != nullptr) preorder(n->right, depth+1, 1);
}


MegaNode* MegaNode::insert(int dim, string name, MegaNode* root, double vals[], int depth) {
	if (root == nullptr) {
		root = new MegaNode(dim, name, vals);
		return root;
	}

	int key = depth % dim; //hardcode dimension for now


	if (root->vals[key] <= vals[key]) {
		root->right = insert(dim, name, root->right, vals, depth + 1);
	} else {
		root->left =  insert(dim, name, root->left, vals, depth + 1);
	}

	return root;

}

void MegaNode::deleteNode(MegaNode *n) {
	if (n == nullptr) return;
	if (n->left != nullptr) deleteNode(n->left);
	if (n->right != nullptr) deleteNode(n->right);
	delete n;
}

MegaNode* MegaNode::insertbalanced(MegaNode* root, item* items, int d, int sz, int dim) {
	//increment k unless d=0, then leave it be	
	if (d != 0) {
		for (int i=0; i<sz; i++) {
			items[i].k++;
		}
	}

	sort(items, items+sz, itemcompare);

	//handle too few nodes
	if (sz == 1) {
		return new MegaNode(dim, items[0].name, items[0].points);
	}
	if (sz == 2) {
		MegaNode* s = new MegaNode(dim, items[1].name, items[1].points);
		s->left = new MegaNode(dim, items[0].name, items[0].points);
		return s;
	}

	//3+ nodes
	int median = floor(sz / 2); //rounded up
	int a = median;
	int b = sz - median - 1;

	s_item* lower = new s_item[a];
	s_item* upper = new s_item[b];

	copy(items, items+a, lower);
	copy(items+a+1, items+sz, upper);

	MegaNode* node = new MegaNode(dim, items[median].name, items[median].points);
	node->left = insertbalanced(node, lower, d+1, a, dim);
	node->right = insertbalanced(node, upper, d+1, b, dim);

	return node;

}

string MegaNode::nearestNodeHelper(double cookie[], int depth) {

	double distance_left=0.0, distance_right = 0.0;
	//distance
	if (left != nullptr && right != nullptr) {
		for (int i=0; i<dimension; i++) {
			distance_left += pow(cookie[depth%dimension] - left->vals[depth%dimension], 2);
			distance_right += pow(cookie[depth%dimension] - right->vals[depth%dimension], 2);
		}
	}

	if (distance_right <= distance_left) {
		if (right != nullptr) {
			return right->nearestNodeHelper(cookie, depth+1);
		} else {
			return name;
		}
	} else {
		if (left != nullptr) {
			return left->nearestNodeHelper(cookie, depth+1);
		} else {
			return name;
		}
	}
}


ostream& operator<< (ostream& out, const MegaNode* t) {
	if (t == nullptr) return out;
	out << t->name << " ";
	out << "(";
	for (int i=0; i<t->dimension; i++) {
		out << t->vals[i];
		if (i != t->dimension-1) out << ", ";
	}
	out << ")";
	return out;
}
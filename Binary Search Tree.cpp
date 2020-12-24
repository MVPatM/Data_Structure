#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* right;
	Node* left;
	Node(int d, Node* r, Node* l):data(d), right(r), left(l) {}
};

class BST {
public:
	Node* root;
	BST() { root = NULL; }
	~BST() { delete root; }
	void insert1(Node* n, int d);
	Node* insertion(Node* n, int d);
	Node* insertion(Node* r, Node* subtree);
	void delete1(Node* n, int d);
	Node* delete2(Node* n, int d);
	Node* delete3(Node* n, int d);
	Node* findMinNodeandDelete(Node* n);
	Node* findMinNode(Node* n);
	Node* findMaxNode(Node* n);
	Node* findParentNode(Node* s, Node* f, int d);
	void print_value(Node* t);//preorder traversal
	void splitTree(int key);
};

void action();

int main(void) {
	action();
	return 0;
}

void BST::insert1(Node* n, int d) {
	if (n == NULL) { // root == null
		root = new Node(d, NULL, NULL);
		return;
	}

	if (d < n->data) {
		if (n->left == NULL) {
			n->left = new Node(d, NULL, NULL);
			return;
		}
		else
			insert1(n->left, d);
	}
	else {
		if (n->right == NULL) {
			n->right = new Node(d, NULL, NULL);
			return;
		}
		else
			insert1(n->right, d);
	}
}

Node* BST::insertion(Node* n, int d) { // use when want to input numeric data to tree
	if (n == NULL)
		return new Node(d, NULL, NULL);
	
	if (d < n->data) 
		n->left = insertion(n->left, d);
	else 
		n->right = insertion(n->right, d);	

	return n;
}

Node* BST::insertion(Node* r, Node* subtree) {
	if (r == NULL)
		return subtree;

	if (subtree->data < r->data) 
		r->left = insertion(r->left, subtree);
	else 
		r->right = insertion(r->right, subtree);
	
	return r;
}

void BST::delete1(Node* n, int d) {
	if (n->data == d) {
		Node* parent = findParentNode(root, n, d);
		
		if (n->left != NULL && n->right != NULL) {



		}
		else {
			if (parent->left == n)
				parent->left = (n->left != NULL) ? n->left : n->right;
			else
				parent->right = (n->right != NULL) ? n->left : n->right;
		}

		return;
	}

	if (d < n->data)
		delete1(n->left, d);
	else
		delete1(n->right, d);
}

Node* BST::delete2(Node* n, int d) {
	if (n->data == d) {
		if (n->left != NULL && n->right != NULL) {
			// find the min node and connect to parent node
			Node* replace = findMinNodeandDelete(n->right);
			replace->left = n->left;
			
			if (n->right != replace)
				replace->right = n->right;

			return replace;
		}
		else
			return (n->left != NULL) ? n->left : n->right;
	}
	else {
		if (d < n->data)
			n->left = delete2(n->left, d);
		else 
			n->right = delete2(n->right, d);
	}

	return n;
}

Node* BST::delete3(Node* n, int d) {
	if (n->data == d) {
		if (n->left != NULL && n->right != NULL) {
			Node* replace = findMinNode(n->right);
			n->data = replace->data;
			n->right = delete3(n->right, replace->data);
		}
		else
			return (n->left != NULL) ? n->left : n->right;
	}
	else if (d < n->data)
		n->left = delete3(n->left, d);
	else
		n->right = delete3(n->right, d);
	
	return n;
}

Node* BST::findMinNodeandDelete(Node* n) {
	if (n->left == NULL)
		return n;

	Node* min = findMinNodeandDelete(n->left);
	
	if (n->left == min)
		n->left = min->right;

	return min;
}

Node* BST::findMinNode(Node* n) {
	Node* min = n;

	while (min->left != NULL)
		min = min->left;
	
	return min;
}

Node* BST::findMaxNode(Node* n) {
	Node* max = n;

	while (max->right != NULL)
		max = max->right;

	return max;
}

void BST::print_value(Node* t) {
	if (t == NULL)
		return;

	print_value(t->left);
	cout << t->data << " ";
	print_value(t->right);
}

Node* BST::findParentNode(Node* s, Node* f, int d) {
	Node* find;

	if (f == root)
		return root;

	if (d < s->data) {
		if (s->left == f)
			return s;
		else 
			find = findParentNode(s->left, f, d);
	}
	else {
		if (s->right == f)
			return s;
		else
			find = findParentNode(s->right, f, d);
	}

	return find;
}

void BST::splitTree(int key) {
	BST LeftTree = BST();
	BST RightTree = BST();
	
	Node* n = root;
	Node* tmp;

	while (n != NULL) {
		if (key < n->data) {
			tmp = n;
			n = n->left;
			tmp->left = NULL;
			RightTree.root = insertion(RightTree.root, tmp);
			
		}
		else if (key > n->data) {
			tmp = n;
			n = n->right;
			tmp->right = NULL;
			LeftTree.root = insertion(LeftTree.root, tmp);
		}
		else { // key == n->data
			LeftTree.root = insertion(LeftTree.root, n->left);
			RightTree.root = insertion(RightTree.root, n->right);
			break;
		}
	}

	cout << "LeftTree\n";
	print_value(LeftTree.root);
	cout << "\n";
	cout << "RightTree\n";
	print_value(RightTree.root);
}

void action() {
	char c;
	int num;
	BST test = BST();

	while (1) {
		cin >> c;
		if (c == 'i') {
			cin >> num;
			test.root = test.insertion(test.root, num);
		}
		else if (c == 'd') {
			cin >> num;
			test.root = test.delete2(test.root, num);
		}
		else if (c == 's') {
			cin >> num;
			test.splitTree(num);
		}
		else
			break;
	}

	test.print_value(test.root);
}
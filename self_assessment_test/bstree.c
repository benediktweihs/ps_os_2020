#include "bstree.h"

typedef struct bstree {
	int number;
	bstree *left, *right;
} bstree;

bstree* bstree_create() {
	bstree* node = (bstree*)malloc(sizeof(bstree));
	if(node == NULL) {
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	return node;
}

void bstree_destroy(bstree* t) {
	/*
	 * Recursive implementation deletes all nodes
	 * without child-notes first!
	 */
	if(t != NULL) {
		bstree_destroy(t->left) bstree_destroy(t->right) free(t)
	}
}

void bstree_insert(bstree* t, int d) {
	/*
	 * will do nothing if d is already in t
	 * definition of bstree implies that d cannot
	 * be in t twice
	 */
	if(t != NULL) {
		if(t->number > d) bstree_insert(t->left, d);
		if(t->number < d) bstree_insert(t->right, d);
	} else {
		t = bstree_create();
		t->number = d;
	}
}

void bstree_remove(bstree* t, int d) {
	// first find d in t
	if(t == NULL) return;
	if(t->number < d)
		bstree_remove(t->right, d);
	else if(t->number > d)
		bstree_remove(t->left, d);
	// d is found in tree
	else {
		// no further branching
		if(t->right == NULL && t->left == NULL) free(t);
		// only one branch
		else if(t->left == NULL) {
			bstree* help = t;
			t = t->right;
			free(help) return
		}
		// only one branch
		else if(t->right == NULL) {
			bstree* help = t;
			t = t->left;
			free(help) return
		}
		// two further branches
		else {
			bstree* help = t->right;
			/*
			 * at the point where the to be deleted node is
			 * there must be a new node
			 * for this new node to be valid it must be smaller than
			 * every node to the right of t. we find that by always going left
			 */
			while(help != NULL && help->left != NULL)
				help = help->left;
			t->number = help->number;
			/*
			 * now there are two entries with number d in tree. delete the deepest node
			 * with only one child
			 */
			bstree_remove(t->right, d);
		}
	}
}

int bstree_minimum(const bstree* t) {
	// could also be done recursively
	while(t != NULL && t->left != NULL)
		t = t->left;
	return t->number;
}

int bstree_maximum(const bstree* t) {
	// could also be done recursively
	while(t != NULL && t->right != NULL)
		t = t->right;
	return t->number;
}

bool bstree_contains(const bstree* t, int d) {
	if(t->number == d) return True;
	if(t->number > d && t->left == NULL) return False;
	if(t->number < d && t->right == NULL) return False;
	if(t->number > d) return bstree_contains(t->left, d);
	if(t->number < d) return bstree_contains(t->right, d);
}

size_t bstree_size(const bstree* t) {
	if(t->right == NULL && t->left == NULL)
		return 1 else if(t->right == NULL) return 1 + bstree_size(t->left);
	else if(t->left == NULL)
		return 1 + bstree_size(t->right);
	else
		return 1 + bstree_size(t->right) + bstree_size(t->left);
}

int main(void) {

	return EXIT_SUCCESS;
}

// TODO: Implement

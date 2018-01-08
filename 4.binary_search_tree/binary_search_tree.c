#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a > b) ? a : b)

typedef struct node *Node;
typedef struct node *Tree;

struct node {
	int value;
	Node parent;
	Node l_child;
	Node r_child;
};

Tree create_tree();
int is_empty(Tree T);
Node search(Tree T, int key);
void insert_node(Tree *T, int key);
void delete_node(Tree *T, int key);
void show_tree(Tree T);
int tree_height(Tree *T);
int get_node_height(Tree T, int key);

int main() {

	Tree mytree = NULL;
	char command;
	int key;

	while (1) {
		scanf(" %c", &command);

		if (command == 'i') {
			scanf(" %d", &key);
			insert_node(&mytree, key);
		}
		else if (command == 'd') {
			scanf(" %d", &key);
			delete_node(&mytree, key);
		}
		else if (command == 's') {
			if (is_empty(mytree)) {
				printf("tree is empty \n");
			}
			else {
				show_tree(mytree);
				printf("\n");
			}
		}
		else if (command == 'h') {
			scanf(" %d", &key);
			if (get_node_height(mytree, key) == -1)
				printf("%d is not in tree \n", key);
			else
				printf("The height of the node (%d) is %d \n", key, get_node_height(mytree, key));
		}
		else if (command == 'e')
			return 0;
		else
			printf("Try again. \n");
	}
	return 0;
}

// Create a tree - allocate memory for tree
Tree create_tree() {

	Tree temp = (Tree)malloc(sizeof(struct node));
	return temp;
}

int is_empty(Tree T) {

	if (T)
		return 0;
	else
		return 1;
}

// Search the key in the tree
// 1. key exists -> return NULL
// 2. key doesn't exist -> return the parent node which will have the key as child
Node search(Tree T, int key) {

	Node temp = NULL;
	while (T) {
		temp = T;
		if (T->value == key)
			return NULL;
		else if (T->value > key)
			T = T->l_child;
		else
			T = T->r_child;
	}
	return temp;
}

void insert_node(Tree *T, int key) {

    // Case1. Tree is empty
	if (is_empty(*T)) {
		*T = create_tree();
		(*T)->value = key;
		(*T)->parent = (*T)->l_child = (*T)->r_child = NULL;
	}
    // Case2. Tree is not empty
	else {
        // Search the node which has the key
		Node temp = search(*T, key);
        // 1. key already exists
		if (!temp) {
			printf("%d is already exist. \n", key);
			return;
		}
        // 2. key doesn't exist
		else {
			Node new_node = (Node)malloc(sizeof(struct node));
			new_node->value = key;
			if (temp->value > key) {
				temp->l_child = new_node;
				new_node->parent = temp;
				new_node->l_child = new_node->r_child = NULL;
			}
			else {
				temp->r_child = new_node;
				new_node->parent = temp;
				new_node->l_child = new_node->r_child = NULL;
			}
		}
	}
	return;
}

void delete_node(Tree * T, int key) {

	Node temp = search(*T, key);
    // Tree is empty or node which has the key doesn't exist
	if (is_empty(*T) || temp) {
		printf("%d is not in tree. \n", key);
		return;
	}
    // Tree is not empty and node which has the key exists
	else {
		Node ptr = (*T);
		while (ptr->value != key) {
			if (ptr->value > key)
				ptr = ptr->l_child;
			else
				ptr = ptr->r_child;

		}
        // Case1. The node has 0 child
		if (ptr->l_child == NULL && ptr->r_child == NULL) {
            // When the node is the only root
            if (ptr->parent == NULL) {
				(*T) = NULL;
			}
			else {
				if (ptr->parent->value > key) {
					ptr->parent->l_child = NULL;
					free(ptr);
				}
				else {
					ptr->parent->r_child = NULL;
					free(ptr);
				}
			}
		}
        // Case2. The node has 2 childs
        // -> Replace this node by left decestor node which has the biggest value
		else if (ptr->l_child != NULL && ptr->r_child != NULL) {
			Node ptr_2 = ptr->l_child;
			if (ptr_2->r_child == NULL) {
				ptr->value = ptr_2->value;
				ptr->l_child = NULL;
				free(ptr_2);
			}
			else {
				while (ptr_2->r_child != NULL) {
					ptr_2 = ptr_2->r_child;
				}
				ptr->value = ptr_2->value;
				ptr_2->parent->r_child = ptr_2->l_child;
				free(ptr_2);
			}
		}
        // Case3. The node has 1 child
		else {
            // When the node is the only root
			if (ptr->parent == NULL) {
				if (ptr->l_child)
					(*T) = ptr->l_child;
				else
					(*T) = ptr->r_child;
			}
			else {
                // ptr is left child and ptr has left child
				if (ptr->parent->value > key && ptr->l_child) {
					ptr->parent->l_child = ptr->l_child;
					ptr->l_child->parent = ptr->parent;
				}
                // ptr is left child and ptr has right child
				else if (ptr->parent->value > key && ptr->r_child) {
					ptr->parent->l_child = ptr->r_child;
					ptr->r_child->parent = ptr->parent;

				}
                // ptr is right child and ptr has left child
				else if (ptr->parent->value < key && ptr->l_child) {
					ptr->parent->r_child = ptr->l_child;
					ptr->l_child->parent = ptr->parent;
				}
                // ptr is right child and ptr has right child
				else {
					ptr->parent->r_child = ptr->r_child;
					ptr->r_child->parent = ptr->parent;
				}
			}
			free(ptr);
		}
	}
	return;
}

void show_tree(Tree T) {

	if (T) {
		show_tree(T->l_child);
		printf("%d ", T->value);
		show_tree(T->r_child);
	}
	return;
}

int tree_height(Tree *T) {

	int height = 0;
	if (*T) {
		height = 1 + max(tree_height(&((*T)->l_child)), tree_height(&((*T)->r_child)));
	}
	return height;
}

int get_node_height(Tree T, int key) {

	if (is_empty(T))
		return -1;
    // Tree is not empty but the node which has the key doesn't exist
	else if (search(T, key))
		return -1;
    // Tree is not empty and the node which has the key exists
	else {
		Node temp = T;
		int height = 0;
		while (temp->value != key) {
			if (temp->value > key)
				temp = temp->l_child;
			else
				temp = temp->r_child;
		}
		height = tree_height(&temp);
		return height - 1;
	}
}

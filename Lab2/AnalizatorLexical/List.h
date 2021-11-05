#pragma once
#include <iostream>
#include <string>
#include "Codare.h"

using namespace std;


struct Node {
    Codare inform;
    struct Node* next;
    Node(Codare x)
    {
        inform = x;
        next = NULL;
    }
};

class List {

public:
    Node* head;
    Node* sorted;

    int start = 1;

    List() {
        head = NULL;
    }

    int insert(string dataCod) {
		Codare codare = Codare();
		codare.cod = start;
		codare.dataCod = dataCod;
		this->add(codare);
		start++;
		return codare.cod;
	}

    void add(Codare codare)
    {
        Node* newnode = new Node(codare);
        newnode->next = head;
        head = newnode;
        insertionSort(head);
    }

    
    void insertionSort(Node* headref)
    {
        // Initialize sorted linked list
        sorted = NULL;
        Node* current = headref;
        // Traverse the given linked list and insert every
        // node to sorted
        while (current != NULL) {
            // Store next for next iteration
            Node* next = current->next;
            // insert current in sorted linked list
            sortedInsert(current);
            // Update current
            current = next;
        }
        // Update head_ref to point to sorted linked list
        head = sorted;
    }

    /*
     * function to insert a new_node in a list. Note that
     * this function expects a pointer to head_ref as this
     * can modify the head of the input linked list
     * (similar to push())
     */
    void sortedInsert(Node* newnode)
    {
        /* Special case for the head end */
        if (sorted == NULL || sorted->inform > newnode->inform || sorted->inform == newnode->inform) {
            newnode->next = sorted;
            sorted = newnode;
        }
        else {
            Node* current = sorted;
            /* Locate the node before the point of insertion
             */
            while (current->next != NULL
                && current->next->inform < newnode->inform) {
                current = current->next;
            }
            newnode->next = current->next;
            current->next = newnode;
        }
    }
    /* Function to print linked list in a file */
    void display(ostream& out)
    {
        Node* p = head;
        while (p != NULL) {
            out << p->inform;
            p = p->next;
        }
    }

    int find(string x) {
        Node* p = head;
        while (p != NULL) {
            if (p->inform.dataCod == x)
                return p->inform.cod;
            p = p->next;
        }
        return NULL;
	}
};

//class List {
//	struct node {
//		Codare inform = Codare();
//		node* left;
//		node* right;
//	};
//
//	node* root;
//
//	int start = 1;
//
//	node* makeEmpty(node* t) {
//		if (t == NULL)
//			return NULL;
//		{
//			makeEmpty(t->left);
//			makeEmpty(t->right);
//			delete t;
//		}
//		return NULL;
//	}
//
//	node* insert(Codare x, node* t)
//	{
//		if (t == NULL)
//		{
//			t = new node;
//			t->inform = x;
//			t->left = t->right = NULL;
//		}
//		else if (x < t->inform)
//			t->left = insert(x, t->left);
//		else if (x > t->inform)
//			t->right = insert(x, t->right);
//		return t;
//	}
//
//	node* findMin(node* t)
//	{
//		if (t == NULL)
//			return NULL;
//		else if (t->left == NULL)
//			return t;
//		else
//			return findMin(t->left);
//	}
//
//	node* findMax(node* t) {
//		if (t == NULL)
//			return NULL;
//		else if (t->right == NULL)
//			return t;
//		else
//			return findMax(t->right);
//	}
//
//	node* remove(Codare cod, node* t) {
//		node* temp;
//		if (t == NULL)
//			return NULL;
//		else if (cod < t->inform)
//			t->left = remove(cod, t->left);
//		else if (cod > t->inform)
//			t->right = remove(cod, t->right);
//		else if (t->left && t->right)
//		{
//			temp = findMin(t->right);
//			t->inform = temp->inform;
//			t->right = remove(t->inform, t->right);
//		}
//		else
//		{
//			temp = t;
//			if (t->left == NULL)
//				t = t->right;
//			else if (t->right == NULL)
//				t = t->left;
//			delete temp;
//		}
//
//		return t;
//	}
//
//	void inorder(ostream& out, node* t) {
//		if (t == NULL)
//			return;
//		inorder(out, t->left);
//		out << t->inform;
//		inorder(out, t->right);
//	}
//
//	node* find(node* t, string x) {
//		if (t == NULL)
//			return NULL;
//		else if (x < t->inform.dataCod)
//			return find(t->left, x);
//		else if (x > t->inform.dataCod)
//			return find(t->right, x);
//		else
//			return t;
//	}
//
//public:
//	List() {
//		root = NULL;
//	}
//
//	~List() {
//		root = makeEmpty(root);
//	}
//
//	int insert(string dataCod) {
//		Codare codare = Codare();
//		codare.cod = start;
//		codare.dataCod = dataCod;
//		root = insert(codare, root);
//		start++;
//		return codare.cod;
//	}
//
//	void insert(Codare codare) {
//		root = insert(codare, root);
//	}
//
//	void remove(Codare x) {
//		root = remove(x, root);
//	}
//
//	void display(ostream& out) {
//		inorder(out, root);
//
//	}
//
//	int find(string x) {
//		node* rez = find(root, x);
//		return rez == NULL ? 0 : rez->inform.cod;
//	}
//};

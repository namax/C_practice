/* 
 * File:   main.c
 * Author: namax
 *
 * Created on February 9, 2012, 7:50 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* Function prototypes */
struct Node *createNode(long value);

struct Node *addNode(long value, struct Node *pNode);

void listNodes(struct Node *pNode);

void freeNodes(struct Node *pNode);

struct Node {
    long item;
    int count;
    struct Node *pLeft;
    struct Node *pRight;
};

/*
 * 
 */
int main(int argc, char **argv) {

    long newvalue = 0;
    struct Node *pRoot = NULL;
    char answer = 'n';
    do {
        printf("Enter the node value: ");
        scanf(" %ld", &newvalue);
        if (pRoot == NULL) {
            pRoot = createNode(newvalue);
        } else {
            addNode(newvalue, pRoot);
        }
        printf("\nDo you want to enter another (y or n)? ");
        scanf(" %c", &answer);
    } while (tolower(answer) == 'y');
    printf("The values in ascending sequence are: ");
    listNodes(pRoot);
    freeNodes(pRoot);
    return (EXIT_SUCCESS);
}


/**
 *
 * @param value
 * @return
 */
struct Node *createNode(long value) {
    /* Allocate memory for a new node */
    struct Node *pNode = (struct Node *) malloc(sizeof(struct Node));
    pNode->item = value;
    pNode->count = 1;
    pNode->pLeft = pNode->pRight = NULL;
    return pNode;
}

/* Add a new node to the tree */
struct Node *addNode(long value, struct Node *pNode) {
    if (pNode == NULL) {
        return createNode(value);
    }
    if (value == pNode->item) {
        ++pNode->count;
        return pNode;
    }
    if (value < pNode->item) {
        if (pNode->pLeft == NULL) {
            pNode->pLeft = createNode(value);
            return pNode->pLeft;
        } else {
            return addNode(value, pNode->pLeft);
        }
    } else {
        if (pNode->pRight == NULL) {
            pNode->pRight = createNode(value);
            return pNode->pRight;
        } else {
            return addNode(value, pNode->pRight);
        }
    }
}

/**
 * List the node values in ascending sequence
 * @param pNode
 */
void listNodes(struct Node *pNode) {
    if (pNode->pLeft != NULL)
        listNodes(pNode->pLeft);
    /* List nodes in the left subtree */
    for (int i = 0; i < pNode->count; i++) {
        printf("\n%10ld", pNode->item);
    }
    if (pNode->pRight != NULL) {
        listNodes(pNode->pRight);
    }
}


/**
 * Release memory allocated to nodes
 * @param pNode
 */
void freeNodes(struct Node *pNode) {
    if (pNode == NULL) {
        return;
    }

    // If there's a left sub-tree  free memory for those nodes
    if (pNode->pLeft != NULL) {
        freeNodes(pNode->pLeft);

    }
    // If there's a right sub-tree free memory for those nodes
    if (pNode->pRight != NULL) {
        freeNodes(pNode->pRight);
    }

    free(pNode);
}

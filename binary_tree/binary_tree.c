#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

struct strNode
{
    Type data;
    struct strNode * left;
    struct strNode * right;
};

typedef struct strNode * Node;

struct strTree
{
    Node root;
    unsigned int size;
    int (*comparator)(Type, Type);
    void (*destructor)(Type);
};

Tree binary_tree_init(void(* destructor)(Type), int(* comparator)(Type, Type))
{
    Tree newTree = (Tree)malloc(sizeof(struct strTree));

    if(newTree == NULL)
        return NULL;

    newTree->root = NULL;
    newTree->size = 0;
    newTree->destructor = destructor;
    newTree->comparator = comparator;

    return newTree;
}

void binary_tree_insert(Tree tree, Type data)
{
    if(tree == NULL)
        return;

    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    if(tree->root == NULL)
        tree->root = node;
    else
    {
        Node curr = tree->root;
        Node prev = NULL;

        while(curr != NULL)
        {
            prev = curr;
            int cmp = tree->comparator(curr->data, data);
            if(cmp < 0)
                curr = curr->right;
            else if(cmp > 0)
                curr = curr->left;
            else
            {
                if(tree->destructor != NULL)
                    tree->destructor(node->data);
                free(node);
                return;
            }
        }

        if(tree->comparator(prev->data, data) < 0)
            prev->right = node;
        else
            prev->left = node;
    }

    tree->size++;
}

void binary_tree_delete(Tree tree, Type data)
{
    if(tree == NULL || tree->root == NULL)
        return;

    Node curr = tree->root;
    Node prev = NULL;

    while(curr != NULL)
    {
        int cmp = tree->comparator(curr->data, data);

        if(cmp == 0)
            break;

        prev = curr;

        if(cmp < 0)
            curr = curr->right;
        else
            curr = curr->left;
    }

    if(curr == NULL)
        return;

    if(curr->left == NULL && curr->right == NULL)
    {
        if(prev == NULL)
            tree->root = NULL;
        else if(prev->left == curr)
            prev->left = NULL;
        else
            prev->right = NULL;

        if(tree->destructor != NULL)
            tree->destructor(curr->data);

        free(curr);
    }

    else if(curr->left == NULL)
    {
        if(prev == NULL)
            tree->root = curr->right;
        else if(prev->left == curr)
            prev->left = curr->right;
        else
            prev->right = curr->right;

        if(tree->destructor != NULL)
            tree->destructor(curr->data);

        free(curr);
    }

    else if(curr->right == NULL)
    {
        if(prev == NULL)
            tree->root = curr->left;
        else if(prev->left == curr)
            prev->left = curr->left;
        else
            prev->right = curr->left;

        if(tree->destructor != NULL)
            tree->destructor(curr->data);

        free(curr);
    }

    else
    {
        Node leastVal = curr->right;
        Node leastPrev = curr;

        while(leastVal->left != NULL)
        {
            leastPrev = leastVal;
            leastVal = leastVal->left;
        }

        curr->data = leastVal->data;

        if(leastPrev->left == leastVal)
            leastPrev->left = leastVal->right;
        else
            leastPrev->right = leastVal->right;

        free(leastVal);
    }

    tree->size--;
}

Type binary_tree_search(Tree tree, Type data)
{
    if(tree == NULL || tree->root == NULL)
        return NULL;
    
    Node curr = tree->root;
    
    while(curr != NULL)
    {
        int cmp = tree->comparator(curr->data, data);

        if(cmp == 0)
            return curr->data;
        else if(cmp < 0)
            curr = curr->right;
        else
            curr = curr->left;
    }

    return NULL;
}

static void destroy(Node node, void (*destructor)(Type))
{
    if(node == NULL)
        return;

    destroy(node->left, destructor);
    destroy(node->right, destructor);

    if(destructor != NULL)
        destructor(node->data);

    free(node);
}

void binary_tree_destroy(Tree tree)
{
    if(tree == NULL)
        return;

    destroy(tree->root, tree->destructor);
    free(tree);
}

unsigned int binary_tree_size(Tree tree)
{
    if(tree == NULL)
        return 0;
    return tree->size;
}

bool binary_tree_is_empty(Tree tree)
{
    if(tree == NULL)
        return true;
    return tree->size == 0;
}
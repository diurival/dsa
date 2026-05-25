#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "avl_tree.h"

struct strNode
{
    Type data;
    struct strNode *left;
    struct strNode *right;
    int height;
};

typedef struct strNode *Node;

struct strTree
{
    Node root;
    unsigned int size;
    void (*destructor)(Type);
    int (*comparator)(Type, Type);
};

static Node avl_insert(Node node, Type data, int (*comparator)(Type, Type), bool *isInserted);
static Node avl_delete(Node node, Type data, int (*comparator)(Type, Type), void (*destructor)(Type), bool *isDeleted);
static Type avl_search(Node node, Type data, int (*comparator)(Type, Type));
static void avl_update_height(Node node);
static int height(Node node);
static int avl_balance(Node node);
static Node rotate_right(Node node);
static Node rotate_left(Node node);
static Node rotate_left_right(Node node);
static Node rotate_right_left(Node node);
static void postorder(Node node, void(*destructor)(Type));

Tree avl_tree_init(void (*destructor)(Type), int (*comparator)(Type, Type))
{
    Tree newTree = (Tree)malloc(sizeof(struct strTree));
    if (newTree == NULL)
        return NULL;

    newTree->root = NULL;
    newTree->size = 0;
    newTree->comparator = comparator;
    newTree->destructor = destructor;

    return newTree;
}

void avl_tree_insert(Tree tree, Type data)
{
    if (tree == NULL)
        return;

    bool flag = false;

    tree->root = avl_insert(tree->root, data, tree->comparator, &flag);
    if (flag)
        tree->size++;
}

void avl_tree_delete(Tree tree, Type data)
{
    if (tree == NULL)
        return;

    bool flag = false;

    tree->root = avl_delete(tree->root, data, tree->comparator, tree->destructor, &flag);
    if (flag)
        tree->size--;
}

Type avl_tree_search(Tree tree, Type data)
{
    if (tree == NULL)
        return NULL;

    return avl_search(tree->root, data, tree->comparator);
}

void avl_tree_destroy(Tree tree)
{
    if (tree == NULL)
        return;

    postorder(tree->root, tree->destructor);
    free(tree);
}

unsigned int avl_tree_size(Tree tree)
{
    return tree == NULL ? 0 : tree->size;
}

bool avl_tree_is_empty(Tree tree)
{
    if (tree == NULL)
        return true;
    return tree->size > 0 ? false : true;
}

static Node avl_delete(Node node, Type data, int (*comparator)(Type, Type), void (*destructor)(Type), bool *isDeleted)
{
    if (node == NULL)
        return NULL;

    if (comparator(node->data, data) == 0)
    {
        if (node->left == NULL && node->right == NULL)
        {
            Node temp = node;
            if (destructor != NULL)
                destructor(temp->data);
            free(temp);

            return NULL;
        }
        else if (node->left != NULL && node->right != NULL)
        {
            Node curr = node->right;
            while (curr->left != NULL)
                curr = curr->left;

            node->data = curr->data;

            node->right = avl_delete(node->right, curr->data, comparator, NULL, isDeleted);
        }
        else
        {
            Node curr = NULL;
            if (node->right != NULL)
                curr = node->right;
            else
                curr = node->left;

            if (destructor != NULL)
                destructor(node->data);
            free(node);
            return curr;
        }
        *isDeleted = true;
    }
    else
    {
        int cmp = comparator(node->data, data);
        if(cmp > 0)
            node->left = avl_delete(node->left, data, comparator, destructor, isDeleted);
        else if(cmp < 0)
            node->right = avl_delete(node->right, data, comparator, destructor, isDeleted);
    }

    avl_update_height(node);

    int balance = avl_balance(node);
    if (balance > 1)
    {
        if (avl_balance(node->left) >= 0)
            return rotate_right(node);
        else
            return rotate_left_right(node);
    }
    else if (balance < -1)
    {
        if (avl_balance(node->right) <= 0)
            return rotate_left(node);
        else
            return rotate_right_left(node);
    }
    else
        return node;
}

static Node avl_insert(Node node, Type data, int (*comparator)(Type, Type), bool *isInserted)
{
    if (node == NULL)
    {
        Node newNode = (Node)malloc(sizeof(struct strNode));
        if (newNode == NULL)
            return NULL;

        newNode->data = data;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        *isInserted = true;

        return newNode;
    }

    int cmp = comparator(node->data, data);
    if (cmp > 0)
        node->left = avl_insert(node->left, data, comparator, isInserted);
    else if (cmp < 0)
        node->right = avl_insert(node->right, data, comparator, isInserted);
    else
        return node;
    avl_update_height(node);

    int balance = avl_balance(node);
    if (balance > 1)
    {
        if (avl_balance(node->left) >= 0)
            return rotate_right(node);
        else
            return rotate_left_right(node);
    }
    else if (balance < -1)
    {
        if (avl_balance(node->right) <= 0)
            return rotate_left(node);
        else
            return rotate_right_left(node);
    }
    else
        return node;
}

static Type avl_search(Node node, Type data, int (*comparator)(Type, Type))
{
    if (node == NULL)
        return NULL;

    int cmp = comparator(data, node->data);
    if (cmp == 0)
        return data;
    else if (cmp > 0)
        return avl_search(node->right, data, comparator);
    else
        return avl_search(node->left, data, comparator);
}

static Node rotate_right(Node node)
{
    Node pivot = node->left;
    node->left = pivot->right;

    pivot->right = node;
    avl_update_height(node);
    avl_update_height(pivot);

    return pivot;
}

static Node rotate_left(Node node)
{
    Node pivot = node->right;
    node->right = pivot->left;

    pivot->left = node;
    avl_update_height(node);
    avl_update_height(pivot);

    return pivot;
}

static Node rotate_left_right(Node node)
{
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

static Node rotate_right_left(Node node)
{
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

static void avl_update_height(Node node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}

static int height(Node node)
{
    return node == NULL ? 0 : node->height;
}

static int avl_balance(Node node)
{
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

static void postorder(Node node, void (*destructor)(Type))
{
    if (node == NULL)
        return;

    postorder(node->left, destructor);
    postorder(node->right, destructor);
    if (destructor != NULL)
        destructor(node->data);
    free(node);
}
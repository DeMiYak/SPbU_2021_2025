#include <stdlib.h>
#include "bst.h"
/*
bst *tree = NULL;
// ...

bst *n = bst_insert(tree, k);
if (!n) {//...

}
else
    tree = n;
*/

bst * bst_insert (bst *root, key_t k)       // Вставка элемента
{
    if (root == NULL)
    {
        bst *node = malloc(sizeof(bst));
        if (!node) return NULL;

        node->left = node->right = NULL;
        node->key = k;

        return node;
    }

    if (root->key <= k)
    {
        bst *node = bst_insert(root->right, k);
        if (!node) return NULL;
        if (root->right == NULL) root->right = node;
    }
    else
    {
        bst *node = bst_insert(root->left, k);
        if (!node) return NULL;
        if (root->left == NULL) root->left = node;

    }

    return root;
}

bst * bst_insert_iter (bst *root, key_t k)         // Итеративная вставка
{
    bst *cur = root, *par;

    bst *node = malloc(sizeof(bst));
    if (!node) return NULL;

    node->left = node->right = NULL;
    node->key = k;

    if (root == NULL) return node;

    do
    {
        par = cur;
        cur = k >= cur->key ? cur->right : cur->left;

    } while (cur);

    if (k >= par->key)
        par->right = node;
    else
        par->left = node;

    return root;
}

bst * bst_search (bst *root, key_t k)           // Поиск элемента
{
    bst *cur = root;

    while (cur)
    {
        if      (k < cur->key) cur = cur->left;
        else if (k > cur->key) cur = cur->right;
        else return cur;
    }

    return NULL;
}

bst * bst_max (bst *root)                   // Максимальный элемент
{
    bst *cur = root;
    if (!root) return NULL;

    while (cur->right) cur = cur->right;

    return cur;
}

bst * bst_min (bst *root)                   // Минимальный элемент
{
    bst *cur = root;
    if (!root) return NULL;

    while (cur->left) cur = cur->left;

    return cur;
}

bst * bst_successor (bst *root, bst *e)     //
{
    bst *succ = NULL;

    if (e->right) return bst_min(e->right);

    while (root)
    {
        if (e->key < root->key)
        {
            succ = root;
            root = root->left;
        }
        else if (e == root)
            return succ;
        else
            root = root->right;
    }

    return succ;
}

/// int bst_remove (bst **root, key_t k)
// if (bst_remove(&root, k)) {// ошибка }

int bst_remove (bst **root, key_t k)            // Удаление элемента
{
    if (!*root) return 1;

    if      (k < (*root)->key) return bst_remove(&(*root)->left,  k);
    else if (k > (*root)->key) return bst_remove(&(*root)->right, k);
    else if ((*root)->left && (*root)->right)
    {
        (*root)->key = bst_min((*root)->right)->key;
        return bst_remove(&(*root)->right, (*root)->key);
    }
    else
    {
        bst *t = *root;
        *root = (*root)->left ? (*root)->left : (*root)->right;
        free(t);
        return 0;
    }
}

void bst_free (bst *root)           // Освобождение памяти для бинарного дерева поиска
{
    if (root)
    {
        bst_free(root->left);
        bst_free(root->right);
        free(root);
    }
}

void bst_print_req (const bst *root)    // Вывод элементов БДП
{
    if (!root) return;
    bst_print_req(root->left);
    if (root->left) print (", ");
    printf ("%i", root->key);
    if (root->right) print (", ");
    bst_print_req(root->right);
}

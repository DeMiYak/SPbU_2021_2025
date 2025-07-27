#ifndef RBT_H_INCLUDED
#define RBT_H_INCLUDED

/* Цвет узлов */
typedef enum {RED,BLACK} rb_color;

/* Узел дерева */
typedef struct rb_node
{
    int      key;
    void    *data;
    size_t   s;
    rb_color color;
    struct rb_node *left, *right, *parent;
} rb_node;

/* Дерево */
typedef struct rb_tree
{
    rb_node *root;
} rb_tree;

rb_tree *rb_alloc();// Создание дерева

void rb_node_clear (rb_node *n);// Рекурсивная очистка поддеревьев узла и самого узла

void rb_free(rb_tree **t);// Удаление дерева из памяти

rb_node * rb_search (rb_tree *t, int key);// Поиск в дереве по ключу

rb_node * rb_min (rb_tree *t);// Поиск узла с минимальным ключом

rb_node * rb_max (rb_tree *t);// Поиск узла с максимальным ключом

void rb_rotate_left (rb_tree *t, rb_node *x, int check);// Левое вращение дерева t вокруг узла x

void rb_rotate_right (rb_tree *t, rb_node *x, int check);// Правое вращение дерева t вокруг узла x

rb_node *rb_bst_insert (rb_tree *t, int key, const void *data, size_t s);
/* Вставка элемента с ключом key и данными data размера s
 *         в дерево t как в простое дерево поиска
 * Возвращает указатель на вставленный элемент или NULL в случае неудачи
 */

int rb_insert (rb_tree *t, int key, const void *data, size_t s);
/* Вставка элемента с ключом key и данными data размера s в дерево t
 * Возвращает 0 в случае успеха, ненулевое значение в случае провала
 */

int rb_delete (rb_tree *t, int key);
/* Удаление элемента с ключом key из дерева t
 * Возвращает 0, если элемент удален, ненулевое значение, если элемента нет
 */

#endif // RBT_H_INCLUDED

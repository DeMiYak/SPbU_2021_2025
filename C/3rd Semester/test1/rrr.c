#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rrr.h"
#include "graph.h"

/* Красно-черное дерево */

/* Создание дерева */
rb_tree *rb_alloc()
{
    rb_tree *r = malloc (sizeof(rb_tree));
    if (!r) return NULL;

    r->root = NULL;
    return r;
}

/* Рекурсивная очистка поддеревьев узла и самого узла */
void rb_node_clear (rb_node *n)
{
    if (!n) return;
    rb_node_clear (n->left);
    rb_node_clear (n->right);
    free(n->data);
    free(n);
}

/* Удаление дерева из памяти */
void rb_free(rb_tree **t)
{
    rb_node_clear ((*t)->root);
    free(*t);
    *t = NULL;
}

// Поиск в дереве по ключу
rb_node * rb_search (rb_tree *t, int key)
{
    rb_node *x = t->root;

    while (x)
    {
        if      (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return x;
    }

    return NULL;
}

// Поиск узла с минимальным ключом
rb_node * rb_min (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->left) x = x->left;
    return x;
}

// Поиск узла с максимальным ключом
rb_node * rb_max (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->right) x = x->right;
    return x;
}


/* Левое вращение дерева t вокруг узла x */
void rb_rotate_left (rb_tree *t, rb_node *x, int at)
{
    rb_node *y = x->right;         /* находим новый корень поддерева                         */
    if(!y)return;       /* проверка возможности вращения                          */

    if(at) rb_tree_graph(t, 8, x);

    x->right = y->left;            /* левый потомок y становится правым потомком x           */
    if (y->left)
        y->left->parent = x;       /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->left = x;                   /* x становится левым потомком y,                         */
    x->parent = y;                 /* а y - родителем x                                      */

    if(at) rb_tree_graph(t, 9, x);
}

/* Правое вращение дерева t вокруг узла x */
void rb_rotate_right (rb_tree *t, rb_node *x, int at)
{
    rb_node *y = x->left;          /* находим новый корень поддерева                         */
    if(!y)return;            /* проверка возможности вращения                          */

    if(at) rb_tree_graph(t, 6, x);

    x->left = y->right;            /* правый потомок y становится левым потомком x           */
    if (y->right)
        y->right->parent = x;      /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->right = x;                  /* x становится правым потомком y,                        */
    x->parent = y;                 /* а y - родителем x                                      */

    if(at) rb_tree_graph(t, 7, x);
}

/* Вставка элемента с ключом key и данными data размера s
 *         в дерево t как в простое дерево поиска
 * Возвращает указатель на вставленный элемент или NULL в случае неудачи
 */
rb_node *rb_bst_insert (rb_tree *t, int key, const void *data, size_t s)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* вставляемый узел            */
    if (!z) return NULL;

    z->key   = key;
    z->color = RED;               /* вставляемый узел - красный  */
    z->left  = z->right   = NULL;
    z->s     = s;
    z->data  = malloc(s);         /* выделение памяти под данные */

    if (!z->data)
    {
        free(z);
        return NULL;
    }
    memcpy (z->data, data, s);    /* копирование данных          */

    while (x)
    {
        y = x;
        x = z->key < x->key ? x->left      /* Спускаемся до листа влево или вправо  */
                            : x->right;    /* в зависимости от ключа item           */
    }

    z->parent = y;
    if (!y)            /* Если вставляли в корень */
        t->root = z;
    else
    {
        if (z->key < y->key)  /* Левым или правым ребенком будет z? */
            y->left = z;
        else
            y->right = z;
    }

    return z;
}

/* Вставка элемента с ключом key и данными data размера s в дерево t
 * Возвращает 0 в случае успеха, ненулевое значение в случае провала
 */
int rb_insert (rb_tree *t, int key, const void *data, size_t s)
{
    rb_node *x = rb_bst_insert(t, key, data, s);

    size_t at;
    printf("You want to visualize it? YES(1), NO(0): ");
    scanf("%Iu", &at);

    if(at) rb_tree_graph(t, 2, t->root);

    if (!x) return -1;

    /* Проблема если у x красный родитель:
     * указатель x перемещается вверх до корня или узла с черным родителем
     */
    while (x != t->root && x->parent->color == RED)
    {
        /* находим дядю в зависимости от того, является ли родитель x
         * правый или левым ребенком своего родителя
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == RED)              /* случай "красный дядя"            */
        {
            x->parent->color         = BLACK;  /* перекраска */
            y->color                 = BLACK;
            x->parent->parent->color = RED;
            x = x->parent->parent;             /* перемещение x вверх              */
                                               /* ( дедушка есть, так как родитель x - красный, */
                                               /*   а значит имеет родителя )                    */
        }
        else                                   /* случай "черный дядя"             */
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
                rb_rotate_left(t, x, at); /* случай x - правый ребенок, а его родитель - левый        */
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
                rb_rotate_right(t, x, at); /* случай x - левый ребенок, а его родитель - правый        */

            /* случай, когда путь от дедушки x к x в одном направлении  */
            x->parent->color         = BLACK; /* перекраска */
            x->parent->parent->color = RED;
            /* вращение вокруг дедушки в зависимости от того,
             * в каком направлении путь от дедушки к x
             */
            x == x->parent->left ? rb_rotate_right(t, x->parent->parent, at)
                                 : rb_rotate_left (t, x->parent->parent, at);
        }
    }

    t->root->color = BLACK;   /* поддержка условия черноты корня */

    if(at) rb_tree_graph(t, 3, t->root);

    return 0;
}

/* Удаление элемента с ключом key из дерева t
 * Возвращает 0, если элемент удален, ненулевое значение, если элемента нет
 */
int rb_delete (rb_tree *t, int key)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* Шаг 1 - удаление элемента из дерева поиска */

    while (z && z->key != key)
        z = key < z->key ? z->left      /* Спускаемся до листа влево или вправо  */
                         : z->right;    /* в зависимости от ключа                */

    if (!z) return -1;                  /* элемент не найден                     */

    /* находим узел y, который будет фактически удален из дерева */
    if (!z->left || !z->right)
    {
         y = z;
         free (y->data);
    }
    else
    {
        rb_tree r;
        r.root = z->right;
        y = rb_min (&r);

        free (z->data);
        z->key  = y->key;                /* копируем ключ                     */
        z->data = y->data;               /* и дополнительные данные           */
        z->s    = y->s;                  /* фактически удаляемого узла y в z  */
    }

    size_t at;
    printf("You want to visualize it? YES(1), NO(0): ");
    scanf("%Iu", &at);

    if(at) rb_tree_graph(t, 4, t->root);
    /* находим единственного потомка фактически удаляемого узла */

    x = y->left ? y->left : y->right;

    if (!x) /* если x - NIL-узел, актуализируем его */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = BLACK;
        x         = n;
    }

    x->parent = y->parent; /* x будет новым ребенком родителя y */

    if (!y->parent)               /* если удаляется корень */
        t->root = x;              /* устанавливаем корень */
    else                          /* иначе удаляется новый ребенок родителя удаленного узла */
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == BLACK)  /* Если удален черный элемент, надо восстановить RB-свойства */
    {
        /* x объявляется "дважды черной вершиной" ( без отражения в памяти )
         * x всегда будет указывать на дважды черную вершину, поднимаясь вверх до корня
         *   или пока не окажется красной вершиной
         */
        while (x != t->root && x->color == BLACK)
        {
            rb_node *w = x == x->parent->left ? x->parent->right
                                              : x->parent->left; /* находим брата вершины x */

            if (w->color == RED)           /* случай "брат - красный" */
            {
                w->color         = BLACK;  /* перекраска              */
                x->parent->color = RED;

                if (x == x->parent->left)          /* нужный поворот и новый w  */
                {                                  /* в зависимости от того,    */
                    rb_rotate_left(t, x->parent, at);  /* левым или правым ребенком */
                    w = x->parent->right;          /* является x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent, at);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == BLACK) &&
                (!w->right || w->right->color == BLACK)
               )                                   /* случай "оба племянники --- черные"     */
            {                                      /* ( NIL-узел считается черным )          */
                w->color = RED;                    /* перекраска и смена x                   */
                x = x->parent;                     /* добавляем черноту родителю x           */
                if (x->color == RED)               /* если он был красный - завершение цикла */
                {
                    x->color = BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == BLACK))
                   ) /* случай "противоположный племянник черный" */
                {
                    w->color = RED;
                    if (x == x->parent->left)
                    {
                        w->left->color = BLACK;
                        rb_rotate_right(t, w, at);
                        w = x->parent->right;
                    }
                    else
                    {
                        w->right->color = BLACK;
                        rb_rotate_left(t, w, at);
                        w = x->parent->left;
                    }
                }
                /* случай "ближний племянник черный" */
                w->color         = x->parent->color;
                x->parent->color = BLACK;

                if (x == x->parent->left)
                {
                    w->right->color = BLACK;
                    rb_rotate_left(t, x->parent, at);
                }
                else
                {
                    w->left->color = BLACK;
                    rb_rotate_right(t, x->parent, at);
                }

                x = t->root;   /* выход из цикла */
            }
        }

        x->color = BLACK;
    }

    free (y);  /* удаляем элемент из памяти */
    if (n)     /* исключаем и удаляем       */
    {
        if (n == t->root)                  /* если удалялся последний элемент */
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left  = NULL;
            else
                n->parent->right = NULL;
        }
        free (n);
    }
    if(at) rb_tree_graph(t, 5, t->root);
    return 0;

}

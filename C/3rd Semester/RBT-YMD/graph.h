#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include"rbt.h"

void rbt_tree_graph(rb_tree *t, size_t n, rb_node *nd);

void rbt_node_graph(rb_node *nd, int x, int y, double fi);

#endif // GRAPH_H_INCLUDED

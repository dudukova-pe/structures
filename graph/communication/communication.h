#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../entering/entering.h"
#include "../graph/graph.h"

Graph* create_graph();
int input_coordinates(uint* x, uint* y);
int insert_vertex(Graph* graph);
int insert_edge(Graph* graph);
int change_type(Graph* graph);
int remove_vertex(Graph* graph);
int remove_edge(Graph* graph);
int checking_reachability(Graph* graph);
int find_shortest_way(Graph* graph);
int find_nearest_exit(Graph* graph);
int print_graph(Graph* graph);
int print_graph_with_change(Graph* graph);
int make_graph_example(Graph* graph);
void delete_graph(Graph* graph);

#endif /*COMMUNICATION_H*/
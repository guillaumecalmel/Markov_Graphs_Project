//
// Created by guill on 06/11/2025.
//
#include "structures.h"
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

t_cell*create_Cell(int arr_vert, float proba);
t_list create_empty_list();
void add_cell(t_list *ptr_list, int arr_vert, float proba);
void display_list(t_list list);
t_adj_list create_adj_list(int size);
void display_adj_list(t_adj_list adj);
t_adj_list readGraph(const char *filename);

#endif //FUNCTIONS_H

//
// Created by guill on 05/11/2025.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_cell{
    int arrival_vertex;
    float proba;
    struct s_cell *next;
}t_cell;

typedef struct s_list{
    t_cell*head;
}t_list;

typedef struct s_adj_list{
    int size;
    t_list *array;
}t_adj_list;


#endif //STRUCTURES_H

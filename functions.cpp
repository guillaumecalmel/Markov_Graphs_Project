//Functions implemented
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <math.h>


t_cell*create_Cell(int arr_vert, float proba){
    t_cell *cell = (t_cell*)malloc(sizeof(t_cell));
    cell->proba = proba;
    cell->arrival_vertex = arr_vert;
    cell->next = NULL;
    return cell;
}

t_list create_empty_list(){
    t_list list;
    list.head = NULL;
    return list;
}

void add_cell(t_list *ptr_list, int arr_vert, float proba){
    t_cell *new_cell = create_Cell(arr_vert, proba);
    new_cell->next = ptr_list->head;
    ptr_list->head = new_cell;
    return;
}

void display_list(t_list list){
    t_cell *current = list.head;
    while(current != NULL){
        printf("Arrival vertex :%d, Probability : %d", current->arrival_vertex, current->proba);
        current = current->next;
    }
}

t_adj_list create_adj_list(int size){
    t_adj_list adj_list;
    adj_list.size = size;
    adj_list.array = (t_list*)malloc(size * sizeof(t_list));
    for (int i = 0; i < size; i++) {
        adj_list.array[i] = create_empty_list();
    }
    return adj_list;
}

void display_adj_list(t_adj_list adj) {
    for (int i = 0; i < adj.size; i++) {
        printf("Vertex %d:", i);
        display_list(adj.array[i]);
    }
}

t_adj_list readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, start, end;
    float proba;
    t_adj_list adj;
    //declare the variable for the adjacency list
    if (file == NULL){
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }      // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1){
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    adj = create_adj_list(nbvert);
    //Initialise an empty adjacency list using the number of vertices
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3){
        add_cell(&adj.array[start], end, proba);
    }
    fclose(file);
    return adj;
}

void check_markov_graph(t_adj_list graph) {
    int is_markov = 1;

    for (int i = 0; i < graph.size; i++) {
        float sum = 0.0f;
        t_cell *curr = graph.array[i].head;

        while (curr != NULL) {
            sum += curr->proba;
            curr = curr->next;
        }

        if (sum < 0.99f || sum > 1.01f) {
            printf("Vertex %d: sum of probabilities = %.2f \n", i, sum);
            is_markov = 0;
        }
    }

    if (is_markov)
        printf("The graph is a Markov graph.\n");
    else
        printf("The graph is not a Markov graph.\n");
}

char* getId(int num);

void writeMermaidGraph(t_adj_list* graph, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    // Write configuration
    fprintf(fp, "---\n");
    fprintf(fp, "config:\n");
    fprintf(fp, "  layout: elk\n");
    fprintf(fp, "  theme: neo\n");
    fprintf(fp, "  look: neo\n");
    fprintf(fp, "---\n\n");
    fprintf(fp, "flowchart LR\n\n");

    // Write vertices
    for (int i = 0; i < graph->size; i++) {
        char* id = getId(i + 1); // assuming vertices numbered 1..size
        fprintf(fp, "  %s((%d))\n", id, i + 1);
    }

    fprintf(fp, "\n");

    // Write edges
    for (int i = 0; i < graph->size; i++) {
        t_cell* current = graph->array[i].head;
        char* fromId = getId(i + 1);

        while (current != NULL) {
            char* toId = getId(current->arrival_vertex);
            fprintf(fp, "  %s -->|%.2f|%s\n", fromId, current->proba, toId);
            current = current->next;
        }
    }

    fclose(fp);
}
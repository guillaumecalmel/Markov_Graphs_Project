#include <stdio.h>


int main() {
    t_adj_list graph = readGraph("data_file.txt");

    printf("Graph loaded from file:\n");
    display_adj_list(graph);

    return 0;
}
